/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.1
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2022. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Functions and Classes
------------------------------------------------------------
*/

uint_fast16_t register_function(string name, uint_fast8_t type) {
    uint_fast16_t counter;

    if (type == __REG_CLASS__) {
        counter = __BUCKET_CLASS__ + __address_class++;
    } else if (type == __REG_UDEF_FUNCTION__) {
        counter = __BUCKET_UDEF_FUNCTION__ + __address_udef++;
    } else if (type == __REG_BUILT_IN_FUNCTION__) {
        counter = __BUCKET_BUILT_IN_FUNCTION__ + __address_builtin++;
    } else {
        counter = __BUCKET_EXTERNAL_FUNCTION__ + __address_external++;
    }

    __registered_functions[name] = counter;
    return counter;
}

DataType* get_function_value(AST_FunctionCall* func, uint_fast32_t& caller_id, bool need_return) {
    uint_fast16_t func_id;

    if (func->__address == 0) {
        func_id = __registered_functions[func->__identifier];
        if (func_id == 0) error_message("Undefined function " + func->__identifier + "()");
        func->__address = func_id;
    } else {
        func_id = func->__address;
    }

    if (func_id > __BUCKET_EXTERNAL_FUNCTION__) {
        Object* o = NULL;

        for (uint_fast16_t i = 0; i < __modules.size(); i++) {
            Module* m = __modules.at(i);
            if (func_id >= m->__min && func_id <= m->__max) return m->__call(func_id, func, o, caller_id);
        }

        return new DataType(__TYPE_NULL__);
    } else if (func_id > __BUCKET_BUILT_IN_FUNCTION__) {
        if (func_id >= standardIO::__min && func_id <= standardIO::__max) return standardIO::__call(func_id, func, caller_id);
        if (func_id >= core::__min && func_id <= core::__max) return core::__call(func_id, func, caller_id);

        return new DataType(__TYPE_NULL__);
    } else if (func_id > __BUCKET_UDEF_FUNCTION__) {
        Code* c = __udef_function_map[func_id];
        AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
        uint_fast32_t fc = __function_caller_id++;
        string sfc = to_string(fc);
        vector<AST*> declaration_params = f->__parameters;
        vector<uint_fast8_t> declaration_params_type = f->__parameters_type;
        vector<AST*> params = func->__parameters;
        __last_cur_i = __cur_i;
        uint_fast32_t default_caller_id = 1;
        bool stop_loop = false;
        bool stop_procedure = false;

        if (params.size() < f->__required_params) {
            error_message_params(func->__identifier, f->__required_params);
        }

        if (params.size() > declaration_params.size()) {
            error_message("Function " + func->__identifier + "() needs maximum " + to_string(declaration_params.size()) + " parameters");
        }

        for (uint_fast8_t i = 0; i < params.size(); i++) {
            string p = ((AST_Variable*) declaration_params.at(i))->__identifier;

            if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                __variables[sfc + p] = get_value(params.at(i), caller_id);
            } else {
                __variables[sfc + p] = core::create_ref(params.at(i), func->__identifier, i, caller_id);
            }
        }

        for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
            string p = ((AST_Variable*) declaration_params.at(i))->__identifier;
            
            if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                __variables[sfc + p] = get_value(f->__optional_parameters.at(i), default_caller_id);
            } else {
                __variables[sfc + p] = core::create_ref(f->__optional_parameters.at(i), func->__identifier, i, default_caller_id);
            }
        }

        walk(c->__index + 1, fc, stop_loop, stop_procedure);
        __last_cur_i = 0;

        if (need_return) {
            DataType* r = __variables[sfc + "__ret__"];

            if (r == NULL) {
                __cur_i = c->__index;
                error_message("Function " + func->__identifier + "() does not have return value");
            }


            // Garbage collector

            __variables.erase(sfc + "__ret__");

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(params.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(f->__optional_parameters.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (int i = 0; i < f->__local_variables.size(); i++) {
                string p = sfc + f->__local_variables.at(i);

                delete(__variables[p]);
                __variables.erase(p);
            }

            return r;
        } else {
            // Garbage collector

            __variables.erase(sfc + "__ret__");

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;

                remove_garbage(params.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(f->__optional_parameters.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (int i = 0; i < f->__local_variables.size(); i++) {
                string p = sfc + f->__local_variables.at(i);
  
                delete(__variables[p]);
                __variables.erase(p);
            }

            return new DataType(__TYPE_NULL__);
        }
    } else {
        Object* cm = __class_map[func_id];
        DataType* d = new DataType(__TYPE_OBJECT__);
        Object* o = new Object(cm->__name, __object_address++);

        o->__functions = cm->__functions;
        d->__value_object = o;

        for (const auto &attr: cm->__attributes) {
            o->__attributes[attr.first] = new DataType(__TYPE_NULL__);
        }

        if (cm->__constructor != 0) {
            Code* c = __udef_function_map[cm->__constructor];
            AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
            uint_fast32_t fc = __function_caller_id++;
            string sfc = to_string(fc);
            vector<AST*> declaration_params = f->__parameters;
            vector<uint_fast8_t> declaration_params_type = f->__parameters_type;
            vector<AST*> params = func->__parameters;
            __last_cur_i = __cur_i;
            uint_fast32_t default_caller_id = 1;
            bool stop_loop = false;
            bool stop_procedure = false;

            if (params.size() < f->__required_params) {
                error_message_params(cm->__name + "::construct", f->__required_params);
            }

            if (params.size() > declaration_params.size()) {
                error_message("Function " + cm->__name + "::construct() needs maximum " + to_string(declaration_params.size()) + " parameters");
            }

            __variables[sfc + "this"] = d;

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = ((AST_Variable*) declaration_params.at(i))->__identifier;

                if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                    __variables[sfc + p] = get_value(params.at(i), caller_id);
                } else {
                    __variables[sfc + p] = core::create_ref(params.at(i), cm->__name + "::construct", i, caller_id);
                }
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                    __variables[sfc + p] = get_value(f->__optional_parameters.at(i), default_caller_id);
                } else {
                    __variables[sfc + p] = core::create_ref(f->__optional_parameters.at(i), cm->__name + "::construct", i, default_caller_id);
                }
            }

            walk(c->__index + 1, fc, stop_loop, stop_procedure);
            __last_cur_i = 0;


            // Garbage collector

            __variables.erase(sfc + "this");

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(params.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(f->__optional_parameters.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (int i = 0; i < f->__local_variables.size(); i++) {
                string p = sfc + f->__local_variables.at(i);

                delete(__variables[p]);
                __variables.erase(p);
            }
        }

        return d;
    }
}

DataType* get_object_function_value(AST_ObjectFunctionCall* func, uint_fast32_t& caller_id, bool need_return) {
    uint_fast16_t func_id = 0;
    Object* fo = get_pure_object_value(func->__object, caller_id);

    func_id = fo->__functions[func->__identifier];
    if (func_id == 0) error_message("Function " + func->__identifier + "() is not declared in class " + fo->__name);

    if (func_id > __BUCKET_EXTERNAL_FUNCTION__) {
        for (uint_fast16_t i = 0; i < __modules.size(); i++) {
            Module* m = __modules.at(i);
            if (func_id >= m->__min && func_id <= m->__max) return m->__call(func_id, func, fo, caller_id);
        }

        return new DataType(__TYPE_NULL__);
    } else if (func_id > __BUCKET_BUILT_IN_FUNCTION__) {
        // TODO: Call built-in

        return new DataType(__TYPE_NULL__);
    } else if (func_id > __BUCKET_UDEF_FUNCTION__) {
        Code* c = __udef_function_map[func_id];
        AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
        uint_fast32_t fc = __function_caller_id++;
        string sfc = to_string(fc);
        vector<AST*> declaration_params = f->__parameters;
        vector<uint_fast8_t> declaration_params_type = f->__parameters_type;
        vector<AST*> params = func->__parameters;
        __last_cur_i = __cur_i;
        uint_fast32_t default_caller_id = 1;
        bool stop_loop = false;
        bool stop_procedure = false;

        if (params.size() < f->__required_params) {
            error_message_params(fo->__name + "::" + func->__identifier, f->__required_params);
        }

        if (params.size() > declaration_params.size()) {
            error_message("Function " + fo->__name + "::" + func->__identifier + "() needs maximum " + to_string(declaration_params.size()) + " parameters");
        }

        DataType* dfo = new DataType(__TYPE_OBJECT__);
        dfo->__value_object = fo;
        __variables[sfc + "this"] = dfo;

        for (uint_fast8_t i = 0; i < params.size(); i++) {
            string p = ((AST_Variable*) declaration_params.at(i))->__identifier;

            if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                __variables[sfc + p] = get_value(params.at(i), caller_id);
            } else {
                __variables[sfc + p] = core::create_ref(params.at(i), fo->__name + "::" + func->__identifier, i, caller_id);
            }
        }

        for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
            string p = ((AST_Variable*) declaration_params.at(i))->__identifier;
            
            if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                __variables[sfc + p] = get_value(f->__optional_parameters.at(i), default_caller_id);
            } else {
                __variables[sfc + p] = core::create_ref(f->__optional_parameters.at(i), fo->__name + "::" + func->__identifier, i, default_caller_id);
            }
        }

        walk(c->__index + 1, fc, stop_loop, stop_procedure);

        __last_cur_i = 0;
        delete(dfo);

        if (need_return) {
            DataType* r = __variables[sfc + "__ret__"];

            if (r == NULL) {
                __cur_i = c->__index;
                error_message("Function " + fo->__name + "::" + func->__identifier + "() does not have return value");
            }


            // Garbage collector

            __variables.erase(sfc + "this");
            __variables.erase(sfc + "__ret__");

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(params.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(f->__optional_parameters.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (int i = 0; i < f->__local_variables.size(); i++) {
                string p = sfc + f->__local_variables.at(i);

                delete(__variables[p]);
                __variables.erase(p);
            }

            return r;
        } else {
            // Garbage collector

            __variables.erase(sfc + "this");
            __variables.erase(sfc + "__ret__");

            for (uint_fast8_t i = 0; i < params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(params.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (uint_fast8_t i = params.size(); i < declaration_params.size(); i++) {
                string p = sfc + ((AST_Variable*) declaration_params.at(i))->__identifier;
                
                remove_garbage(f->__optional_parameters.at(i), __variables[p]);
                __variables.erase(p);
            }

            for (int i = 0; i < f->__local_variables.size(); i++) {
                string p = sfc + f->__local_variables.at(i);
                
                delete(__variables[p]);
                __variables.erase(p);
            }

            return new DataType(__TYPE_NULL__);
        }
    } else {
        return new DataType(__TYPE_NULL__);
    }
}

void call_function(AST* func, uint_fast32_t& caller_id) {
    if (func->__type == __AST_FUNCTION_CALL__) {
        DataType* d = get_function_value((AST_FunctionCall*) func, caller_id, false);
        delete(d);
    } else {
        DataType* d = get_object_function_value((AST_ObjectFunctionCall*) func, caller_id, false);
        delete(d);
    }
}

void remove_garbage(AST* param, DataType* d_param) {
    if (param->__type == __AST_FUNCTION_CALL__ || param->__type == __AST_OBJECT_FUNCTION_CALL__ ||
        param->__type == __AST_BINARY_EXPRESSION__ || param->__type == __AST_ARRAY_NOTATION__ ||
        param->__type == __AST_OBJECT_NOTATION__) {
        delete(d_param);
    }
}

void parse_function_class() {
    uint_fast16_t count = __functions_classes.size();
    Object* cur_class = NULL;
    unordered_map<string, uint_fast8_t> classes;
    AST_FunctionCall* cur_func = NULL;

    for (uint_fast16_t i = 0; i < count; i++) {
        Code* c = __functions_classes.at(i);
        __cur_i = c->__index;

        if (c->__header == __H_CLASS__) {
            AST_Parameter* param = ((AST_Parameter*) c->__body);
            vector<AST*> params = param->__parameters;
            string class_name = ((AST_Variable*) params.at(0))->__identifier;

            if (cur_class != NULL) {
                error_message("Could not place a class inside a class");
            }

            if (classes.find(class_name) != classes.end()) {
                error_message("Class '" + class_name + "' is already declared");
            }

            cur_class = new Object(class_name, 0);
            string extends = "";

            for (int j = 1; j < params.size(); j++) {
                extends += ((AST_Variable*) params.at(j))->__identifier + ",";
            }

            uint_fast16_t r = register_function(class_name, __REG_CLASS__);
            // cur_class->__blue_print_inherited = extends;
            cur_class->__constructor = 0;
            __class_map[r] = cur_class;

            classes[class_name] = 1;
        } else if (c->__header == __H_END_CLASS__) {
            cur_class = NULL;
        } else if (c->__header == __H_FIELD__) {
            if (cur_class == NULL) error_message("Field declaration is only permitted inside a class block");
            if (cur_class->__functions.size() > 0) error_message("Field declaration must be placed at the top of class block");

            AST_Parameter* param = ((AST_Parameter*) c->__body);
            vector<AST*> params = param->__parameters;

            for (int j = 0; j < params.size(); j++) {
                cur_class->__attributes[((AST_Variable*) params.at(j))->__identifier] = new DataType(__TYPE_DOUBLE__);
            }
        } else if (c->__header == __H_FUNCTION__) {
            AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
            cur_func = f;
            string func_name = f->__identifier;

            if (cur_class == NULL) {
                uint_fast16_t r = register_function(func_name, __REG_UDEF_FUNCTION__);
                __udef_function_map[r] = c;

                if (func_name.length() > 6 && right(func_name, 6) == "::init") {
                    AST_FunctionCall* initf = new AST_FunctionCall(func_name);
                    initf->__address = r;

                    __init_functions.push_back(initf);
                }
            } else {
                string fname = cur_class->__name + "::" + func_name;
                uint_fast16_t r = register_function(fname, __REG_UDEF_FUNCTION__);
                __udef_function_map[r] = c;

                cur_class->__functions[func_name] = r;

                if (func_name == "construct") {
                    cur_class->__constructor = r;
                }
            }
        } else if (c->__header == __H_VARIABLE_ASSIGNMENT__) {
            if (cur_func != NULL) {
                AST_Variable* v = ((AST_Variable*) c->__body);
                cur_func->__local_variables.push_back(v->__identifier);
            }
        } else if (c->__header == __H_VAR__) {
            if (cur_func != NULL) {
                AST_Parameter* v = ((AST_Parameter*) c->__body);

                for (uint_fast8_t j = 0; j < v->__parameters.size(); j++) {
                    cur_func->__local_variables.push_back(((AST_Variable*) v->__parameters.at(j))->__identifier);
                }
            }
        } else if (c->__header == __H_FOR__) {
            if (cur_func != NULL) {
                AST_Parameter* v = ((AST_Parameter*) c->__body);
                cur_func->__local_variables.push_back(((AST_Variable*) v->__parameters.at(0))->__identifier);
            }
        }
    }
}
