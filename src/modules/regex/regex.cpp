/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.1
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2021. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - Regular Expression (Regex)
-------------------------------------------------------------------
 Compilation Instruction:
  - Please see ./compile.sh
-------------------------------------------------------------------
*/

#include <regex>
#include "module.h"

Connector* connector;
uint_fast16_t __regex_match, __regex_search, __regex_replace;

extern "C" Module* create_module() {
    return new Module();
}

extern "C" void destroy_module(Module* object) {
    delete object;
}

void Module::__init(Connector* c) {
    connector = c;


    // Register functions

    __regex_match = connector->__register_function("regex_match");
    __regex_search = connector->__register_function("regex_search");
    __regex_replace = connector->__register_function("regex_replace");


    // Set function addresses boundary

    __min = __regex_match;
    __max = __regex_replace;   // DO NOT FORGET THIS!
}

DataType* Module::__call(uint_fast16_t& func_id, AST* func, Object* obj, uint_fast32_t& caller_id) {
    DataType* result = new DataType(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __regex_match) {
        if (params.size() < 2) connector->__error_message_params("regex_match", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("regex_match(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("regex_match(): parameter #2 must be a string");
        bool case_sensitive = false;
        
        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("regex_match(): parameter #3 must be a boolean");
            case_sensitive = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }

        result->__type = __TYPE_BOOL__;

        if (case_sensitive) {
            regex r(d->__value_string);
            result->__value_bool = regex_match(e->__value_string, r);
        } else {
            regex r(d->__value_string, regex_constants::icase);
            result->__value_bool = regex_match(e->__value_string, r);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __regex_search) {
        if (params.size() < 2) connector->__error_message_params("regex_search", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("regex_search(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("regex_search(): parameter #2 must be a string");
        bool case_sensitive = false;
        
        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("regex_search(): parameter #3 must be a boolean");
            case_sensitive = f->__value_bool;
            
            connector->__remove_garbage(params.at(2), f);
        }

        DataType* arr = connector->__create_array(0);

        if (case_sensitive) {
            string str = e->__value_string;
            regex r(d->__value_string);
            sregex_iterator pos(str.cbegin(), str.cend(), r);
            sregex_iterator end;
            int i = 0;

            for (; pos != end; pos++) {
                DataType* rs = connector->__create_object("regex");
                
                DataType* rsv = new DataType(__TYPE_STRING__);
                rsv->__value_string = pos->str(0);
                connector->__object_set_attribute(rs, "value", rsv);

                DataType* rsp = new DataType(__TYPE_DOUBLE__);
                rsp->__value_double = pos->position(0);
                connector->__object_set_attribute(rs, "position", rsp);

                DataType* garr = connector->__create_array(0);
                int k = 0;

                for (int j = 1; j < pos->size(); j++) {
                    DataType* grs = connector->__create_object("regex_group");
                
                    DataType* grsv = new DataType(__TYPE_STRING__);
                    grsv->__value_string = pos->str(j);
                    connector->__object_set_attribute(grs, "value", grsv);

                    DataType* grsp = new DataType(__TYPE_DOUBLE__);
                    grsp->__value_double = pos->position(j);
                    connector->__object_set_attribute(grs, "position", grsp);

                    garr->__value_array->__elements.push_back(grs);
                    k++;
                }

                connector->__object_set_attribute(rs, "group", garr);

                arr->__value_array->__elements.push_back(rs);
                i++;
            }
        } else {
            string str = e->__value_string;
            regex r(d->__value_string, regex_constants::icase);
            sregex_iterator pos(str.cbegin(), str.cend(), r);
            sregex_iterator end;
            int i = 0;

            for (; pos != end; pos++) {
                DataType* rs = connector->__create_object("regex");
                
                DataType* rsv = new DataType(__TYPE_STRING__);
                rsv->__value_string = pos->str(0);
                connector->__object_set_attribute(rs, "value", rsv);

                DataType* rsp = new DataType(__TYPE_DOUBLE__);
                rsp->__value_double = pos->position(0);
                connector->__object_set_attribute(rs, "position", rsp);

                DataType* garr = connector->__create_array(0);
                int k = 0;

                for (int j = 1; j < pos->size(); j++) {
                    DataType* grs = connector->__create_object("regex_group");
                
                    DataType* grsv = new DataType(__TYPE_STRING__);
                    grsv->__value_string = pos->str(j);
                    connector->__object_set_attribute(grs, "value", grsv);

                    DataType* grsp = new DataType(__TYPE_DOUBLE__);
                    grsp->__value_double = pos->position(j);
                    connector->__object_set_attribute(grs, "position", grsp);

                    garr->__value_array->__elements.push_back(grs);
                    k++;
                }

                connector->__object_set_attribute(rs, "group", garr);

                arr->__value_array->__elements.push_back(rs);
                i++;
            }
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return arr;
    } else if (func_id == __regex_replace) {
        if (params.size() < 3) connector->__error_message_params("regex_replace", 3);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        DataType* g = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("regex_replace(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("regex_replace(): parameter #2 must be a string");
        if (g->__type != __TYPE_STRING__) connector->__error_message("regex_replace(): parameter #3 must be a string");
        bool case_sensitive = false;
        
        if (params.size() > 3) {
            DataType* f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("regex_replace(): parameter #4 must be a boolean");
            case_sensitive = f->__value_bool;

            connector->__remove_garbage(params.at(3), f);
        }

        result->__type = __TYPE_STRING__;

        if (case_sensitive) {
            regex r(d->__value_string);
            result->__value_string = regex_replace(e->__value_string, r, g->__value_string);
        } else {
            regex r(d->__value_string, regex_constants::icase);
            result->__value_string = regex_replace(e->__value_string, r, g->__value_string);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), g);

        return result;
    }

    return result;
}
