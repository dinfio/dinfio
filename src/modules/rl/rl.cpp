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
 Module - Advanced Readline
-------------------------------------------------------------------
 Compilation Instruction:
  - Please see ./compile.sh
-------------------------------------------------------------------
*/

#include "linenoise.hpp"
#include "module.h"

Connector* connector;
uint_fast16_t __rl, __rl_loadhistory, __rl_addhistory, __rl_savehistory;
uint_fast16_t __rl_setmaxhistory, __rl_setcompletion, __rl_addcompletion, __rl_clearcompletion;

vector<string> __completion_list;

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

string rtrim(string s) {
    char t = ' ';
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

string ltrim(string s) {
    char t = ' ';
    s.erase(0, s.find_first_not_of(t));
    return s;
}

string trim(string s) {
    return ltrim(rtrim(s));
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

    __rl = connector->__register_function("rl");
    __rl_loadhistory = connector->__register_function("rl_loadhistory");
    __rl_addhistory = connector->__register_function("rl_addhistory");
    __rl_savehistory = connector->__register_function("rl_savehistory");
    __rl_setmaxhistory = connector->__register_function("rl_setmaxhistory");
    __rl_setcompletion = connector->__register_function("rl_setcompletion");
    __rl_addcompletion = connector->__register_function("rl_addcompletion");
    __rl_clearcompletion = connector->__register_function("rl_clearcompletion");


    // Set function addresses boundary

    __min = __rl;
    __max = __rl_clearcompletion;   // DO NOT FORGET THIS!


    // Setup

    linenoise::SetMultiLine(true);
    linenoise::SetHistoryMaxLen(1000);

    linenoise::SetCompletionCallback([](const char* edit_buffer, std::vector<std::string>& completions) {
        string buffer = edit_buffer;

        for (int i = 0; i < __completion_list.size(); i++) {
            string c = __completion_list.at(i);

            if (c.substr(0, buffer.length()) == trim(buffer)) {
                completions.push_back(c);
            }
        }
    });
}

DataType* Module::__call(uint_fast16_t& func_id, AST* func, Object* obj, uint_fast32_t& caller_id) {
    DataType* result = new DataType(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __rl) {
        string prompt = "";
        string r = "";
        bool quit;

        if (params.size() > 0) {
            DataType* d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_STRING__) connector->__error_message("rl(): parameter #1 must be a string");
            prompt = d->__value_string;

            connector->__remove_garbage(params.at(0), d);
        }

        quit = linenoise::Readline(prompt.c_str(), r);

        if (quit) {
            return result;
        } else {
            result->__type = __TYPE_STRING__;
            result->__value_string = r;
        }

        return result;
    } else if (func_id == __rl_addhistory) {
        if (params.size() < 1) connector->__error_message_param("rl_addhistory");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("rl_addhistory(): parameter #1 must be a string");

        result->__type = __TYPE_BOOL__;
        result->__value_bool = linenoise::AddHistory(d->__value_string.c_str());

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __rl_loadhistory) {
        if (params.size() < 1) connector->__error_message_param("rl_loadhistory");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("rl_loadhistory(): parameter #1 must be a string");

        result->__type = __TYPE_BOOL__;
        result->__value_bool = linenoise::LoadHistory(d->__value_string.c_str());

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __rl_savehistory) {
        if (params.size() < 1) connector->__error_message_param("rl_savehistory");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("rl_savehistory(): parameter #1 must be a string");

        result->__type = __TYPE_BOOL__;
        result->__value_bool = linenoise::SaveHistory(d->__value_string.c_str());

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __rl_clearcompletion) {
        __completion_list.clear();
        
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        return result;
    } else if (func_id == __rl_addcompletion) {
        if (params.size() < 1) connector->__error_message_param("rl_addcompletion");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("rl_addcompletion(): parameter #1 must be a string");

        __completion_list.push_back(d->__value_string);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __rl_setcompletion) {
        if (params.size() < 1) connector->__error_message_param("rl_setcompletion");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("rl_setcompletion(): parameter #1 must be an array");

        vector<DataType*> arr = d->__value_array->__elements;
        __completion_list.clear();

        for (int i = 0; i < arr.size(); i++) {
            string s = arr.at(i)->__value_string;
            __completion_list.push_back(s);
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    }

    return result;
}
