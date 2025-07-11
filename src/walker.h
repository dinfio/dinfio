/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2025. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 AST Walker
------------------------------------------------------------
*/

void walk(uint_fast32_t start, uint_fast32_t& caller_id, bool& stop_loop, bool& stop_procedure) {
    for (uint_fast32_t i = start; i < __n_codes; i++) {
        if (stop_loop || stop_procedure) return;

        Code* c = __codes[i];
        __cur_i = i;

        if (c->__header == __H_VARIABLE_ASSIGNMENT__) {
            assignment(c->__body, c->__body2, caller_id);
            
        } else if (c->__header == __H_IF__) {
            branch_if(c->__body, i, c->__endclause, c->__endclause2, false, caller_id, stop_loop, stop_procedure);
            return;
        } else if (c->__header == __H_END_IF__ || c->__header == __H_ELSE__ || c->__header == __H_ELSE_IF__) {
            return;

        } else if (c->__header == __H_FOR__) {
            loop_for(c->__body, i, c->__additional_header, c->__endclause, caller_id, stop_loop, stop_procedure);
            return;
        } else if (c->__header == __H_END_FOR__) {
            return;
        
        } else if (c->__header == __H_WHILE__) {
            loop_while(c->__body, i, c->__endclause, caller_id, stop_loop, stop_procedure);
            return;
        } else if (c->__header == __H_END_WHILE__) {
            return;
            
        } else if (c->__header == __H_PROCEDURE_CALL__) {
            call_function(c->__body, caller_id);
        
        } else if (c->__header == __H_RETURN__) {
            assignment(c->__body, c->__body2, caller_id);

            stop_procedure = true;
            return;
        } else if (c->__header == __H_YIELD__) {
            assignment(c->__body, c->__body2, caller_id);
        
        } else if (c->__header == __H_VAR__) {
            declare_variables(c->__body, c->__body2, caller_id, true);
        } else if (c->__header == __H_GLOBAL__) {
            declare_variables(c->__body, c->__body2, caller_id, false);
        } else if (c->__header == __H_CONST__) {
            declare_constants(c->__body, c->__body2, caller_id);
        
        } else if (c->__header == __H_EXIT_LOOP__) {
            stop_loop = true;
            return;
        } else if (c->__header == __H_STOP__ || c->__header == __H_RETURN_VOID__) {
            stop_procedure = true;
            return;
        } else if (c->__header == __H_FUNCTION__) {
            stop_procedure = true;
            return;
        } else if (c->__header == __H_CLASS__) {
            stop_procedure = true;
            return;
        } else if (c->__header == __H_END_CLASS__) {
            stop_procedure = true;
            return;
        }
    }
}

