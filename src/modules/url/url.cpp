/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.1
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2022. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - URL
-------------------------------------------------------------------
 Compilation Instruction:
  - Please see ./compile.sh
-------------------------------------------------------------------
*/

/*
NOTE: Add this if your libcurl version >= 7.56
#define __NEW_CURL__
*/

#include <curl/curl.h>
#include "module.h"

Connector* connector;
uint_fast16_t __url_get, __url_post;
uint_fast16_t __file_data, __url_encode, __url_decode;
uint_fast16_t __url_verbose, __url_follow_location, __url_ssl_verify_peer, __url_ssl_verify_host;
uint_fast16_t __url_ssl_cainfo, __url_ssl_capath, __url_proxy;
uint_fast16_t __bytes_unit;

long __verbose = 0L;
long __follow_location = 1L;
long __ssl_verify_peer = 1L;
long __ssl_verify_host = 2L;
bool __ssl_use_cainfo = false;
bool __ssl_use_capath = false;
bool __use_proxy = false;
string __ssl_cainfo = "";
string __ssl_capath = "";
string __proxy = "";

const string __USER_AGENT__ = "dinfio-url/1.0.0";

class Progress {
public:
    uint_fast32_t __caller_id;
    AST* __callback;
};

size_t __write_to_string(void* ptr, size_t size, size_t nmemb, string* s) {
    s->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

static size_t __write_to_file(void* ptr, size_t size, size_t nmemb, void* stream) {
    return fwrite(ptr, size, nmemb, (FILE*) stream);
}

DataType* __new_double(double v) {
    DataType* d = new DataType(__TYPE_DOUBLE__);
    d->__value_double = v;

    return d;
}

DataType* __new_string(string v) {
    DataType* d = new DataType(__TYPE_STRING__);
    d->__value_string = v;

    return d;
}

int __progress_callback(void* ptr, double total_download, double downloaded, double total_upload, double uploaded) {
    Progress* p = (Progress*) ptr;

    if (p->__callback == NULL) {
        // Continue downloading/uploading

        return 0;
    } else {
        vector<AST*> params2;
        AST_FunctionCall* af = (AST_FunctionCall*) p->__callback;

        for (int i = 0; i < af->__parameters.size(); i++) {
            params2.push_back(af->__parameters.at(i));
        }

        params2.push_back(new AST_Value(__new_double(downloaded)));
        params2.push_back(new AST_Value(__new_double(total_download)));
        params2.push_back(new AST_Value(__new_double(uploaded)));
        params2.push_back(new AST_Value(__new_double(total_upload)));

        AST_FunctionCall* aaf = new AST_FunctionCall(af->__identifier);
        aaf->__address = af->__address;
        aaf->__parameters = params2;

        DataType* d = connector->__get_value(aaf, p->__caller_id);
        int code = (int) d->__value_double;

        connector->__remove_garbage(aaf, d);

        return code;
    }
}

void add_constant_double(string name, double value) {
    DataType* d = new DataType(__TYPE_DOUBLE__);
    d->__value_double = value;
    connector->__add_constant(name, d);
}

void add_constant_string(string name, string value) {
    DataType* d = new DataType(__TYPE_STRING__);
    d->__value_string = value;
    connector->__add_constant(name, d);
}

void __add_constant_url() {
    DataType* d = connector->__create_object("url");

    connector->__object_set_function(d, "get", __url_get);
    connector->__object_set_function(d, "post", __url_post);
    connector->__object_set_function(d, "encode", __url_encode);
    connector->__object_set_function(d, "decode", __url_decode);

    connector->__object_set_function(d, "verbose", __url_verbose);
    connector->__object_set_function(d, "follow_location", __url_follow_location);
    connector->__object_set_function(d, "ssl_verify_peer", __url_ssl_verify_peer);
    connector->__object_set_function(d, "ssl_verify_host", __url_ssl_verify_host);
    connector->__object_set_function(d, "ssl_cainfo", __url_ssl_cainfo);
    connector->__object_set_function(d, "ssl_capath", __url_ssl_capath);
    connector->__object_set_function(d, "proxy", __url_proxy);

    connector->__add_constant("url", d);
}

void __add_constant_http() {
    DataType* d = connector->__create_object("http");

    connector->__object_set_attribute(d, "ok", __new_double(200));
    connector->__object_set_attribute(d, "not_found", __new_double(404));
    connector->__object_set_attribute(d, "bad_request", __new_double(400));
    connector->__object_set_attribute(d, "unauthorised", __new_double(401));
    connector->__object_set_attribute(d, "forbidden", __new_double(403));
    connector->__object_set_attribute(d, "internal_server_error", __new_double(500));
    connector->__object_set_attribute(d, "bad_gateway", __new_double(502));
    connector->__object_set_attribute(d, "service_unavailable", __new_double(503));
    connector->__object_set_attribute(d, "gateway_timeout", __new_double(504));

    connector->__add_constant("http", d);
}

string __url_escape(string str) {
    CURL *curl = curl_easy_init();
    string result = "";

    if (curl) {
        char* output = curl_easy_escape(curl, str.c_str(), str.length());

        if (output) {
            result = output;
            curl_free(output);
        }
    }

    return result;
}

string __url_unescape(string str) {
    CURL *curl = curl_easy_init();
    string result = "";

    if (curl) {
        char* output = curl_easy_unescape(curl, str.c_str(), str.length(), NULL);

        if (output) {
            result = output;
            curl_free(output);
        }
    }

    return result;
}

string __parse_request_params(Object* p) {
    if (p->__attributes.empty()) return "";

    stringstream result;
    auto ib = p->__attributes.cbegin();
    auto ie = p->__attributes.cend();

    string key = ib->first;
    if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

    result << key + "=";
    DataType* d = ib->second;

    if (d->__type == __TYPE_DOUBLE__) {
        string ss = to_string(d->__value_double);

        ss.erase(ss.find_last_not_of('0') + 1, string::npos);
        ss.erase(ss.find_last_not_of('.') + 1, string::npos);

        result << ss;
    } else if (d->__type == __TYPE_STRING__) {
        result << __url_escape(d->__value_string);
    } else if (d->__type == __TYPE_BOOL__) {
        string s = d->__value_bool ? "true" : "false";
        result << s;
    } else if (d->__type == __TYPE_ARRAY__) {
        stringstream ss;
        ss << std::hex << d->__value_array->__address;

        result << "array@0x0" << ss.str();
    } else if (d->__type == __TYPE_OBJECT__) {
        stringstream ss;
        ss << std::hex << d->__value_object->__address;

        result << d->__value_object->__name << "@0x0" << ss.str();
    } else {
        result << "nothing";
    }

    ++ib;
    if (ib == ie) return result.str();

    for (; ib != ie; ++ib) {
        string key = ib->first;
        if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

        result << "&" << key + "=";
        DataType* d = ib->second;

        if (d->__type == __TYPE_DOUBLE__) {
            string ss = to_string(d->__value_double);

            ss.erase(ss.find_last_not_of('0') + 1, string::npos);
            ss.erase(ss.find_last_not_of('.') + 1, string::npos);

            result << ss;
        } else if (d->__type == __TYPE_STRING__) {
            result << __url_escape(d->__value_string);
        } else if (d->__type == __TYPE_BOOL__) {
            string s = d->__value_bool ? "true" : "false";
            result << s;
        } else if (d->__type == __TYPE_ARRAY__) {
            stringstream ss;
            ss << std::hex << d->__value_array->__address;

            result << "array@0x0" << ss.str();
        } else if (d->__type == __TYPE_OBJECT__) {
            stringstream ss;
            ss << std::hex << d->__value_object->__address;

            result << d->__value_object->__name << "@0x0" << ss.str();
        } else {
            result << "nothing";
        }
    }

    return result.str();
}

struct curl_slist* __parse_header(Object* p) {
    struct curl_slist* chunk = NULL;
    chunk = curl_slist_append(chunk, ("User-Agent: " + __USER_AGENT__).c_str());

    if (p->__attributes.empty()) return chunk;

    auto ib = p->__attributes.cbegin();
    auto ie = p->__attributes.cend();

    for (; ib != ie; ++ib) {
        string key = ib->first;
        if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

        string val = "";
        DataType* d = ib->second;

        if (d->__type == __TYPE_DOUBLE__) {
            string ss = to_string(d->__value_double);

            ss.erase(ss.find_last_not_of('0') + 1, string::npos);
            ss.erase(ss.find_last_not_of('.') + 1, string::npos);

            val = ss;
        } else if (d->__type == __TYPE_STRING__) {
            val = d->__value_string;
        } else if (d->__type == __TYPE_BOOL__) {
            string s = d->__value_bool ? "true" : "false";
            val = s;
        } else if (d->__type == __TYPE_ARRAY__) {
            stringstream ss;
            ss << std::hex << d->__value_array->__address;

            val = "array@0x0" + ss.str();
        } else if (d->__type == __TYPE_OBJECT__) {
            stringstream ss;
            ss << std::hex << d->__value_object->__address;

            val = d->__value_object->__name + "@0x0" + ss.str();
        } else {
            val = "nothing";
        }

        chunk = curl_slist_append(chunk, (key + ": " + val).c_str());
    }

    return chunk;
}

struct curl_slist* __default_header() {
    struct curl_slist* chunk = NULL;
    chunk = curl_slist_append(chunk, ("User-Agent: " + __USER_AGENT__).c_str());
    return chunk;
}

#ifdef __NEW_CURL__
curl_mime* __parse_mime(CURL* curl, Object* p) {
    curl_mime* form = NULL;
    curl_mimepart* field = NULL;

    if (p->__attributes.empty()) return form;

    form = curl_mime_init(curl);

    auto ib = p->__attributes.cbegin();
    auto ie = p->__attributes.cend();

    for (; ib != ie; ++ib) {
        string key = ib->first;
        if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

        DataType* d = ib->second;

        if (d->__type == __TYPE_DOUBLE__) {
            string ss = to_string(d->__value_double);

            ss.erase(ss.find_last_not_of('0') + 1, string::npos);
            ss.erase(ss.find_last_not_of('.') + 1, string::npos);

            field = curl_mime_addpart(form);
            curl_mime_name(field, key.c_str());
            curl_mime_data(field, ss.c_str(), CURL_ZERO_TERMINATED);
        } else if (d->__type == __TYPE_STRING__) {
            field = curl_mime_addpart(form);
            curl_mime_name(field, key.c_str());
            curl_mime_data(field, d->__value_string.c_str(), CURL_ZERO_TERMINATED);
        } else if (d->__type == __TYPE_BOOL__) {
            string s = d->__value_bool ? "true" : "false";

            field = curl_mime_addpart(form);
            curl_mime_name(field, key.c_str());
            curl_mime_data(field, s.c_str(), CURL_ZERO_TERMINATED);
        } else if (d->__type == __TYPE_ARRAY__) {
            string val = "";
            stringstream ss;

            ss << std::hex << d->__value_array->__address;
            val = "array@0x0" + ss.str();
            
            field = curl_mime_addpart(form);
            curl_mime_name(field, key.c_str());
            curl_mime_data(field, val.c_str(), CURL_ZERO_TERMINATED);
        } else if (d->__type == __TYPE_OBJECT__) {
            if (d->__value_object->__name != "file_data") {
                string val = "";
                stringstream ss;

                ss << std::hex << d->__value_object->__address;
                val = d->__value_object->__name + "@0x0" + ss.str();

                field = curl_mime_addpart(form);
                curl_mime_name(field, key.c_str());
                curl_mime_data(field, val.c_str(), CURL_ZERO_TERMINATED);
            } else {
                field = curl_mime_addpart(form);
                curl_mime_name(field, key.c_str());
                curl_mime_filedata(field, d->__value_object->__attributes["filename"]->__value_string.c_str());
            }
        } else {
            field = curl_mime_addpart(form);
            curl_mime_name(field, key.c_str());
            curl_mime_data(field, "nothing", CURL_ZERO_TERMINATED);
        }
    }

    return form;
}
#endif

struct curl_httppost* __parse_mime_old(Object* p) {
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;

    if (p->__attributes.empty()) return post;

    auto ib = p->__attributes.cbegin();
    auto ie = p->__attributes.cend();

    for (; ib != ie; ++ib) {
        string key = ib->first;
        if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

        DataType* d = ib->second;

        if (d->__type == __TYPE_DOUBLE__) {
            string ss = to_string(d->__value_double);

            ss.erase(ss.find_last_not_of('0') + 1, string::npos);
            ss.erase(ss.find_last_not_of('.') + 1, string::npos);

            curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, ss.c_str(), CURLFORM_END);
        } else if (d->__type == __TYPE_STRING__) {
            curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, d->__value_string.c_str(), CURLFORM_END);
        } else if (d->__type == __TYPE_BOOL__) {
            string s = d->__value_bool ? "true" : "false";

            curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, s.c_str(), CURLFORM_END);
        } else if (d->__type == __TYPE_ARRAY__) {
            string val = "";
            stringstream ss;

            ss << std::hex << d->__value_array->__address;
            val = "array@0x0" + ss.str();
            
            curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, val.c_str(), CURLFORM_END);
        } else if (d->__type == __TYPE_OBJECT__) {
            if (d->__value_object->__name != "file_data") {
                string val = "";
                stringstream ss;

                ss << std::hex << d->__value_object->__address;
                val = d->__value_object->__name + "@0x0" + ss.str();

                curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, val.c_str(), CURLFORM_END);
            } else {
                curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_FILE, d->__value_object->__attributes["filename"]->__value_string.c_str(), CURLFORM_END);
            }
        } else {
            curl_formadd(&post, &last, CURLFORM_COPYNAME, key.c_str(), CURLFORM_COPYCONTENTS, "nothing", CURLFORM_END);
        }
    }

    return post;
}

