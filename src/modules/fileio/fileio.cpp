/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2024. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - File I/O
-------------------------------------------------------------------
*/

#ifndef _WIN32
    #define UNICODE
#endif

#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "tinydir.h"
#include "dinfio_module.h"

Connector* connector;
uint_fast16_t __file_size, __file_exists, __file_content, __file_put;
uint_fast16_t __file, __file_read, __file_readln, __file_write, __file_writeln, __readbyte, __readstring, __writebyte, __writestring;
uint_fast16_t __file_eof, __file_size_alt, __file_close, __file_reopen;
uint_fast16_t __getcurrentfile, __getcurrentdirectory, __getabsolutepath, __getfoldername, __getfilename, __deletefile, __deletefolder;
uint_fast16_t __list_dirs, __list_files;

class FileIO: public Base {
public:
    string filename;
    fstream holder;

    ~FileIO() {}
};

long get_file_size(string filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

string read_file(string filename) {
    ifstream t(filename);
    stringstream buffer;
    buffer << t.rdbuf();

    return buffer.str();
}

#ifdef _WIN32
string full_path(const char* filename) {
    char full[MAX_PATH];
    GetFullPathName(filename, MAX_PATH, full, nullptr);

    return full;
}

string getcwd_string() {
   char buff[MAX_PATH];
   char* temp = getcwd(buff, MAX_PATH);
   string cwd(buff);

   return cwd;
}
#else
string full_path(const char* filename) {
    char* path = realpath(filename, NULL);

    if(path == NULL) {
        return "";
    } else {
        string result = path;
        return result;
    }
}

string getcwd_string() {
   char buff[PATH_MAX];
   char* temp = getcwd(buff, PATH_MAX);
   string cwd(buff);

   return cwd;
}
#endif

string dirname(const string& fname) {
    size_t pos = fname.find_last_of("\\/");
    return (string::npos == pos) ? "" : fname.substr(0, pos);
}

string fname(const string& filename) {
    size_t pos = filename.find_last_of("\\/");
    return (string::npos == pos) ? "" : filename.substr(pos + 1);
}

bool is_number(const string& s) {
    char* p;
    strtod(s.c_str(), &p);
    return *p == 0;
}

gc<DataType> get_list_dirs(string path, bool fullpath) {
    gc<DataType> result = connector->__create_array(0);
    tinydir_dir dir;
    tinydir_open(&dir, path.c_str());

    int i = 0;

    while (dir.has_next) {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        std::string filename = file.name;
        std::string filepath = file.path;

        if (filename != "." && filename != "..") {
            if (file.is_dir) {
                gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
                d->__value_string = (fullpath) ? filepath : filename;
                result->__value_array->__elements.push_back(d);
                i++;
            }
        }

        tinydir_next(&dir);
    }

    tinydir_close(&dir);
    return result;
}

gc<DataType> get_list_files(string path, bool fullpath) {
    gc<DataType> result = connector->__create_array(0);
    tinydir_dir dir;
    tinydir_open(&dir, path.c_str());

    int i = 0;

    while (dir.has_next) {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        std::string filename = file.name;
        std::string filepath = file.path;

        if (filename != "." && filename != "..") {
            if (!file.is_dir) {
                gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
                d->__value_string = (fullpath) ? filepath : filename;
                result->__value_array->__elements.push_back(d);
                i++;
            }
        }

        tinydir_next(&dir);
    }

    tinydir_close(&dir);
    return result;
}

void add_constant_double(string name, double value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
    d->__value_double = value;
    connector->__add_constant(name, d);
}

void add_constant_string(string name, string value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
    d->__value_string = value;
    connector->__add_constant(name, d);
}

extern "C" Module* create_module() {
    return new Module();
}

extern "C" void destroy_module(Module* m) {
    delete m;
}

void Module::__init(Connector* c) {
    connector = c;


    // Add constants

    add_constant_double("file_append", ios::app);
    add_constant_double("file_read", ios::in);
    add_constant_double("file_write", ios::out);
    add_constant_double("file_binary", ios::binary);
    add_constant_double("file_truncate", ios::trunc);


    // Register functions

    __file_size = connector->__register_function("filesize");
    __file_exists = connector->__register_function("fileexists");
    __file_content = connector->__register_function("filecontent");
    __file_put = connector->__register_function("fileput");
    __file = connector->__register_function("file");
    __file_read = connector->__register_function("file::read");
    __file_readln = connector->__register_function("file::readln");
    __file_write = connector->__register_function("file::write");
    __file_writeln = connector->__register_function("file::writeln");
    __readbyte = connector->__register_function("file::readbyte");
    __readstring = connector->__register_function("file::readstring");
    __writebyte = connector->__register_function("file::writebyte");
    __writestring = connector->__register_function("file::writestring");
    __file_eof = connector->__register_function("file::eof");
    __file_size_alt = connector->__register_function("file::size");
    __file_close = connector->__register_function("file::close");
    __file_reopen = connector->__register_function("file::reopen");
    __getcurrentfile = connector->__register_function("getcurrentfile");
    __getcurrentdirectory = connector->__register_function("getcurrentdirectory");
    __getabsolutepath = connector->__register_function("getabsolutepath");
    __getfoldername = connector->__register_function("getfoldername");
    __getfilename = connector->__register_function("getfilename");
    __list_dirs = connector->__register_function("listdirs");
    __list_files = connector->__register_function("listfiles");
    __deletefile = connector->__register_function("deletefile");
    __deletefolder = connector->__register_function("deletefolder");


    // Set function addresses boundary

    __min = __file_size;
    __max = __deletefolder;   // DO NOT FORGET THIS!
}

gc<DataType> Module::__call(uint_fast16_t& func_id, AST* func, gc<Object> obj, uint_fast32_t& caller_id) {
    gc<DataType> result = new_gc<DataType>(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __file_size) {
        if (params.size() < 1) connector->__error_message_param("filesize");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("filesize(): parameter #1 must be a string");
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = get_file_size(d->__value_string);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __file_exists) {
        if (params.size() < 1) connector->__error_message_param("fileexists");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("fileexists(): parameter #1 must be a string");
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = get_file_size(d->__value_string) != -1;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __file_content) {
        if (params.size() < 1) connector->__error_message_param("filecontent");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("filecontent(): parameter #1 must be a string");
        
        result->__type = __TYPE_STRING__;
        result->__value_string = read_file(d->__value_string);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __file_put) {
        if (params.size() < 2) connector->__error_message_params("fileput", 2);

        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("fileput(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("fileput(): parameter #2 must be a string");
        
        bool is_append = false;
        result->__type = __TYPE_BOOL__;

        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("fileput(): parameter #3 must be a boolean");
            is_append = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }

        if (!is_append) {
            ofstream fh(d->__value_string);

            if (!fh.fail()) {
                fh << e->__value_string;
                fh.close();

                result->__value_bool = true;
            } else {
                result->__value_bool = false;
            }
        } else {
            ofstream fh(d->__value_string, ios_base::app);

            if (!fh.fail()) {
                fh << e->__value_string;
                fh.close();
                
                result->__value_bool = true;
            } else {
                result->__value_bool = false;
            }
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __getcurrentfile) {
        result->__type = __TYPE_STRING__;
        result->__value_string = full_path(connector->__get_current_file().c_str());

        return result;
    } else if (func_id == __getcurrentdirectory) {
        result->__type = __TYPE_STRING__;
        result->__value_string = getcwd_string();

        return result;
    } else if (func_id == __getabsolutepath) {
        if (params.size() < 1) connector->__error_message_param("getabsolutepath");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("getabsolutepath(): parameter #1 must be a string");

        result->__type = __TYPE_STRING__;
        result->__value_string = full_path(d->__value_string.c_str());

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __getfoldername) {
        if (params.size() < 1) connector->__error_message_param("getfoldername");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("getfoldername(): parameter #1 must be a string");

        result->__type = __TYPE_STRING__;
        result->__value_string = dirname(full_path(d->__value_string.c_str()));

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __getfilename) {
        if (params.size() < 1) connector->__error_message_param("getfilename");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("getfilename(): parameter #1 must be a string");

        result->__type = __TYPE_STRING__;
        result->__value_string = fname(full_path(d->__value_string.c_str()));

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __deletefile) {
        if (params.size() < 1) connector->__error_message_param("deletefile");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("deletefile(): parameter #1 must be a string");

        result->__type = __TYPE_BOOL__;
        result->__value_bool = remove(d->__value_string.c_str()) == 0 ? true : false;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __deletefolder) {
        if (params.size() < 1) connector->__error_message_param("deletefolder");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("deletefolder(): parameter #1 must be a string");

        result->__type = __TYPE_BOOL__;
        result->__value_bool = remove(d->__value_string.c_str()) == 0 ? true : false;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __list_dirs) {
        if (params.size() < 1) connector->__error_message_param("listdirs");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("listdirs(): parameter #1 must be a string");
        if (d->__value_string == "") connector->__error_message("listdirs(): path cannot be an empty string");

        string path = d->__value_string;
        bool fullpath = false;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("listdirs(): parameter #2 must be a boolean");
            fullpath = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        connector->__remove_garbage(params.at(0), d);
        return get_list_dirs(path, fullpath);
    } else if (func_id == __list_files) {
        if (params.size() < 1) connector->__error_message_param("listfiles");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("listfiles(): parameter #1 must be a string");
        if (d->__value_string == "") connector->__error_message("listfiles(): path cannot be an empty string");

        string path = d->__value_string;
        bool fullpath = false;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("listfiles(): parameter #2 must be a boolean");
            fullpath = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }
        
        connector->__remove_garbage(params.at(0), d);
        return get_list_files(path, fullpath);

    } else if (func_id == __file) {
        if (params.size() < 2) connector->__error_message_params("file", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("file(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("file(): parameter #2 must be a number");

        FileIO* fio = new FileIO();
        fio->filename = d->__value_string;
        fio->holder.open(d->__value_string, (ios_base::openmode) e->__value_double);
        
        if (fio->holder.is_open()) {
            gc<DataType> dfo = connector->__create_object("file");
            dfo->__value_object->__holder_pointer = fio;
            
            gc<DataType> dfo_f = new_gc<DataType>(__TYPE_STRING__);
            dfo_f->__value_string = d->__value_string;
            gc<DataType> dfo_m = new_gc<DataType>(__TYPE_DOUBLE__);
            dfo_m->__value_double = e->__value_double;
            
            connector->__object_set_attribute(dfo, "name", dfo_f);
            connector->__object_set_attribute(dfo, "mode", dfo_m);
            
            connector->__object_set_function(dfo, "read", __file_read);
            connector->__object_set_function(dfo, "readln", __file_readln);
            connector->__object_set_function(dfo, "write", __file_write);
            connector->__object_set_function(dfo, "writeln", __file_writeln);
            connector->__object_set_function(dfo, "readbyte", __readbyte);
            connector->__object_set_function(dfo, "readstring", __readstring);
            connector->__object_set_function(dfo, "writebyte", __writebyte);
            connector->__object_set_function(dfo, "writestring", __writestring);
            connector->__object_set_function(dfo, "eof", __file_eof);
            connector->__object_set_function(dfo, "size", __file_size);
            connector->__object_set_function(dfo, "close", __file_close);
            connector->__object_set_function(dfo, "reopen", __file_reopen);

            connector->__remove_garbage(params.at(0), d);
            connector->__remove_garbage(params.at(1), e);

            return dfo;
        } else {
            connector->__remove_garbage(params.at(0), d);
            connector->__remove_garbage(params.at(1), e);

            result->__type = __TYPE_NULL__;
        }

        return result;
    } else if (func_id == __file_close) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        fio->holder.close();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        return result;
    } else if (func_id == __file_reopen) {
        if (params.size() < 2) connector->__error_message_params("file::reopen", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);

        if (d->__type != __TYPE_STRING__) connector->__error_message("file::reopen(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("file::reopen(): parameter #2 must be a number");

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);

        if (fio->holder.is_open()) fio->holder.close();

        fio->filename = d->__value_string;
        fio->holder.open(d->__value_string, (ios_base::openmode) e->__value_double);
        
        if (fio->holder.is_open()) {
            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;
        } else {
            result->__type = __TYPE_BOOL__;
            result->__value_bool = false;
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __file_eof) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = (fio->holder.peek() == EOF);

        return result;
    } else if (func_id == __file_size_alt) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = get_file_size(fio->filename);

        return result;
    } else if (func_id == __file_read) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);

        string s = "";
        fio->holder >> s;
        
        if (s != "" && is_number(s)) {
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = stod(s);
        } else if (s == "true") {
            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;
        } else if (s == "false") {
            result->__type = __TYPE_BOOL__;
            result->__value_bool = false;
        } else {
            result->__type = __TYPE_STRING__;
            result->__value_string = s;
        }

        return result;
    } else if (func_id == __file_readln) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);

        string s = "";
        getline(fio->holder, s);
        
        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        return result;
    } else if (func_id == __file_write) {
        if (params.size() < 1) connector->__error_message_param("file::write");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);

        if (d->__type == __TYPE_DOUBLE__) {
            fio->holder << d->__value_double;
        } else if (d->__type == __TYPE_STRING__) {
            fio->holder << d->__value_string;
        } else if (d->__type == __TYPE_BOOL__) {
            string s = d->__value_bool ? "true" : "false";
            fio->holder << s;
        } else if (d->__type == __TYPE_ARRAY__) {
            stringstream sstream;
            sstream << std::hex << d->__value_array->__address;
            string result = sstream.str();

            fio->holder << "array@0x0" << result;
        } else if (d->__type == __TYPE_OBJECT__) {
            stringstream sstream;
            sstream << std::hex << d->__value_object->__address;
            string result = sstream.str();

            fio->holder << d->__value_object->__name << "@0x0" << result;
        } else {
            fio->holder << "nothing";
        }
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __file_writeln) {
        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);

            if (d->__type == __TYPE_DOUBLE__) {
                fio->holder << d->__value_double << endl;
            } else if (d->__type == __TYPE_STRING__) {
                fio->holder << d->__value_string << endl;
            } else if (d->__type == __TYPE_BOOL__) {
                string s = d->__value_bool ? "true" : "false";
                fio->holder << s << endl;
            } else if (d->__type == __TYPE_ARRAY__) {
                stringstream sstream;
                sstream << std::hex << d->__value_array->__address;
                string result = sstream.str();

                fio->holder << "array@0x0" << result << endl;
            } else if (d->__type == __TYPE_OBJECT__) {
                stringstream sstream;
                sstream << std::hex << d->__value_object->__address;
                string result = sstream.str();

                fio->holder << d->__value_object->__name << "@0x0" << result << endl;
            } else {
                fio->holder << "nothing" << endl;
            }

            connector->__remove_garbage(params.at(0), d);
        } else {
            fio->holder << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        return result;
    } else if (func_id == __readbyte) {
        if (params.size() < 1) connector->__error_message_param("file::readbyte");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("file::readbyte(): parameter #1 must be a number");

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        unsigned char x;

        fio->holder.seekg(d->__value_double);
        fio->holder.read((char*) &x, sizeof(x));
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = x;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __readstring) {
        if (params.size() < 2) connector->__error_message_params("file::readstring", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("file::readstring(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("file::readstring(): parameter #2 must be a number");

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        unsigned char x[(int) (e->__value_double)];
        string s = "";

        fio->holder.seekg(d->__value_double);
        fio->holder.read((char*) &x, (int) (e->__value_double));

        for (int i = 0; i < e->__value_double; i++) {
            s += x[i];
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __writebyte) {
        if (params.size() < 2) connector->__error_message_params("file::writebyte", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("file::writebyte(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("file::writebyte(): parameter #2 must be a number");

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        unsigned char x = (unsigned char) d->__value_double;
        
        fio->holder.seekp(e->__value_double);
        fio->holder.write((char*) &x, sizeof(char));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __writestring) {
        if (params.size() < 2) connector->__error_message_params("file::writestring", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("file::writestring(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("file::writestring(): parameter #2 must be a number");

        gc<Object> f = obj;
        FileIO* fio = ((FileIO*) f->__holder_pointer);
        string t = d->__value_string;
        
        fio->holder.seekp(e->__value_double);
        fio->holder.write(t.c_str(), t.size());

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    }

    return result;
}