void assignment(AST* var, AST* value, uint_fast32_t& caller_id) {
    uint_fast8_t type = var->__type;

    if (type == __AST_VARIABLE__) {
        AST_Variable* e = (AST_Variable*) var;
        gc<DataType> val = get_value(value, caller_id);
        
        if (e->__caller_id == caller_id) {
            if (val->__type == __TYPE_DOUBLE__) {
                e->__variable_holder->__type = __TYPE_DOUBLE__;
                e->__variable_holder->__value_double = val->__value_double;
            } else if (val->__type == __TYPE_BOOL__) {
                e->__variable_holder->__type = __TYPE_BOOL__;
                e->__variable_holder->__value_bool = val->__value_bool;
            } else if (val->__type == __TYPE_STRING__) {
                e->__variable_holder->__type = __TYPE_STRING__;
                e->__variable_holder->__value_string = val->__value_string;
            } else if (val->__type == __TYPE_ARRAY__) {
                e->__variable_holder->__type = __TYPE_ARRAY__;
                e->__variable_holder->__value_array = val->__value_array;
            } else if (val->__type == __TYPE_OBJECT__) {
                e->__variable_holder->__type = __TYPE_OBJECT__;
                e->__variable_holder->__value_object = val->__value_object;
            } else {
                e->__variable_holder->__type = __TYPE_NULL__;
            }
        } else {
            string c = to_string(caller_id);

            if (__variables.count(c + e->__identifier) == 0) {
                c = "1";
            }

            if (__variables.count(c + e->__identifier) != 0) {
                e->__caller_id = caller_id;
                e->__variable_holder = __variables[c + e->__identifier];

                if (e->__variable_holder->__is_constant) error_message("Invalid assignment to constant '" + e->__identifier + "'");

                if (e->__variable_holder->__type == __TYPE_ARRAY__ && val->__type != __TYPE_ARRAY__) e->__variable_holder->__value_array = NULL;
                if (e->__variable_holder->__type == __TYPE_OBJECT__ && val->__type != __TYPE_OBJECT__) e->__variable_holder->__value_object = NULL;

                if (val->__type == __TYPE_DOUBLE__) {
                    e->__variable_holder->__type = __TYPE_DOUBLE__;
                    e->__variable_holder->__value_double = val->__value_double;
                }
                if (val->__type == __TYPE_BOOL__) {
                    e->__variable_holder->__type = __TYPE_BOOL__;
                    e->__variable_holder->__value_bool = val->__value_bool;
                }
                if (val->__type == __TYPE_STRING__) {
                    e->__variable_holder->__type = __TYPE_STRING__;
                    e->__variable_holder->__value_string = val->__value_string;
                }
                if (val->__type == __TYPE_ARRAY__) {
                    e->__variable_holder->__type = __TYPE_ARRAY__;
                    e->__variable_holder->__value_array = val->__value_array;
                }
                if (val->__type == __TYPE_OBJECT__) {
                    e->__variable_holder->__type = __TYPE_OBJECT__;
                    e->__variable_holder->__value_object = val->__value_object;
                }
                if (val->__type == __TYPE_NULL__) {
                    e->__variable_holder->__type = __TYPE_NULL__;
                }
            } else {
                string c = to_string(caller_id);
                
                if (val->__type == __TYPE_DOUBLE__) {
                    gc<DataType> f = new_gc<DataType>(__TYPE_DOUBLE__);
                    f->__value_double = val->__value_double;

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                } else if (val->__type == __TYPE_BOOL__) {
                    gc<DataType> f = new_gc<DataType>(__TYPE_BOOL__);
                    f->__value_bool = val->__value_bool;

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                } else if (val->__type == __TYPE_STRING__) {
                    gc<DataType> f = new_gc<DataType>(__TYPE_STRING__);
                    f->__value_string = val->__value_string;

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                } else if (val->__type == __TYPE_ARRAY__) {
                    gc<DataType> f = new_gc<DataType>(__TYPE_ARRAY__);
                    f->__value_array = val->__value_array;

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                } else  if (val->__type == __TYPE_OBJECT__) {
                    gc<DataType> f = new_gc<DataType>(__TYPE_OBJECT__);
                    f->__value_object = val->__value_object;

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                } else {
                    gc<DataType> f = new_gc<DataType>(__TYPE_NULL__);

                    __variables[c + e->__identifier] = f;
                    e->__caller_id = caller_id;
                    e->__variable_holder = f;
                }
            }
        }
    } else if (type == __AST_ARRAY__) {
        AST_Array* e = (AST_Array*) var;
        gc<DataType> val = get_value(value, caller_id);

        if (e->__caller_id == caller_id) {
            set_array_value(e->__variable_holder, e, val, caller_id);
        } else {
            string c = to_string(caller_id);

            if (__variables.count(c + e->__identifier) == 0) {
                c = "1";
            }

            if (__variables.count(c + e->__identifier) != 0) {
                e->__caller_id = caller_id;
                e->__variable_holder = __variables[c + e->__identifier];
                
                set_array_value(e->__variable_holder, e, val, caller_id);
            } else {
                error_message("Variable " + e->__identifier + " is not an array");
            }
        }
    } else if (type == __AST_OBJECT__) {
        AST_Object* e = (AST_Object*) var;
        gc<DataType> val = get_value(value, caller_id);

        if (e->__caller_id == caller_id) {
            set_object_value(e->__variable_holder, e, val, caller_id);
        } else {
            if (e->__array_holder == NULL) {
                string c = to_string(caller_id);

                if (__variables.count(c + e->__identifier) == 0) {
                    c = "1";
                }

                if (__variables.count(c + e->__identifier) != 0) {
                    e->__caller_id = caller_id;
                    e->__variable_holder = __variables[c + e->__identifier];
                    
                    set_object_value(e->__variable_holder, e, val, caller_id);
                } else {
                    error_message("Variable " + e->__identifier + " is not an object");
                }
            } else {
                set_object_value(e->__variable_holder, e, val, caller_id);
            }
        }
    } else if (type == __AST_ARRAY_NOTATION__) {
        vector<AST*> arr = ((AST_ArrayNotation*) var)->__elements;
        gc<DataType> val = get_value(value, caller_id);

        if (val->__type != __TYPE_ARRAY__) {
            for (int i = 0; i < arr.size(); i++) {
                AST_Variable* e = (AST_Variable*) arr.at(i);
                assignment(e, value, caller_id);
            }
        } else {
            for (int i = 0; i < arr.size(); i++) {
                AST_Variable* e = (AST_Variable*) arr.at(i);

                if (val->__value_array->__elements.size() <= i) error_message("Index " + to_string(i) + " of the right side array is undefined");
                gc<DataType> ival = val->__value_array->__elements[i];
                
                AST_Value* v = new AST_Value(ival);
                assignment(e, v, caller_id);
                delete v;
            }
        }
    }
}