extern "C" Module* create_module() {
    return new Module();
}

extern "C" void destroy_module(Module* object) {
    delete object;
}

void Module::__init(Connector* c) {
    connector = c;


    // Register functions

    __url_get = connector->__register_function("url::get");
    __url_post = connector->__register_function("url::post");
    __url_encode = connector->__register_function("url::encode");
    __url_decode = connector->__register_function("url::decode");
    __url_verbose = connector->__register_function("url::verbose");
    __url_follow_location = connector->__register_function("url::follow_location");
    __url_ssl_verify_peer = connector->__register_function("url::ssl_verify_peer");
    __url_ssl_verify_host = connector->__register_function("url::ssl_verify_host");
    __url_ssl_cainfo = connector->__register_function("url::ssl_cainfo");
    __url_ssl_capath = connector->__register_function("url::ssl_capath");
    __url_proxy = connector->__register_function("url::proxy");
    __file_data = connector->__register_function("file_data");
    __bytes_unit = connector->__register_function("bytes_unit");


    // Set function addresses boundary

    __min = __url_get;
    __max = __bytes_unit;   // DO NOT FORGET THIS!


    // Add constants

    __add_constant_url();
    __add_constant_http();
}

DataType* Module::__call(uint_fast16_t& func_id, AST* func, Object* obj, uint_fast32_t& caller_id) {
    DataType* result = new DataType(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __bytes_unit) {
        if (params.size() < 1) connector->__error_message_param("bytes_unit");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("bytes_unit(): parameter #1 must be a number");
        
        double val = d->__value_double;
        result->__type = __TYPE_STRING__;

        if (val >= 1073741824) {
            stringstream ss;
            ss << (val / 1073741824) << " GB";
            result->__value_string = ss.str();
        } else if (val >= 1048576) {
            stringstream ss;
            ss << (val / 1048576) << " MB";
            result->__value_string = ss.str();
        } else if (val >= 1024) {
            stringstream ss;
            ss << (val / 1024) << " kB";
            result->__value_string = ss.str();
        } else {
            stringstream ss;
            ss << val << " B";
            result->__value_string = ss.str();
        }

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_encode) {
        if (params.size() < 1) connector->__error_message_param("url::encode");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::encode(): parameter #1 must be a string");
        
        result->__type = __TYPE_STRING__;
        result->__value_string = __url_escape(d->__value_string);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_decode) {
        if (params.size() < 1) connector->__error_message_param("url::decode");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::decode(): parameter #1 must be a string");
        
        result->__type = __TYPE_STRING__;
        result->__value_string = __url_unescape(d->__value_string);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __file_data) {
        if (params.size() < 1) connector->__error_message_param("file_data");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("file_data(): parameter #1 must be a string");
        
        DataType* dfo = connector->__create_object("file_data");
        connector->__object_set_attribute(dfo, "filename", __new_string(d->__value_string));

        connector->__remove_garbage(params.at(0), d);

        return dfo;
    

    // Configurations

    } else if (func_id == __url_verbose) {
        if (params.size() < 1) connector->__error_message_param("url::verbose");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_BOOL__) connector->__error_message("url::verbose(): parameter #1 must be a boolean");

        __verbose = d->__value_bool ? 1L : 0L;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_follow_location) {
        if (params.size() < 1) connector->__error_message_param("url::follow_location");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_BOOL__) connector->__error_message("url::follow_location(): parameter #1 must be a boolean");

        __follow_location = d->__value_bool ? 1L : 0L;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_ssl_verify_peer) {
        if (params.size() < 1) connector->__error_message_param("url::ssl_verify_peer");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("url::ssl_verify_peer(): parameter #1 must be a number");

        __ssl_verify_peer = (long) d->__value_double;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_ssl_verify_host) {
        if (params.size() < 1) connector->__error_message_param("url::ssl_verify_host");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("url::ssl_verify_host(): parameter #1 must be a number");

        __ssl_verify_host = (long) d->__value_double;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_ssl_cainfo) {
        if (params.size() < 1) connector->__error_message_param("url::ssl_cainfo");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::ssl_cainfo(): parameter #1 must be a string");

        __ssl_use_cainfo = (d->__value_string != "") ? true : false;
        __ssl_cainfo = d->__value_string;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_ssl_capath) {
        if (params.size() < 1) connector->__error_message_param("url::ssl_capath");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::ssl_capath(): parameter #1 must be a string");

        __ssl_use_capath = (d->__value_string != "") ? true : false;
        __ssl_capath = d->__value_string;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __url_proxy) {
        if (params.size() < 1) connector->__error_message_param("url::proxy");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::proxy(): parameter #1 must be a string");

        __use_proxy = (d->__value_string != "") ? true : false;
        __proxy = d->__value_string;
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    

    // HTTP GET method

    } else if (func_id == __url_get) {
        if (params.size() < 1) connector->__error_message_param("url::get");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::get(): parameter #1 must be a string");

        string url = d->__value_string;
        string request_params = "";
        DataType* header = NULL;
        string downloaded_to = "";
        AST* progress_callback = NULL;

        Progress* prog = new Progress();

        long response_code = 0;
        string response_body = "";
        int response_error = 0;
        string response_error_string = "";

        if (params.size() > 1) {
            DataType* e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_STRING__ && e->__type != __TYPE_OBJECT__) connector->__error_message("url::get(): parameter #2 must be a string or an object");

            if (e->__type == __TYPE_STRING__) {
                request_params = e->__value_string;
            } else {
                request_params = __parse_request_params(e->__value_object);
            }

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            header = connector->__get_value(params.at(2), caller_id);
            if (header->__type != __TYPE_OBJECT__) connector->__error_message("url::get(): parameter #3 must be an object");
        }
        if (params.size() > 3) {
            DataType* f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("url::get(): parameter #4 must be a string");

            downloaded_to = f->__value_string;
            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            AST* g = params.at(4);
            if (g->__type != __AST_FUNCTION_CALL__) connector->__error_message("url::get(): parameter #5 must be a function call");

            vector<AST*> params2;
            AST_FunctionCall* af = (AST_FunctionCall*) g;

            for (int i = 0; i < af->__parameters.size(); i++) {
                DataType* ad = connector->__get_value(af->__parameters.at(i), caller_id);
                DataType* ae;

                if (ad->__type == __TYPE_DOUBLE__) {
                    ae = new DataType(__TYPE_DOUBLE__);
                    ae->__value_double = ad->__value_double;
                } else if (ad->__type == __TYPE_BOOL__) {
                    ae = new DataType(__TYPE_BOOL__);
                    ae->__value_bool = ad->__value_bool;
                } else if (ad->__type == __TYPE_STRING__) {
                    ae = new DataType(__TYPE_STRING__);
                    ae->__value_string = ad->__value_string;
                } else if (ad->__type == __TYPE_ARRAY__) {
                    ae = new DataType(__TYPE_ARRAY__);
                    ae->__value_array = ad->__value_array;
                } else if (ad->__type == __TYPE_OBJECT__) {
                    ae = new DataType(__TYPE_OBJECT__);
                    ae->__value_object = ad->__value_object;
                }

                params2.push_back(new AST_Value(ae));
            }

            AST_FunctionCall* aaf = new AST_FunctionCall(af->__identifier);
            aaf->__address = af->__address;
            aaf->__parameters = params2;

            progress_callback = aaf;

            prog->__callback = progress_callback;
            prog->__caller_id = caller_id;
        }


        // Do cURL

        CURL* curl = curl_easy_init();
        CURLcode res;

        if (request_params == "") {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        } else {
            curl_easy_setopt(curl, CURLOPT_URL, (url + "?" + request_params).c_str());
        }

        curl_easy_setopt(curl, CURLOPT_VERBOSE, __verbose);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, __follow_location);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, __ssl_verify_host);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, __ssl_verify_peer);

        if (__ssl_use_cainfo) {
            curl_easy_setopt(curl, CURLOPT_CAINFO, __ssl_cainfo.c_str());
        } else {
            #ifdef _WIN32
                curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Program Files (x86)\\Dinfio\\curl-ca-bundle.crt");
            #endif
        }
        
        if (__ssl_use_capath) curl_easy_setopt(curl, CURLOPT_CAPATH, __ssl_capath.c_str());
        if (__use_proxy) curl_easy_setopt(curl, CURLOPT_PROXY, __proxy.c_str());

        if (progress_callback != NULL) {
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, __progress_callback);
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, prog);
        } else {
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        }

        if (header != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, __parse_header(header->__value_object));
            connector->__remove_garbage(params.at(2), header);
        } else {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, __default_header());
        }

        if (downloaded_to == "") {
            // Response is saved to string

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __write_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

            res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                response_error = 0;
                response_error_string = "";
            } else {
                response_code = 0;
                response_body = "";
                response_error = (int) res;
                response_error_string = curl_easy_strerror(res);
            }
        } else {
            // Response saved to file

            FILE *target;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __write_to_file);

            target = fopen(downloaded_to.c_str(), "wb");

            if (target) {
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, target);
                res = curl_easy_perform(curl);
                fclose(target);

                if (res == CURLE_OK) {
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                    response_body = "";
                    response_error = 0;
                    response_error_string = "";
                } else {
                    response_code = 0;
                    response_body = "";
                    response_error = (int) res;
                    response_error_string = curl_easy_strerror(res);
                }
            } else {
                response_code = 0;
                response_body = "";
                response_error = 9999;
                response_error_string = "Unable to write to file";
            }
        }

        curl_easy_cleanup(curl);


        // Output

        DataType* dfo = connector->__create_object("response");

        connector->__object_set_attribute(dfo, "code", __new_double(response_code));
        connector->__object_set_attribute(dfo, "body", __new_string(response_body));
        connector->__object_set_attribute(dfo, "error", __new_double(response_error));
        connector->__object_set_attribute(dfo, "error_string", __new_string(response_error_string));

        connector->__remove_garbage(params.at(0), d);

        return dfo;
    

    // HTTP POST method

    } else if (func_id == __url_post) {
        if (params.size() < 1) connector->__error_message_param("url::post");
        DataType* d = connector->__get_value(params.at(0), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("url::post(): parameter #1 must be a string");

        string url = d->__value_string;
        bool multipart = false;
        string request_params = "";
        DataType* dmime;
        DataType* header = NULL;
        string downloaded_to = "";
        AST* progress_callback = NULL;

        Progress* prog = new Progress();

        long response_code = 0;
        string response_body = "";
        int response_error = 0;
        string response_error_string = "";

        if (params.size() > 2) {
            DataType* m = connector->__get_value(params.at(2), caller_id);
            if (m->__type != __TYPE_BOOL__) connector->__error_message("url::post(): parameter #3 must be a boolean");
            multipart = m->__value_bool;

            connector->__remove_garbage(params.at(2), m);
        }
        if (params.size() > 1) {
            if (!multipart) {
                DataType* e = connector->__get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_STRING__ && e->__type != __TYPE_OBJECT__) connector->__error_message("url::post(): parameter #2 must be a string or an object");

                if (e->__type == __TYPE_STRING__) {
                    request_params = e->__value_string;
                } else {
                    request_params = __parse_request_params(e->__value_object);
                }

                connector->__remove_garbage(params.at(1), e);
            } else {
                dmime = connector->__get_value(params.at(1), caller_id);
                if (dmime->__type != __TYPE_OBJECT__) connector->__error_message("url::post(): parameter #2 must be an object because multipart is true");
            }
        }
        if (params.size() > 3) {
            header = connector->__get_value(params.at(3), caller_id);
            if (header->__type != __TYPE_OBJECT__) connector->__error_message("url::post(): parameter #4 must be an object");
        }
        if (params.size() > 4) {
            DataType* f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("url::post(): parameter #5 must be a string");

            downloaded_to = f->__value_string;
            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            AST* g = params.at(5);
            if (g->__type != __AST_FUNCTION_CALL__) connector->__error_message("url::post(): parameter #6 must be a function call");

            vector<AST*> params2;
            AST_FunctionCall* af = (AST_FunctionCall*) g;

            for (int i = 0; i < af->__parameters.size(); i++) {
                DataType* ad = connector->__get_value(af->__parameters.at(i), caller_id);
                DataType* ae;

                if (ad->__type == __TYPE_DOUBLE__) {
                    ae = new DataType(__TYPE_DOUBLE__);
                    ae->__value_double = ad->__value_double;
                } else if (ad->__type == __TYPE_BOOL__) {
                    ae = new DataType(__TYPE_BOOL__);
                    ae->__value_bool = ad->__value_bool;
                } else if (ad->__type == __TYPE_STRING__) {
                    ae = new DataType(__TYPE_STRING__);
                    ae->__value_string = ad->__value_string;
                } else if (ad->__type == __TYPE_ARRAY__) {
                    ae = new DataType(__TYPE_ARRAY__);
                    ae->__value_array = ad->__value_array;
                } else if (ad->__type == __TYPE_OBJECT__) {
                    ae = new DataType(__TYPE_OBJECT__);
                    ae->__value_object = ad->__value_object;
                }

                params2.push_back(new AST_Value(ae));
            }

            AST_FunctionCall* aaf = new AST_FunctionCall(af->__identifier);
            aaf->__address = af->__address;
            aaf->__parameters = params2;

            progress_callback = aaf;

            prog->__callback = progress_callback;
            prog->__caller_id = caller_id;
        }


        // Do cURL

        CURL* curl = curl_easy_init();
        CURLcode res;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, __verbose);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, __follow_location);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, __ssl_verify_host);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, __ssl_verify_peer);

        if (__ssl_use_cainfo) {
            curl_easy_setopt(curl, CURLOPT_CAINFO, __ssl_cainfo.c_str());
        } else {
            #ifdef _WIN32
                curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Program Files (x86)\\Dinfio\\curl-ca-bundle.crt");
            #endif
        }

        if (__ssl_use_capath) curl_easy_setopt(curl, CURLOPT_CAPATH, __ssl_capath.c_str());
        if (__use_proxy) curl_easy_setopt(curl, CURLOPT_PROXY, __proxy.c_str());

        if (progress_callback != NULL) {
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, __progress_callback);
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, prog);
        } else {
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        }

        if (!multipart) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_params.c_str());
        } else {
            #ifdef __NEW_CURL__
                curl_easy_setopt(curl, CURLOPT_MIMEPOST, __parse_mime(curl, dmime->__value_object));
            #else
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, __parse_mime_old(dmime->__value_object));
            #endif

            connector->__remove_garbage(params.at(1), dmime);
        }

        if (header != NULL) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, __parse_header(header->__value_object));
            connector->__remove_garbage(params.at(3), header);
        } else {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, __default_header());
        }

        if (downloaded_to == "") {
            // Response is saved to string

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __write_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

            res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                response_error = 0;
                response_error_string = "";
            } else {
                response_code = 0;
                response_body = "";
                response_error = (int) res;
                response_error_string = curl_easy_strerror(res);
            }
        } else {
            // Response saved to file

            FILE *target;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, __write_to_file);

            target = fopen(downloaded_to.c_str(), "wb");

            if (target) {
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, target);
                res = curl_easy_perform(curl);
                fclose(target);

                if (res == CURLE_OK) {
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                    response_body = "";
                    response_error = 0;
                    response_error_string = "";
                } else {
                    response_code = 0;
                    response_body = "";
                    response_error = (int) res;
                    response_error_string = curl_easy_strerror(res);
                }
            } else {
                response_code = 0;
                response_body = "";
                response_error = 9999;
                response_error_string = "Unable to write to file";
            }
        }

        curl_easy_cleanup(curl);


        // Output

        DataType* dfo = connector->__create_object("response");

        connector->__object_set_attribute(dfo, "code", __new_double(response_code));
        connector->__object_set_attribute(dfo, "body", __new_string(response_body));
        connector->__object_set_attribute(dfo, "error", __new_double(response_error));
        connector->__object_set_attribute(dfo, "error_string", __new_string(response_error_string));

        connector->__remove_garbage(params.at(0), d);

        return dfo;
    }

    return result;
}
