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
 Module - JSON Parser & Builder (RFC 8259)
-------------------------------------------------------------------
*/

#include "json.hpp"
#include "dinfio_module.h"

using json = nlohmann::json;

Connector* connector;
uint_fast16_t __json_encode, __json_decode, __json_error;

string __json_error_string = "";

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

DataType* __new_bool(bool v) {
    DataType* d = new DataType(__TYPE_BOOL__);
    d->__value_bool = v;

    return d;
}

void __add_constants() {
    DataType* d = connector->__create_object("json");

    connector->__object_set_function(d, "encode", __json_encode);
    connector->__object_set_function(d, "decode", __json_decode);
    connector->__object_set_function(d, "get_error", __json_error);

    connector->__add_constant("json", d);
}

string lcase(string s) {
    string result = "";

    for (int i = 0; i < s.length(); i++) {
        result += tolower(s[i]);
    }

    return result;
}

json __encode(DataType* d) {
    json result;

    if (d->__type == __TYPE_BOOL__) {
        result = d->__value_bool;
    } else if (d->__type == __TYPE_DOUBLE__) {
        if (d->__value_double == floor(d->__value_double)) {
            result = (int) d->__value_double;
        } else {
            result = d->__value_double;
        }
    } else if (d->__type == __TYPE_STRING__) {
        result = d->__value_string;
    } else if (d->__type == __TYPE_NULL__) {
        result = nullptr;
    } else if (d->__type == __TYPE_OBJECT__) {
        for (const auto &attr: d->__value_object->__attributes) {
            string key = attr.first;
            if (key.at(0) == '"' && key.at(key.length() - 1) == '"') key = key.substr(1, key.length() - 2);

            result[key] = __encode(attr.second);
        }
    } else if (d->__type == __TYPE_ARRAY__) {
        for (int i = 0; i < d->__value_array->__elements.size(); i++) {
            result.push_back(__encode(d->__value_array->__elements.at(i)));
        }
    }

    return result;
}

DataType* __decode(json& js) {
    DataType* result = new DataType(__TYPE_NULL__);

    if (js.is_boolean()) {
        result->__type = __TYPE_BOOL__;
        result->__value_bool = js;
    } else if (js.is_string()) {
        result->__type = __TYPE_STRING__;
        result->__value_string = js;
    } else if (js.is_number()) {
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = js;
    } else if (js.is_object()) {
        result = connector->__create_object("object");

        for (auto &it: js.items()) {
            connector->__object_set_attribute(result, lcase(it.key()), __decode(it.value()));
        }
    } else if (js.is_array()) {
        result = connector->__create_array(0);

        for (auto &it: js) {
            result->__value_array->__elements.push_back(__decode(it));
        }
    }

    return result;
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

    __json_encode = connector->__register_function("json::encode");
    __json_decode = connector->__register_function("json::decode");
    __json_error = connector->__register_function("json::get_error");


    // Set function addresses boundary

    __min = __json_encode;
    __max = __json_error;   // DO NOT FORGET THIS!


    // Add constants

    __add_constants();
}

DataType* Module::__call(uint_fast16_t& func_id, AST* func, Object* obj, uint_fast32_t& caller_id) {
    DataType* result = new DataType(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __json_error) {
        result->__type = __TYPE_STRING__;
        result->__value_string = __json_error_string;

        return result;

    } else if (func_id == __json_encode) {
        if (params.size() < 1) connector->__error_message_param("json::encode");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("json::encode(): parameter #1 must be an object");

        int indent = -1;
        string indent_char = " ";

        if (params.size() > 1) {
            DataType* e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("json::encode(): parameter #2 must be a number");
            indent = (int) e->__value_double;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            DataType* e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_STRING__) connector->__error_message("json::encode(): parameter #3 must be a string");
            indent_char = e->__value_string;

            connector->__remove_garbage(params.at(2), e);
        }

        json js;
        js = __encode(d);

        result->__type = __TYPE_STRING__;
        result->__value_string = js.dump(indent, indent_char[0]);

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __json_decode) {
        if (params.size() < 1) connector->__error_message_param("json::decode");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("json::decode(): parameter #1 must be a string");

        json js;

        try {
            js = json::parse(d->__value_string);
        } catch(json::exception e) {
            __json_error_string = "json::decode(): ";
            __json_error_string += e.what();
            return result;
        }

        result = __decode(js);
        connector->__remove_garbage(params.at(0), d);
        
        return result;
    }

    return result;
}
