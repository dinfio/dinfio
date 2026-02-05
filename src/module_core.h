/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2026. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Module - Core
------------------------------------------------------------
*/

namespace core {
    uint_fast16_t __array, __array2d, __size, __append, __clear, __pop, __declare, __array_random;
    uint_fast16_t __object, __is_nothing, __extend, __equal, __name, __attributes, __address, __inherits;
    uint_fast16_t __type, __exit, __iif, __total_vars;
    uint_fast16_t __platform, __platform_linux, __platform_mac, __platform_windows;
    uint_fast16_t __execute;
    uint_fast16_t __ref, __ref_call, __ref_eval;
    uint_fast16_t __var_exists, __error;
    uint_fast16_t __caller_file, __get_value;
    uint_fast16_t __attribute_set, __attribute_get, __attribute_exists;
    uint_fast16_t __bit_not, __bit_and, __bit_or, __bit_xor, __bit_ls, __bit_rs;
    uint_fast16_t __register_event_loop, __set_on_error_callback;
    uint_fast16_t __assert, __range;

    class RefHolder: public Base {
    public:
        AST* __func;
        vector<AST*> __original_params;
        uint_fast32_t __caller_id;

        RefHolder(AST* func, uint_fast32_t caller_id) {
            __func = func;
            __caller_id = caller_id;
        }

        void call(uint_fast32_t caller_id) {
            call_function(__func, caller_id);
        }

        gc<DataType> eval(uint_fast32_t caller_id) {
            return get_function_value((AST_FunctionCall*) __func, caller_id, true);
        }

        ~RefHolder() {
            if (__func != NULL) delete __func;
            __original_params.clear();
        }
    };

    void __init() {
        __array = register_function("array", __REG_BUILT_IN_FUNCTION__);
        __array2d = register_function("array2d", __REG_BUILT_IN_FUNCTION__);
        __object = register_function("object", __REG_BUILT_IN_FUNCTION__);
        __size = register_function("size", __REG_BUILT_IN_FUNCTION__);
        __append = register_function("append", __REG_BUILT_IN_FUNCTION__);
        __clear = register_function("clear", __REG_BUILT_IN_FUNCTION__);
        __pop = register_function("pop", __REG_BUILT_IN_FUNCTION__);
        __is_nothing = register_function("is_nothing", __REG_BUILT_IN_FUNCTION__);
        __extend = register_function("extend", __REG_BUILT_IN_FUNCTION__);
        __equal = register_function("equal", __REG_BUILT_IN_FUNCTION__);
        __name = register_function("object_name", __REG_BUILT_IN_FUNCTION__);
        __attributes = register_function("attributes", __REG_BUILT_IN_FUNCTION__);
        __address = register_function("address", __REG_BUILT_IN_FUNCTION__);
        __inherits = register_function("inherits", __REG_BUILT_IN_FUNCTION__);
        __type = register_function("type", __REG_BUILT_IN_FUNCTION__);
        __exit = register_function("exit", __REG_BUILT_IN_FUNCTION__);
        __iif = register_function("iif", __REG_BUILT_IN_FUNCTION__);
        __var_exists = register_function("var_exists", __REG_BUILT_IN_FUNCTION__);
        __total_vars = register_function("__vars", __REG_BUILT_IN_FUNCTION__);
        __platform = register_function("platform", __REG_BUILT_IN_FUNCTION__);
        __platform_linux = register_function("platform_linux", __REG_BUILT_IN_FUNCTION__);
        __platform_mac = register_function("platform_mac", __REG_BUILT_IN_FUNCTION__);
        __platform_windows = register_function("platform_windows", __REG_BUILT_IN_FUNCTION__);
        __execute = register_function("execute", __REG_BUILT_IN_FUNCTION__);
        __declare = register_function("declare", __REG_BUILT_IN_FUNCTION__);
        __array_random = register_function("array_random", __REG_BUILT_IN_FUNCTION__);
        __ref = register_function("ref", __REG_BUILT_IN_FUNCTION__);
        __ref_call = register_function("call", __REG_BUILT_IN_FUNCTION__);
        __ref_eval = register_function("eval", __REG_BUILT_IN_FUNCTION__);
        __error = register_function("error", __REG_BUILT_IN_FUNCTION__);
        __caller_file = register_function("caller_file", __REG_BUILT_IN_FUNCTION__);
        __get_value = register_function("get_value", __REG_BUILT_IN_FUNCTION__);
        __attribute_get = register_function("attribute_get", __REG_BUILT_IN_FUNCTION__);
        __attribute_set = register_function("attribute_set", __REG_BUILT_IN_FUNCTION__);
        __attribute_exists = register_function("attribute_exists", __REG_BUILT_IN_FUNCTION__);

        __bit_not = register_function("bnot", __REG_BUILT_IN_FUNCTION__);
        __bit_and = register_function("band", __REG_BUILT_IN_FUNCTION__);
        __bit_or = register_function("bor", __REG_BUILT_IN_FUNCTION__);
        __bit_xor = register_function("bxor", __REG_BUILT_IN_FUNCTION__);
        __bit_ls = register_function("bls", __REG_BUILT_IN_FUNCTION__);
        __bit_rs = register_function("brs", __REG_BUILT_IN_FUNCTION__);

        __register_event_loop = register_function("register_event_loop", __REG_BUILT_IN_FUNCTION__);
        __set_on_error_callback = register_function("set_on_error_callback", __REG_BUILT_IN_FUNCTION__);

        __assert = register_function("assert", __REG_BUILT_IN_FUNCTION__);
        __range = register_function("range", __REG_BUILT_IN_FUNCTION__);
        
        __min = __array;
        __max = __range;   // DO NOT FORGET THIS!
    }

    gc<DataType> __call(uint_fast16_t& func, AST* ast_func, uint_fast32_t& caller_id) {
        gc<DataType> result = new_gc<DataType>(__TYPE_NULL__);
        vector<AST*> params = ((AST_FunctionCall*) ast_func)->__parameters;

        if (func == __array) {
            if (params.size() > 0) {
                gc<DataType> d = get_value(params.at(0), caller_id);
                gc<DataType> r = core::create_array(d->__value_double);

                return r;
            } else {
                return core::create_array(0);
            }
        } else if (func == __array2d) {
            if (params.size() < 2) error_message_params("array2d", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("array2d(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("array2d(): parameter #2 must be a number");

            gc<DataType> r = core::create_array_2d(d->__value_double, e->__value_double);
            
            return r;
        } else if (func == __object) {
            if (params.size() > 0) {
                gc<DataType> d = get_value(params.at(0), caller_id);
                gc<DataType> r = core::create_empty_object(d->__value_string);

                return r;
            } else {
                return core::create_empty_object("object");
            }
        } else if (func == __size) {
            if (params.size() < 1) error_message_param("size");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_ARRAY__) error_message("size(): parameter #1 must be an array");

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = d->__value_array->__elements.size();

            return result;
        } else if (func == __append) {
            if (params.size() < 2) error_message_params("append", 2);
            gc<DataType> f = get_value(params.at(0), caller_id);
            gc<DataType> d = get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_ARRAY__) error_message("append(): parameter #1 must be an array");

            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            } else {
                e = new_gc<DataType>(__TYPE_NULL__);
            }

            f->__value_array->__elements.push_back(e);

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __clear) {
            if (params.size() < 1) error_message_param("clear");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_ARRAY__) error_message("clear(): parameter #1 must be an array");

            d->__value_array->__elements.clear();

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __pop) {
            if (params.size() < 1) error_message_param("pop");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_ARRAY__) error_message("pop(): parameter #1 must be an array");

            // delete(d->__value_array->__elements[0]);
            d->__value_array->__elements.erase(d->__value_array->__elements.begin());

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __is_nothing) {
            if (params.size() < 1) error_message_param("is_nothing");
            gc<DataType> d = get_value(params.at(0), caller_id);

            result->__type = __TYPE_BOOL__;
            result->__value_bool = (d->__type == __TYPE_NULL__) ? true : false;

            return result;
        } else if (func == __extend) {
            if (params.size() < 2) error_message_params("extend", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("extend(): parameter #1 must be an object");
            if (b->__type != __TYPE_OBJECT__) error_message("extend(): parameter #2 must be an object");

            a->__value_object->__inherited += b->__value_object->__name + " ";
            a->__value_object->__holder_pointer = b->__value_object->__holder_pointer;

            for (const auto &attr: b->__value_object->__attributes) {
                a->__value_object->__attributes[attr.first] = b->__value_object->__attributes[attr.first];
            }

            for (const auto &func: b->__value_object->__functions) {
                if (a->__value_object->__functions.find(func.first) == a->__value_object->__functions.end()) a->__value_object->__functions[func.first] = b->__value_object->__functions[func.first];
            }

            b->__value_object->__has_been_inherited = true;
            a->__value_object->__attributes[b->__value_object->__name] = b;

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __equal) {
            if (params.size() < 2) error_message_params("equal", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            if (a->__type != __TYPE_OBJECT__ && a->__type != __TYPE_ARRAY__) error_message("equal(): parameter #1 must be a reference");
            if (b->__type != __TYPE_OBJECT__ && b->__type != __TYPE_ARRAY__) error_message("equal(): parameter #2 must be a reference");

            uint_fast32_t addr_a, addr_b;

            if (a->__type == __TYPE_ARRAY__) addr_a = ((gc<Array>) a->__value_array)->__address;
            if (b->__type == __TYPE_ARRAY__) addr_b = ((gc<Array>) b->__value_array)->__address;
            if (a->__type == __TYPE_OBJECT__) addr_a = ((gc<Object>) a->__value_object)->__address;
            if (b->__type == __TYPE_OBJECT__) addr_b = ((gc<Object>) b->__value_object)->__address;

            result->__type = __TYPE_BOOL__;
            result->__value_bool = (addr_a == addr_b);

            return result;
        } else if (func == __name) {
            if (params.size() < 1) error_message_param("name");
            gc<DataType> a = get_value(params.at(0), caller_id);
            if (a->__type != __TYPE_OBJECT__ && a->__type != __TYPE_ARRAY__) error_message("name(): parameter #1 must be a reference");

            string name;

            if (a->__type == __TYPE_ARRAY__) name = "array";
            if (a->__type == __TYPE_OBJECT__) name = ((gc<Object>) a->__value_object)->__name;

            result->__type = __TYPE_STRING__;
            result->__value_string = name;

            return result;
        } else if (func == __address) {
            if (params.size() < 1) error_message_param("address");
            gc<DataType> a = get_value(params.at(0), caller_id);
            if (a->__type != __TYPE_OBJECT__ && a->__type != __TYPE_ARRAY__) error_message("address(): parameter #1 must be a reference");

            uint_fast32_t addr;

            if (a->__type == __TYPE_ARRAY__) addr = ((gc<Array>) a->__value_array)->__address;
            if (a->__type == __TYPE_OBJECT__) addr = ((gc<Object>) a->__value_object)->__address;

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = addr;

            return result;
        } else if (func == __inherits) {
            if (params.size() < 1) error_message_param("inherits");
            gc<DataType> a = get_value(params.at(0), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("inherits(): parameter #1 must be an object");

            string inherits = ((gc<Object>) a->__value_object)->__inherited;

            result->__type = __TYPE_STRING__;
            result->__value_string = inherits;

            return result;
        } else if (func == __attributes) {
            if (params.size() < 1) error_message_param("attributes");
            gc<DataType> a = get_value(params.at(0), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("attributes(): parameter #1 must be an object");

            gc<Array> arr = core::create_array(0)->__value_array;
            uint_fast16_t i = 0;
            
            for (const auto &attr: ((gc<Object>) a->__value_object)->__attributes) {
                gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
                d->__value_string = attr.first;
                arr->__elements.push_back(d);
            }

            result->__type = __TYPE_ARRAY__;
            result->__value_array = arr;

            return result;
        } else if (func == __type) {
            if (params.size() < 1) error_message_param("type");
            gc<DataType> a = get_value(params.at(0), caller_id);

            string type;

            if (a->__type == __TYPE_ARRAY__) type = "array";
            if (a->__type == __TYPE_OBJECT__) type = "object";
            if (a->__type == __TYPE_DOUBLE__) type = "number";
            if (a->__type == __TYPE_STRING__) type = "string";
            if (a->__type == __TYPE_BOOL__) type = "boolean";
            if (a->__type == __TYPE_NULL__) type = "nothing";

            result->__type = __TYPE_STRING__;
            result->__value_string = type;

            return result;
        } else if (func == __var_exists) {
            if (params.size() < 1) error_message_params("var_exists", 1);
            AST* var = params.at(0);
            if (var->__type != __AST_VARIABLE__) error_message("var_exists(): parameter #1 must be a variable");
            
            result->__type = __TYPE_BOOL__;
            result->__value_bool = variable_exists(((AST_Variable*) var)->__identifier, caller_id);

            return result;
        } else if (func == __exit) {
            if (params.size() > 0) {
                gc<DataType> d = get_value(params.at(0), caller_id);
                if (d->__type != __TYPE_DOUBLE__ && d->__type != __TYPE_STRING__) error_message("exit(): parameter #1 must be an integer number or string");

                if (d->__type == __TYPE_DOUBLE__) {
                    int c = d->__value_double;
                    exit(c);
                } else {
                    cout << d->__value_string << endl;
                    exit(1);
                }
            } else {
                exit(0);
            }

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __error) {
            if (params.size() < 1) error_message_param("error");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_STRING__) error_message("error(): parameter #1 must be a string");

            if (__last_cur_i_e != 0) __cur_i = __last_cur_i_e;
            error_message(d->__value_string);

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __assert) {
            if (params.size() < 1) error_message_param("assert");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_BOOL__) error_message("assert(): parameter #1 must be a boolean");

            string message = "Assertion error";

            if (params.size() > 1) {
                gc<DataType> e = get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_STRING__) error_message("assert(): parameter #2 must be a string");

                message = "Assertion error: " + e->__value_string;
            }

            if (!d->__value_bool) error_message(message);

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __iif) {
            if (params.size() < 2) error_message_params("iif", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            if (a->__type != __TYPE_BOOL__) error_message("iif(): parameter #1 must be a boolean expression");

            if (a->__value_bool) {
                gc<DataType> b = get_value(params.at(1), caller_id);
                result->__type = b->__type;

                if (b->__type == __TYPE_DOUBLE__) {
                    result->__value_double = b->__value_double;
                } else if (b->__type == __TYPE_STRING__) {
                    result->__value_string = b->__value_string;
                } else if (b->__type == __TYPE_BOOL__) {
                    result->__value_bool = b->__value_bool;
                } else if (b->__type == __TYPE_ARRAY__) {
                    result->__value_array = b->__value_array;
                } else if (b->__type == __TYPE_OBJECT__) {
                    result->__value_object = b->__value_object;
                }
            } else {
                if (params.size() > 2) {
                    gc<DataType> b = get_value(params.at(2), caller_id);
                    result->__type = b->__type;

                    if (b->__type == __TYPE_DOUBLE__) {
                        result->__value_double = b->__value_double;
                    } else if (b->__type == __TYPE_STRING__) {
                        result->__value_string = b->__value_string;
                    } else if (b->__type == __TYPE_BOOL__) {
                        result->__value_bool = b->__value_bool;
                    } else if (b->__type == __TYPE_ARRAY__) {
                        result->__value_array = b->__value_array;
                    } else if (b->__type == __TYPE_OBJECT__) {
                        result->__value_object = b->__value_object;
                    }
                } else {
                    return result;
                }
            }

            return result;

        } else if (func == __total_vars) {
            cout << "Memory heap size: " << __variables.size() << endl;
            cout << "Variables:" << endl;

            for (const auto &attr: __variables) {
                cout << attr.first << endl;
            }

            return result;
        } else if (func == __platform) {
            if (params.size() < 3) error_message_params("platform", 3);
            gc<DataType> b = get_value(params.at(__DINFIO_PLATFORM_RAW__), caller_id);
            result->__type = b->__type;

            if (b->__type == __TYPE_DOUBLE__) {
                result->__value_double = b->__value_double;
            } else if (b->__type == __TYPE_STRING__) {
                result->__value_string = b->__value_string;
            } else if (b->__type == __TYPE_BOOL__) {
                result->__value_bool = b->__value_bool;
            } else if (b->__type == __TYPE_ARRAY__) {
                result->__value_array = b->__value_array;
            } else if (b->__type == __TYPE_OBJECT__) {
                result->__value_object = b->__value_object;
            }
        } else if (func == __platform_linux) {
            if (params.size() < 2) error_message_params("platform_linux", 2);
            int pos = (__DINFIO_PLATFORM_RAW__ == 0) ? 0 : 1;
            gc<DataType> b = get_value(params.at(pos), caller_id);
            result->__type = b->__type;

            if (b->__type == __TYPE_DOUBLE__) {
                result->__value_double = b->__value_double;
            } else if (b->__type == __TYPE_STRING__) {
                result->__value_string = b->__value_string;
            } else if (b->__type == __TYPE_BOOL__) {
                result->__value_bool = b->__value_bool;
            } else if (b->__type == __TYPE_ARRAY__) {
                result->__value_array = b->__value_array;
            } else if (b->__type == __TYPE_OBJECT__) {
                result->__value_object = b->__value_object;
            }
        } else if (func == __platform_mac) {
            if (params.size() < 2) error_message_params("platform_mac", 2);
            int pos = (__DINFIO_PLATFORM_RAW__ == 1) ? 0 : 1;
            gc<DataType> b = get_value(params.at(pos), caller_id);
            result->__type = b->__type;

            if (b->__type == __TYPE_DOUBLE__) {
                result->__value_double = b->__value_double;
            } else if (b->__type == __TYPE_STRING__) {
                result->__value_string = b->__value_string;
            } else if (b->__type == __TYPE_BOOL__) {
                result->__value_bool = b->__value_bool;
            } else if (b->__type == __TYPE_ARRAY__) {
                result->__value_array = b->__value_array;
            } else if (b->__type == __TYPE_OBJECT__) {
                result->__value_object = b->__value_object;
            }
        } else if (func == __platform_windows) {
            if (params.size() < 2) error_message_params("platform_windows", 2);
            int pos = (__DINFIO_PLATFORM_RAW__ == 2) ? 0 : 1;
            gc<DataType> b = get_value(params.at(pos), caller_id);
            result->__type = b->__type;

            if (b->__type == __TYPE_DOUBLE__) {
                result->__value_double = b->__value_double;
            } else if (b->__type == __TYPE_STRING__) {
                result->__value_string = b->__value_string;
            } else if (b->__type == __TYPE_BOOL__) {
                result->__value_bool = b->__value_bool;
            } else if (b->__type == __TYPE_ARRAY__) {
                result->__value_array = b->__value_array;
            } else if (b->__type == __TYPE_OBJECT__) {
                result->__value_object = b->__value_object;
            }

        } else if (func == __declare) {
            if (params.size() < 2) error_message_params("declare", 2);
            gc<DataType> f = get_value(params.at(0), caller_id);
            gc<DataType> d = get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) error_message("declare(): parameter #1 must be a string");
            if (!valid_name(f->__value_string)) error_message("declare(): invalid variable name '" + f->__value_string + "'");

            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            } else {
                e = new_gc<DataType>(__TYPE_NULL__);
            }

            __variables["1" + f->__value_string] = e;

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __get_value) {
            if (params.size() < 1) error_message_params("get_value", 1);
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_STRING__) error_message("get_value(): parameter #1 must be a string");

            bool need_return = true;

            if (params.size() > 1) {
                gc<DataType> e = get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_BOOL__) error_message("get_value(): parameter #2 must be a boolean");
                
                need_return = e->__value_bool;
            }

            if (need_return) {
                AST* expression = parse_expression(d->__value_string);
                uint_fast32_t cid = 1;

                result = get_value(expression, cid);
                delete expression;
            } else {
                AST* expression = parse_expression(d->__value_string);
                uint_fast32_t cid = 1;

                call_function(expression, cid);
                delete expression;

                result->__type = __TYPE_NULL__;
            }

            return result;
        
        } else if (func == __array_random) {
            if (params.size() < 3) error_message_params("array_random", 3);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            gc<DataType> c = get_value(params.at(2), caller_id);

            gc<Array> arr = core::create_array(0)->__value_array;

            for (int i = 0; i < a->__value_double; i++) {
                gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
                d->__value_double = random_int(b->__value_double, c->__value_double);
                arr->__elements.push_back(d);
            }

            result->__type = __TYPE_ARRAY__;
            result->__value_array = arr;

            return result;
        } else if (func == __range) {
            if (params.size() < 2) error_message_params("range", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);

            double step = 1;

            if (params.size() > 2) {
                gc<DataType> c = get_value(params.at(2), caller_id);
                step = c->__value_double;

                if (step == 0) error_message("range(): unable to use 0 in parameter #3");
            }

            gc<Array> arr = core::create_array(0)->__value_array;

            if (step > 0) {
                for (double i = a->__value_double; i <= b->__value_double; i += step) {
                    gc<DataType> ii = new_gc<DataType>(__TYPE_DOUBLE__);
                    ii->__value_double = i;
                    arr->__elements.push_back(ii);
                }
            } else {
                for (double i = a->__value_double; i >= b->__value_double; i += step) {
                    gc<DataType> ii = new_gc<DataType>(__TYPE_DOUBLE__);
                    ii->__value_double = i;
                    arr->__elements.push_back(ii);
                }
            }

            result->__type = __TYPE_ARRAY__;
            result->__value_array = arr;

            return result;
        } else if (func == __execute) {
            #ifdef __DINFIO_PLAYGROUND__
                error_message("execute(): this function is disabled");
            #endif

            if (params.size() < 1) error_message_param("execute");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_STRING__) error_message("execute(): parameter #1 must be a string");

            bool wait = true;
            string cmd = d->__value_string;
            int r = 0;

            if (params.size() > 1) {
                gc<DataType> e = get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_BOOL__) error_message("execute(): parameter #2 must be a boolean");
            
                wait = e->__value_bool;
            }

            if (!wait) {
                #ifdef _WIN32
                    cmd = "start /b " + cmd;
                #else
                    cmd += " &";
                #endif
            }

            r = system(cmd.c_str());

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = r;

            return result;
        
        } else if (func == __ref) {
            if (params.size() < 1) error_message_param("ref");
            return core::create_ref(params.at(0), "ref", 0, caller_id);
        } else if (func == __ref_eval) {
            if (params.size() < 1) error_message_param("eval");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_OBJECT__) error_message("eval(): parameter #1 must be a ref object");
            if (d->__value_object->__name != "ref") error_message("eval(): parameter #1 must be a ref object");

            RefHolder* rh = (RefHolder*) d->__value_object->__holder_pointer;
            ((AST_FunctionCall*) rh->__func)->__parameters = rh->__original_params;

            for (int i = 1; i < params.size(); i++) {
                ((AST_FunctionCall*) rh->__func)->__parameters.push_back(params.at(i));
            }

            gc<DataType> b = get_function_value((AST_FunctionCall*) rh->__func, caller_id, true);
            result->__type = b->__type;
            
            if (b->__type == __TYPE_DOUBLE__) {
                result->__value_double = b->__value_double;
            } else if (b->__type == __TYPE_STRING__) {
                result->__value_string = b->__value_string;
            } else if (b->__type == __TYPE_BOOL__) {
                result->__value_bool = b->__value_bool;
            } else if (b->__type == __TYPE_ARRAY__) {
                result->__value_array = b->__value_array;
            } else if (b->__type == __TYPE_OBJECT__) {
                result->__value_object = b->__value_object;
            }

            // delete(b);
            return result;

        } else if (func == __ref_call) {
            if (params.size() < 1) error_message_param("call");
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_OBJECT__) error_message("call(): parameter #1 must be a ref object");
            if (d->__value_object->__name != "ref") error_message("call(): parameter #1 must be a ref object");

            RefHolder* rh = (RefHolder*) d->__value_object->__holder_pointer;
            ((AST_FunctionCall*) rh->__func)->__parameters = rh->__original_params;

            for (int i = 1; i < params.size(); i++) {
                ((AST_FunctionCall*) rh->__func)->__parameters.push_back(params.at(i));
            }

            rh->call(caller_id);
        
        } else if (func == __caller_file) {
            result->__type = __TYPE_STRING__;
            result->__value_string = __codes_info[__last_cur_i]->__file;

            return result;
        } else if (func == __attribute_get) {
            if (params.size() < 2) error_message_params("attribute_get", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("attribute_get(): parameter #1 must be an object");
            if (b->__type != __TYPE_STRING__) error_message("attribute_get(): parameter #2 must be a string");

            if (((gc<Object>) a->__value_object)->__attributes.count(b->__value_string) <= 0) {
                return result;
            }

            gc<DataType> d = ((gc<Object>) a->__value_object)->__attributes[b->__value_string];

            if (d != NULL) {
                if (d->__type == __TYPE_DOUBLE__) {
                    result = new_gc<DataType>(__TYPE_DOUBLE__);
                    result->__value_double = d->__value_double;
                } else if (d->__type == __TYPE_BOOL__) {
                    result = new_gc<DataType>(__TYPE_BOOL__);
                    result->__value_bool = d->__value_bool;
                } else if (d->__type == __TYPE_STRING__) {
                    result = new_gc<DataType>(__TYPE_STRING__);
                    result->__value_string = d->__value_string;
                } else if (d->__type == __TYPE_ARRAY__) {
                    result = new_gc<DataType>(__TYPE_ARRAY__);
                    result->__value_array = d->__value_array;
                } else if (d->__type == __TYPE_OBJECT__) {
                    result = new_gc<DataType>(__TYPE_OBJECT__);
                    result->__value_object = d->__value_object;
                }
            }

            return result;
        } else if (func == __attribute_set) {
            if (params.size() < 3) error_message_params("attribute_set", 3);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            gc<DataType> d = get_value(params.at(2), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("attribute_set(): parameter #1 must be an object");
            if (b->__type != __TYPE_STRING__) error_message("attribute_set(): parameter #2 must be a string");

            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            } else {
                e = new_gc<DataType>(__TYPE_NULL__);
            }

            ((gc<Object>) a->__value_object)->__attributes[b->__value_string] = e;

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __attribute_exists) {
            if (params.size() < 2) error_message_params("attribute_exists", 2);
            gc<DataType> a = get_value(params.at(0), caller_id);
            gc<DataType> b = get_value(params.at(1), caller_id);
            if (a->__type != __TYPE_OBJECT__) error_message("attribute_exists(): parameter #1 must be an object");
            if (b->__type != __TYPE_STRING__) error_message("attribute_exists(): parameter #2 must be a string");

            result->__type = __TYPE_BOOL__;
            result->__value_bool = ((gc<Object>) a->__value_object)->__attributes.count(b->__value_string) > 0;

            return result;
        
        } else if (func == __bit_not) {
            if (params.size() < 1) error_message_params("bnot", 1);
            gc<DataType> d = get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("bnot(): parameter #1 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 1) {
                gc<DataType> e = get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_DOUBLE__) error_message("bnot(): parameter #2 must be a number");
            
                bw = e->__value_double;
                if (bw < 1 || bw > 32) error_message("bnot(): parameter #2 must be in between 1 and 32");
            }
            if (params.size() > 2) {
                gc<DataType> e = get_value(params.at(2), caller_id);
                if (e->__type != __TYPE_BOOL__) error_message("bnot(): parameter #3 must be a boolean");
            
                is_unsigned = e->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, 0, bw, 0, is_unsigned);

            return result;
        } else if (func == __bit_and) {
            if (params.size() < 2) error_message_params("band", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("band(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("band(): parameter #2 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 2) {
                gc<DataType> f = get_value(params.at(2), caller_id);
                if (f->__type != __TYPE_DOUBLE__) error_message("band(): parameter #3 must be a number");
            
                bw = f->__value_double;
                if (bw < 1 || bw > 32) error_message("band(): parameter #3 must be in between 1 and 32");
            }
            if (params.size() > 3) {
                gc<DataType> f = get_value(params.at(3), caller_id);
                if (f->__type != __TYPE_BOOL__) error_message("band(): parameter #4 must be a boolean");
            
                is_unsigned = f->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, e->__value_double, bw, 1, is_unsigned);

            return result;
        } else if (func == __bit_or) {
            if (params.size() < 2) error_message_params("bor", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("bor(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("bor(): parameter #2 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 2) {
                gc<DataType> f = get_value(params.at(2), caller_id);
                if (f->__type != __TYPE_DOUBLE__) error_message("bor(): parameter #3 must be a number");
            
                bw = f->__value_double;
                if (bw < 1 || bw > 32) error_message("bor(): parameter #3 must be in between 1 and 32");
            }
            if (params.size() > 3) {
                gc<DataType> f = get_value(params.at(3), caller_id);
                if (f->__type != __TYPE_BOOL__) error_message("bor(): parameter #4 must be a boolean");
            
                is_unsigned = f->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, e->__value_double, bw, 2, is_unsigned);

            return result;
        } else if (func == __bit_xor) {
            if (params.size() < 2) error_message_params("bxor", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("bxor(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("bxor(): parameter #2 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 2) {
                gc<DataType> f = get_value(params.at(2), caller_id);
                if (f->__type != __TYPE_DOUBLE__) error_message("bxor(): parameter #3 must be a number");
            
                bw = f->__value_double;
                if (bw < 1 || bw > 32) error_message("bxor(): parameter #3 must be in between 1 and 32");
            }
            if (params.size() > 3) {
                gc<DataType> f = get_value(params.at(3), caller_id);
                if (f->__type != __TYPE_BOOL__) error_message("bxor(): parameter #4 must be a boolean");
            
                is_unsigned = f->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, e->__value_double, bw, 3, is_unsigned);

            return result;
        } else if (func == __bit_ls) {
            if (params.size() < 2) error_message_params("bls", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("bls(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("bls(): parameter #2 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 2) {
                gc<DataType> f = get_value(params.at(2), caller_id);
                if (f->__type != __TYPE_DOUBLE__) error_message("bls(): parameter #3 must be a number");
            
                bw = f->__value_double;
                if (bw < 1 || bw > 32) error_message("bls(): parameter #3 must be in between 1 and 32");
            }
            if (params.size() > 3) {
                gc<DataType> f = get_value(params.at(3), caller_id);
                if (f->__type != __TYPE_BOOL__) error_message("bls(): parameter #4 must be a boolean");
            
                is_unsigned = f->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, e->__value_double, bw, 4, is_unsigned);

            return result;
        } else if (func == __bit_rs) {
            if (params.size() < 2) error_message_params("brs", 2);
            gc<DataType> d = get_value(params.at(0), caller_id);
            gc<DataType> e = get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) error_message("brs(): parameter #1 must be a number");
            if (e->__type != __TYPE_DOUBLE__) error_message("brs(): parameter #2 must be a number");
            
            int bw = 32;
            bool is_unsigned = false;

            if (params.size() > 2) {
                gc<DataType> f = get_value(params.at(2), caller_id);
                if (f->__type != __TYPE_DOUBLE__) error_message("brs(): parameter #3 must be a number");
            
                bw = f->__value_double;
                if (bw < 1 || bw > 32) error_message("brs(): parameter #3 must be in between 1 and 32");
            }
            if (params.size() > 3) {
                gc<DataType> f = get_value(params.at(3), caller_id);
                if (f->__type != __TYPE_BOOL__) error_message("brs(): parameter #4 must be a boolean");
            
                is_unsigned = f->__value_bool;
            }

            result->__type = __TYPE_DOUBLE__;
            result->__value_double = bitwise_operation(d->__value_double, e->__value_double, bw, 5, is_unsigned);

            return result;

        } else if (func == __register_event_loop) {
            if (params.size() < 1) error_message_param("register_event_loop");
            AST* f = params.at(0);
            if (f->__type != __AST_FUNCTION_CALL__) error_message("register_event_loop(): parameter #1 must be a function call");

            if (__event_loop == NULL) {
                if (__gui_event_loop == 0) {
                    __event_loop = f;

                    result->__type = __TYPE_BOOL__;
                    result->__value_bool = true;
                } else {
                    result->__type = __TYPE_BOOL__;
                    result->__value_bool = false;
                }
            } else {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = false;
            }
        } else if (func == __set_on_error_callback) {
            if (params.size() < 1) error_message_param("set_on_error_callback");
            AST* f = params.at(0);
            if (f->__type != __AST_FUNCTION_CALL__) error_message("set_on_error_callback(): parameter #1 must be a function call");

            if (((AST_FunctionCall*) f)->__address == 0) {
                uint_fast16_t func_id = __registered_functions[((AST_FunctionCall*) f)->__identifier];
                if (func_id == 0) error_message("Undefined function " + ((AST_FunctionCall*) f)->__identifier + "()");
            }

            if (__on_error_callback == NULL) {
                __on_error_callback = f;

                result->__type = __TYPE_BOOL__;
                result->__value_bool = true;
            } else {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = false;
            }
        }

        return result;
    }

    gc<DataType> create_ref(AST* func, string identifier, uint_fast8_t pos, uint_fast32_t& caller_id) {
        if (func->__type == __AST_FUNCTION_CALL__) {
            AST_FunctionCall* af = (AST_FunctionCall*) func;

            if (af->__identifier == "ref") {
                return get_function_value(af, caller_id, true);
            } else {
                vector<uint_fast8_t> declaration_params_type;
                uint_fast16_t func_id;

                if (af->__address == 0) {
                    func_id = __registered_functions[af->__identifier];
                    if (func_id == 0) error_message("Undefined function " + af->__identifier + "()");
                    af->__address = func_id;
                } else {
                    func_id = af->__address;
                }

                if (func_id > __BUCKET_EXTERNAL_FUNCTION__) {
                    // Do nothing
                } else if (func_id > __BUCKET_BUILT_IN_FUNCTION__) {
                    // Do nothing
                } else if (func_id > __BUCKET_UDEF_FUNCTION__) {
                    Code* c = __udef_function_map[func_id];
                    AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
                    declaration_params_type = f->__parameters_type;
                } else {
                    gc<Object> cm = __class_map[func_id];

                    if (cm->__constructor != 0) {
                        Code* c = __udef_function_map[cm->__constructor];
                        AST_FunctionCall* f = ((AST_FunctionCall*) c->__body);
                        declaration_params_type = f->__parameters_type;
                    }
                }

                int param_size = af->__parameters.size() - declaration_params_type.size();
                if (param_size < 0) param_size = 0;

                for (int i = 0; i < param_size; i++) declaration_params_type.push_back(__AST_PARAMETER_ANY__);

                gc<DataType> result = core::create_empty_object("ref");
                vector<AST*> params;

                for (int i = 0; i < af->__parameters.size(); i++) {
                    if (declaration_params_type.at(i) == __AST_PARAMETER_ANY__) {
                        gc<DataType> d = get_value(af->__parameters.at(i), caller_id);
                        gc<DataType> e;

                        if (d->__type == __TYPE_DOUBLE__) {
                            e = new_gc<DataType>(__TYPE_DOUBLE__);
                            e->__value_double = d->__value_double;
                        } else if (d->__type == __TYPE_BOOL__) {
                            e = new_gc<DataType>(__TYPE_BOOL__);
                            e->__value_bool = d->__value_bool;
                        } else if (d->__type == __TYPE_STRING__) {
                            e = new_gc<DataType>(__TYPE_STRING__);
                            e->__value_string = d->__value_string;
                        } else if (d->__type == __TYPE_ARRAY__) {
                            e = new_gc<DataType>(__TYPE_ARRAY__);
                            e->__value_array = d->__value_array;
                        } else if (d->__type == __TYPE_OBJECT__) {
                            e = new_gc<DataType>(__TYPE_OBJECT__);
                            e->__value_object = d->__value_object;
                        }

                        params.push_back(new AST_Value(e));
                    } else {
                        params.push_back(new AST_Value(core::create_ref(af->__parameters.at(i), af->__identifier, i, caller_id)));
                    }
                }

                AST_FunctionCall* f = new AST_FunctionCall(af->__identifier);
                f->__address = af->__address;
                f->__parameters = params;

                RefHolder* ref = new RefHolder(f, caller_id);
                ref->__original_params = params;
                result->__value_object->__holder_pointer = ref;

                return result;
            }
        } else {
            gc<DataType> d = get_value(func, caller_id);

            if (d->__type == __TYPE_OBJECT__) {
                if (d->__value_object->__name == "ref") {
                    return d;
                } else {
                    error_message(identifier + "(): parameter #" + to_string(pos + 1) + " must be a function call or a ref object");
                }
            } else if (d->__type == __TYPE_NULL__) {
                return d;
            } else {
                error_message(identifier + "(): parameter #" + to_string(pos + 1) + " must be a function call or a ref object");
            }
        }

        return NULL;
    }

    gc<DataType> create_array(uint_fast32_t size) {
        gc<DataType> result = new_gc<DataType>(__TYPE_ARRAY__);
        gc<Array> a = new_gc<Array>(__object_address++);

        for (int_fast32_t i = 0; i < size; i++) {
            gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
            d->__value_double = 0;
            a->__elements.push_back(d);
        }

        result->__value_array = a;
        return result;
    }

    gc<DataType> create_array_2d(uint_fast32_t rows, uint_fast32_t cols) {
        gc<DataType> result = new_gc<DataType>(__TYPE_ARRAY__);
        gc<Array> a = new_gc<Array>(__object_address++);

        for (int_fast32_t i = 0; i < rows; i++) {
            gc<DataType> r = new_gc<DataType>(__TYPE_ARRAY__);
            gc<Array> ar = new_gc<Array>(__object_address++);

            for (int_fast32_t j = 0; j < cols; j++) {
                gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
                d->__value_double = 0;
                ar->__elements.push_back(d);
            }

            r->__value_array = ar;
            a->__elements.push_back(r);
        }

        result->__value_array = a;
        return result;
    }

    gc<DataType> create_filled_array(AST_ArrayNotation* arr, uint_fast32_t& caller_id) {
        gc<DataType> result = new_gc<DataType>(__TYPE_ARRAY__);
        gc<Array> a = new_gc<Array>(__object_address++);
        vector<AST*> elements = arr->__elements;

        for (int_fast32_t i = 0; i < elements.size(); i++) {
            gc<DataType> d = get_value(elements.at(i), caller_id);
            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            } else {
                e = new_gc<DataType>(__TYPE_NULL__);
            }
            
            a->__elements.push_back(e);
        }

        result->__value_array = a;
        return result;
    }

    gc<DataType> create_empty_object(const string& name) {
        gc<DataType> result = new_gc<DataType>(__TYPE_OBJECT__);
        gc<Object> a = new_gc<Object>(name, __object_address++);

        result->__value_object = a;
        return result;
    }

    gc<DataType> create_object(AST_ObjectNotation* obj, uint_fast32_t& caller_id) {
        gc<DataType> result = new_gc<DataType>(__TYPE_OBJECT__);
        gc<Object> a = new_gc<Object>("object", __object_address++);
        vector<string> names = obj->__names;
        vector<AST*> attributes = obj->__attributes;

        for (int_fast32_t i = 0; i < attributes.size(); i++) {
            gc<DataType> d = get_value(attributes.at(i), caller_id);
            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            } else {
                e = new_gc<DataType>(__TYPE_NULL__);
            }

            a->__attributes[names.at(i)] = e;
        }

        result->__value_object = a;
        return result;
    }

    double bitwise_operation(double x, double y, int bw, char o, bool is_unsigned) {
        double result = 0;

        if (is_unsigned) {
            unsigned int mask = pow(2, bw) - 1;
            unsigned int ox = x;
            unsigned int oy = y;
            unsigned int r = 0;

            ox &= mask;
            oy &= mask;

            if (o == 0) {
                r = ~ox;
            } else if (o == 1) {
                r = ox & oy;
            } else if (o == 2) {
                r = ox | oy;
            } else if (o == 3) {
                r = ox ^ oy;
            } else if (o == 4) {
                r = ox << oy;
            } else if (o == 5) {
                r = ox >> oy;
            }

            result = r & mask;
        } else {
            unsigned int mask = pow(2, bw) - 1;
            int ox = x;
            int oy = y;
            int r = 0;

            ox &= mask;
            oy &= mask;

            if (o == 0) {
                r = ~ox;
            } else if (o == 1) {
                r = ox & oy;
            } else if (o == 2) {
                r = ox | oy;
            } else if (o == 3) {
                r = ox ^ oy;
            } else if (o == 4) {
                r = ox << oy;
            } else if (o == 5) {
                r = ox >> oy;
            }

            r &= mask;

            if (bw <= 8) {
                char r2 = r;
                result = r2;
            } else if (bw <= 16) {
                short r2 = r;
                result = r2;
            } else {
                int r2 = r;
                result = r2;
            }
        }

        return result;
    }
}
