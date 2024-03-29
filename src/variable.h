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
 Data Type & Variable Layer
------------------------------------------------------------
*/

DataType::DataType(uint_fast8_t type) {
    __type = type;
}

class Array {
public:
    uint_fast32_t __address;
    vector<DataType*> __elements;

    Array(uint_fast32_t address) {
        __address = address;
    }
};

class Object {
public:
    string __name;
    uint_fast32_t __address;
    string __inherited;
    Base* __holder_pointer;

    uint_fast16_t __constructor;
    
    unordered_map<string, DataType*> __attributes;
    unordered_map<string, uint_fast16_t> __functions;

    Object(string name, uint_fast32_t address) {
        __name = name;
        __address = address;
    }
};

DataType* get_value(AST* expression, uint_fast32_t& caller_id) {
    uint_fast8_t type = expression->__type;

    if (type == __AST_VARIABLE__) {
        AST_Variable* e = (AST_Variable*) expression;

        if (e->__caller_id == caller_id) {
            return e->__variable_holder;
        } else {
            string c = to_string(caller_id);
            DataType* d = __variables[c + e->__identifier];

            if (d == NULL) {
                __variables.erase(c + e->__identifier);
                c = "1";
                d = __variables[c + e->__identifier];
            }

            if (d == NULL) error_message("Undeclared variable '" + e->__identifier + "'");

            e->__caller_id = caller_id;
            e->__variable_holder = d;

            return d;
        }
    } else if (type == __AST_DOUBLE__) {
        AST_Double* e = (AST_Double*) expression;
        return e->__value;
    } else if (type == __AST_BOOL__) {
        AST_Bool* e = (AST_Bool*) expression;
        return e->__value;
    } else if (type == __AST_STRING__) {
        AST_String* e = (AST_String*) expression;
        return e->__value;
    } else if (type == __AST_BINARY_EXPRESSION__) {
        AST_BinaryExpression* e = (AST_BinaryExpression*) expression;
        DataType* a = get_value(e->__left, caller_id);
        DataType* b = get_value(e->__right, caller_id);
        DataType* r;
        uint_fast8_t opr = e->__operator;

        if (opr == __AST_OPERATOR_PLUS__) {
            r = new DataType(__TYPE_DOUBLE__);
            r->__value_double = a->__value_double + b->__value_double;

            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_MINUS__) {
            r = new DataType(__TYPE_DOUBLE__);
            r->__value_double = a->__value_double - b->__value_double;

            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_MULTIPLY__) {
            r = new DataType(__TYPE_DOUBLE__);
            r->__value_double = a->__value_double * b->__value_double;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_DIVIDE__) {
            r = new DataType(__TYPE_DOUBLE__);
            if (b->__value_double == 0) error_message("Division by zero");

            r->__value_double = a->__value_double / b->__value_double;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_INT_DIVIDE__) {
            r = new DataType(__TYPE_DOUBLE__);
            if (b->__value_double == 0) error_message("Division by zero");

            r->__value_double = (int) (a->__value_double / b->__value_double);
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_MODULO__) {
            r = new DataType(__TYPE_DOUBLE__);
            if (b->__value_double == 0) error_message("Division by zero");
            
            r->__value_double = fmod(a->__value_double, b->__value_double);
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_CONCAT__) {
            r = new DataType(__TYPE_STRING__);
            
            DataType* x = a;
            DataType* y = b;

            if (x->__type == __TYPE_DOUBLE__) {
                char buffer[255];
                sprintf(buffer, "%g", x->__value_double);
                x->__value_string = buffer;
            }
            if (y->__type == __TYPE_DOUBLE__) {
                char buffer[255];
                sprintf(buffer, "%g", y->__value_double);
                y->__value_string = buffer;
            }
            if (x->__type == __TYPE_BOOL__) x->__value_string = (x->__value_bool) ? "true" : "false";
            if (y->__type == __TYPE_BOOL__) y->__value_string = (y->__value_bool) ? "true" : "false";

            r->__value_string = x->__value_string + y->__value_string;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_EXPONENT__) {
            r = new DataType(__TYPE_DOUBLE__);
            r->__value_double = pow(a->__value_double, b->__value_double);
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_AND__) {
            r = new DataType(__TYPE_BOOL__);
            r->__value_bool = a->__value_bool && b->__value_bool;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_OR__) {
            r = new DataType(__TYPE_BOOL__);
            r->__value_bool = a->__value_bool || b->__value_bool;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_XOR__) {
            r = new DataType(__TYPE_BOOL__);
            r->__value_bool = a->__value_bool == !b->__value_bool;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_NOT__) {
            r = new DataType(__TYPE_BOOL__);
            r->__value_bool = !b->__value_bool;
            
            if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
            if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);

            return r;
        } else if (opr == __AST_OPERATOR_EQUAL__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                if (b->__type != __TYPE_DOUBLE__) {
                    r->__value_bool = false;
                } else {
                    r->__value_bool = a->__value_double == b->__value_double;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                if (b->__type != __TYPE_STRING__) {
                    r->__value_bool = false;
                } else {
                    r->__value_bool = a->__value_string == b->__value_string;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                if (b->__type != __TYPE_BOOL__) {
                    r->__value_bool = false;
                } else {
                    r->__value_bool = a->__value_bool == b->__value_bool;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_NULL__ && b->__type == __TYPE_NULL__) {
                r->__value_bool = true;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_NULL__ && b->__type != __TYPE_NULL__) {
                r->__value_bool = false;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_ARRAY__ && b->__type != __TYPE_ARRAY__) {
                r->__value_bool = false;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_OBJECT__ && b->__type != __TYPE_OBJECT__) {
                r->__value_bool = false;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_ARRAY__) {
                r->__value_bool = a->__value_array->__address == b->__value_array->__address;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_OBJECT__) {
                r->__value_bool = a->__value_object->__address == b->__value_object->__address;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        } else if (opr == __AST_OPERATOR_NOT_EQUAL__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                if (b->__type != __TYPE_DOUBLE__) {
                    r->__value_bool = true;
                } else {
                    r->__value_bool = a->__value_double != b->__value_double;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                if (b->__type != __TYPE_STRING__) {
                    r->__value_bool = true;
                } else {
                    r->__value_bool = a->__value_string != b->__value_string;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                if (b->__type != __TYPE_BOOL__) {
                    r->__value_bool = true;
                } else {
                    r->__value_bool = a->__value_bool != b->__value_bool;
                }

                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_NULL__ && b->__type == __TYPE_NULL__) {
                r->__value_bool = false;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_NULL__ && b->__type != __TYPE_NULL__) {
                r->__value_bool = true;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_ARRAY__ && b->__type != __TYPE_ARRAY__) {
                r->__value_bool = true;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_OBJECT__ && b->__type != __TYPE_OBJECT__) {
                r->__value_bool = true;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_ARRAY__) {
                r->__value_bool = a->__value_array->__address != b->__value_array->__address;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_OBJECT__) {
                r->__value_bool = a->__value_object->__address != b->__value_object->__address;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        } else if (opr == __AST_OPERATOR_LESS__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                r->__value_bool = a->__value_double < b->__value_double;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                r->__value_bool = a->__value_string < b->__value_string;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                r->__value_bool = a->__value_bool < b->__value_bool;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        } else if (opr == __AST_OPERATOR_GREATER__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                r->__value_bool = a->__value_double > b->__value_double;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                r->__value_bool = a->__value_string > b->__value_string;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                r->__value_bool = a->__value_bool > b->__value_bool;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        } else if (opr == __AST_OPERATOR_LESS_EQUAL__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                r->__value_bool = a->__value_double <= b->__value_double;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                r->__value_bool = a->__value_string <= b->__value_string;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                r->__value_bool = a->__value_bool <= b->__value_bool;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        } else if (opr == __AST_OPERATOR_GREATER_EQUAL__) {
            r = new DataType(__TYPE_BOOL__);

            if (a->__type == __TYPE_DOUBLE__) {
                r->__value_bool = a->__value_double >= b->__value_double;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_STRING__) {
                r->__value_bool = a->__value_string >= b->__value_string;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            if (a->__type == __TYPE_BOOL__) {
                r->__value_bool = a->__value_bool >= b->__value_bool;
            
                if (e->__left->__type == __AST_FUNCTION_CALL__ || e->__left->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__left->__type == __AST_BINARY_EXPRESSION__) delete(a);
                if (e->__right->__type == __AST_FUNCTION_CALL__ || e->__right->__type == __AST_OBJECT_FUNCTION_CALL__ || e->__right->__type == __AST_BINARY_EXPRESSION__) delete(b);
                return r;
            }

            return NULL;
        }
    
    } else if (type == __AST_ARRAY__) {
        return get_array_value(expression, caller_id);
    } else if (type == __AST_OBJECT__) {
        return get_object_value(expression, caller_id);

    } else if (type == __AST_FUNCTION_CALL__) {
        AST_FunctionCall* e = (AST_FunctionCall*) expression;
        return get_function_value(e, caller_id, true);
    } else if (type == __AST_OBJECT_FUNCTION_CALL__) {
        AST_ObjectFunctionCall* e = (AST_ObjectFunctionCall*) expression;
        return get_object_function_value(e, caller_id, true);

    } else if (type == __AST_ARRAY_NOTATION__) {
        AST_ArrayNotation* e = (AST_ArrayNotation*) expression;
        return core::create_filled_array(e, caller_id);
    } else if (type == __AST_OBJECT_NOTATION__) {
        AST_ObjectNotation* e = (AST_ObjectNotation*) expression;
        return core::create_object(e, caller_id);
    } else if (type == __AST_VALUE__) {
        AST_Value* e = (AST_Value*) expression;
        return e->__value;
    
    } else if (type == __AST_NULL__) {
        return __nothing_value;
    }

    return __nothing_value;
}

void declare_variables(AST* l, AST* r, uint_fast32_t& caller_id, bool is_local) {
    string c = (is_local) ? to_string(caller_id) : "1";
    AST_Parameter* vars = (AST_Parameter*) l;
    AST_Parameter* vals = (AST_Parameter*) r;

    for (uint_fast16_t i = 0; i < vars->__parameters.size(); i++) {
        AST* vr = vars->__parameters.at(i);
        AST* vl = vals->__parameters.at(i);

        DataType* g = get_value(vl, caller_id);
        DataType* d = new DataType(__TYPE_NULL__);
        d->__type = g->__type;

        if (g->__type == __TYPE_DOUBLE__) {
            d->__value_double = g->__value_double;
        } else if (g->__type == __TYPE_BOOL__) {
            d->__value_bool = g->__value_bool;
        } else if (g->__type == __TYPE_STRING__) {
            d->__value_string = g->__value_string;
        } else if (g->__type == __TYPE_ARRAY__) {
            d->__value_array = g->__value_array;
        } else  if (g->__type == __TYPE_OBJECT__) {
            d->__value_object = g->__value_object;
        }

        if (__variables[c + ((AST_Variable*) vr)->__identifier] != NULL) {
            error_message("Variable '" + ((AST_Variable*) vr)->__identifier + "' is already declared");
        }

        __variables[c + ((AST_Variable*) vr)->__identifier] = d;
        remove_garbage(vl, g);
    }
}

DataType* get_array_value(AST* expression, uint_fast32_t& caller_id) {
    AST_Array* e = (AST_Array*) expression;
    DataType* v;

    if (e->__caller_id == caller_id) {
        v = e->__variable_holder;
    } else {
        string c = to_string(caller_id);
        DataType* d = __variables[c + e->__identifier];

        if (d == NULL) {
            __variables.erase(c + e->__identifier);
            c = "1";
            d = __variables[c + e->__identifier];
        }

        if (d == NULL) error_message("Undeclared variable '" + e->__identifier + "'");

        e->__caller_id = caller_id;
        e->__variable_holder = d;

        v = d;
    }

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_ARRAY__) error_message(msg + " is not an array");
    Array* temp = v->__value_array;

    for (; i < e->__indices.size() - 1; i++) {
        DataType* index = get_value(e->__indices.at(i), caller_id);

        if (index->__type != __TYPE_DOUBLE__) {
            error_message("Array index must be a number");
        }

        if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
        v = temp->__elements[(int) (index->__value_double)];
        if (v->__type != __TYPE_ARRAY__) error_message_array(msg, "is not an array", i, e->__indices, caller_id);

        temp = v->__value_array;

        remove_garbage(e->__indices.at(i), index);
    }

    DataType* index = get_value(e->__indices.at(i), caller_id);
    
    if (index->__type != __TYPE_DOUBLE__) {
        error_message("Array index must be a number");
    }

    if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
    v = temp->__elements[(int) (index->__value_double)];

    remove_garbage(e->__indices.at(i), index);

    return v;
}

void set_array_value(DataType* v, AST_Array* e, DataType* val, uint_fast32_t& caller_id) {
    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_ARRAY__) error_message(msg + " is not an array");
    Array* temp = v->__value_array;

    for (; i < e->__indices.size() - 1; i++) {
        DataType* index = get_value(e->__indices.at(i), caller_id);
        
        if (index->__type != __TYPE_DOUBLE__) {
            error_message("Array index must be a number");
        }

        if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
        v = temp->__elements[(int) (index->__value_double)];
        if (v->__type != __TYPE_ARRAY__) error_message_array(msg, "is not an array", i, e->__indices, caller_id);

        remove_garbage(e->__indices.at(i), index);

        temp = v->__value_array;
    }

    int j = i;
    DataType* index = get_value(e->__indices.at(i), caller_id);
    
    if (index->__type != __TYPE_DOUBLE__) {
        error_message("Array index must be a number");
    }

    if (temp->__elements.size() <= index->__value_double) {
        int s = ((index->__value_double - temp->__elements.size()) + 1);
        
        for (i = 1; i <= s; i++) {
            temp->__elements.push_back(new DataType(__TYPE_DOUBLE__));
        }

        v = temp->__elements[(int) (index->__value_double)];
    } else {
        v = temp->__elements[(int) (index->__value_double)];
    }

    if (val->__type == __TYPE_DOUBLE__) {
        v->__type = __TYPE_DOUBLE__;
        v->__value_double = val->__value_double;
    }
    if (val->__type == __TYPE_BOOL__) {
        v->__type = __TYPE_BOOL__;
        v->__value_bool = val->__value_bool;
    }
    if (val->__type == __TYPE_STRING__) {
        v->__type = __TYPE_STRING__;
        v->__value_string = val->__value_string;
    }
    if (val->__type == __TYPE_ARRAY__) {
        v->__type = __TYPE_ARRAY__;
        v->__value_array = val->__value_array;
    }
    if (val->__type == __TYPE_OBJECT__) {
        v->__type = __TYPE_OBJECT__;
        v->__value_object = val->__value_object;
    }
    if (val->__type == __TYPE_NULL__) {
        v->__type = __TYPE_NULL__;
    }

    remove_garbage(e->__indices.at(j), index);
}

DataType* get_object_value(AST* expression, uint_fast32_t& caller_id) {
    AST_Object* e = (AST_Object*) expression;
    DataType* v;

    if (e->__array_holder == NULL) {
        if (e->__caller_id == caller_id) {
            v = e->__variable_holder;
        } else {
            string c = to_string(caller_id);
            DataType* d = __variables[c + e->__identifier];

            if (d == NULL) {
                __variables.erase(c + e->__identifier);
                c = "1";
                d = __variables[c + e->__identifier];
            }

            if (d == NULL) error_message("Undeclared variable '" + e->__identifier + "'");

            e->__caller_id = caller_id;
            e->__variable_holder = d;

            v = d;
        }
    } else {
        v = get_array_value(e->__array_holder, caller_id);
    }

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_OBJECT__) error_message(msg + " is not an object");
    Object* temp = v->__value_object;

    for (; i < e->__attributes.size() - 1; i++) {
        if (e->__attributes.at(i)->__type == __AST_VARIABLE__) {
            string idx = ((AST_Variable*) e->__attributes.at(i))->__identifier;
            v = temp->__attributes[idx];
        } else {
            v = get_attribute_array_value(temp, e->__attributes.at(i), caller_id);
        }

        if (v == NULL) error_message_object(msg, "is undefined", i, e->__attributes, caller_id);
        if (v->__type != __TYPE_OBJECT__) error_message_object(msg, "is not an object", i, e->__attributes, caller_id);

        temp = v->__value_object;
    }

    if (e->__attributes.at(i)->__type == __AST_VARIABLE__) {
        string idx = ((AST_Variable*) e->__attributes.at(i))->__identifier;
        v = temp->__attributes[idx];
    } else {
        v = get_attribute_array_value(temp, e->__attributes.at(i), caller_id);
    }

    if (v == NULL) error_message_object(msg, "is undefined", i, e->__attributes, caller_id);

    return v;
}

void set_object_value(DataType* v, AST_Object* e, DataType* val, uint_fast32_t& caller_id) {
    if (e->__array_holder != NULL) {
        v = get_array_value(e->__array_holder, caller_id);
    }

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_OBJECT__) error_message(msg + " is not an object");
    Object* temp = v->__value_object;

    for (; i < e->__attributes.size() - 1; i++) {
        if (e->__attributes.at(i)->__type == __AST_VARIABLE__) {
            string idx = ((AST_Variable*) e->__attributes.at(i))->__identifier;
            v = temp->__attributes[idx];
        } else {
            v = get_attribute_array_value(temp, e->__attributes.at(i), caller_id);
        }

        if (v == NULL) error_message_object(msg, "is undefined", i, e->__attributes, caller_id);
        if (v->__type != __TYPE_OBJECT__) error_message_object(msg, "is not an object", i, e->__attributes, caller_id);

        temp = v->__value_object;
    }

    if (e->__attributes.at(i)->__type == __AST_VARIABLE__) {
        string idx = ((AST_Variable*) e->__attributes.at(i))->__identifier;
        v = temp->__attributes[idx];

        if (v == NULL) {
            DataType* nv = new DataType(__TYPE_NULL__);
            temp->__attributes[idx] = nv;
            v = nv;
        }

        if (val->__type == __TYPE_DOUBLE__) {
            v->__type = __TYPE_DOUBLE__;
            v->__value_double = val->__value_double;
        }
        if (val->__type == __TYPE_BOOL__) {
            v->__type = __TYPE_BOOL__;
            v->__value_bool = val->__value_bool;
        }
        if (val->__type == __TYPE_STRING__) {
            v->__type = __TYPE_STRING__;
            v->__value_string = val->__value_string;
        }
        if (val->__type == __TYPE_ARRAY__) {
            v->__type = __TYPE_ARRAY__;
            v->__value_array = val->__value_array;
        }
        if (val->__type == __TYPE_OBJECT__) {
            v->__type = __TYPE_OBJECT__;
            v->__value_object = val->__value_object;
        }
        if (val->__type == __TYPE_NULL__) {
            v->__type = __TYPE_NULL__;
        }
    } else {
        set_attribute_array_value(temp, e->__attributes.at(i), val, caller_id);
    }
}

DataType* get_attribute_array_value(Object* obj, AST* expression, uint_fast32_t& caller_id) {
    AST_Array* e = (AST_Array*) expression;
    DataType* v = obj->__attributes[e->__identifier];

    if (v == NULL) error_message("Attribute " + e->__identifier + " is undefined");

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_ARRAY__) error_message("Attribute " + msg + " is not an array");
    Array* temp = v->__value_array;

    for (; i < e->__indices.size() - 1; i++) {
        DataType* index = get_value(e->__indices.at(i), caller_id);
        
        if (index->__type != __TYPE_DOUBLE__) {
            error_message("Array index must be a number");
        }

        if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
        v = temp->__elements[(int) (index->__value_double)];
        if (v->__type != __TYPE_ARRAY__) error_message_array(msg, "is not an array", i, e->__indices, caller_id);

        remove_garbage(e->__indices.at(i), index);

        temp = v->__value_array;
    }

    DataType* index = get_value(e->__indices.at(i), caller_id);
    
    if (index->__type != __TYPE_DOUBLE__) {
        error_message("Array index must be a number");
    }

    if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
    v = temp->__elements[(int) (index->__value_double)];

    remove_garbage(e->__indices.at(i), index);

    return v;
}

void set_attribute_array_value(Object* obj, AST* expression, DataType* val, uint_fast32_t& caller_id) {
    AST_Array* e = (AST_Array*) expression;
    DataType* v = obj->__attributes[e->__identifier];

    if (v == NULL) error_message("Attribute " + e->__identifier + " is undefined");

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_ARRAY__) error_message("Attribute " + msg + " is not an array");
    Array* temp = v->__value_array;

    for (; i < e->__indices.size() - 1; i++) {
        DataType* index = get_value(e->__indices.at(i), caller_id);
        
        if (index->__type != __TYPE_DOUBLE__) {
            error_message("Array index must be a number");
        }

        if (temp->__elements.size() <= index->__value_double) error_message_array(msg, "is undefined", i, e->__indices, caller_id);
        v = temp->__elements[(int) (index->__value_double)];
        if (v->__type != __TYPE_ARRAY__) error_message_array(msg, "is not an array", i, e->__indices, caller_id);

        remove_garbage(e->__indices.at(i), index);

        temp = v->__value_array;
    }

    int j = i;
    DataType* index = get_value(e->__indices.at(i), caller_id);

    if (index->__type != __TYPE_DOUBLE__) {
        error_message("Array index must be a number");
    }

    if (temp->__elements.size() <= index->__value_double) {
        int s = ((index->__value_double - temp->__elements.size()) + 1);
        
        for (i = 1; i <= s; i++) {
            temp->__elements.push_back(new DataType(__TYPE_DOUBLE__));
        }

        v = temp->__elements[(int) (index->__value_double)];
    } else {
        v = temp->__elements[(int) (index->__value_double)];
    }

    if (val->__type == __TYPE_DOUBLE__) {
        v->__type = __TYPE_DOUBLE__;
        v->__value_double = val->__value_double;
    }
    if (val->__type == __TYPE_BOOL__) {
        v->__type = __TYPE_BOOL__;
        v->__value_bool = val->__value_bool;
    }
    if (val->__type == __TYPE_STRING__) {
        v->__type = __TYPE_STRING__;
        v->__value_string = val->__value_string;
    }
    if (val->__type == __TYPE_ARRAY__) {
        v->__type = __TYPE_ARRAY__;
        v->__value_array = val->__value_array;
    }
    if (val->__type == __TYPE_OBJECT__) {
        v->__type = __TYPE_OBJECT__;
        v->__value_object = val->__value_object;
    }
    if (val->__type == __TYPE_NULL__) {
        v->__type = __TYPE_NULL__;
    }

    remove_garbage(e->__indices.at(j), index);
}

Object* get_pure_object_value(AST* expression, uint_fast32_t& caller_id) {
    AST_Object* e = (AST_Object*) expression;
    DataType* v;

    if (e->__array_holder == NULL) {
        if (e->__caller_id == caller_id) {
            v = e->__variable_holder;
        } else {
            string c = to_string(caller_id);
            DataType* d = __variables[c + e->__identifier];

            if (d == NULL) {
                __variables.erase(c + e->__identifier);
                c = "1";
                d = __variables[c + e->__identifier];
            }

            if (d == NULL) error_message("Undeclared variable '" + e->__identifier + "'");

            e->__caller_id = caller_id;
            e->__variable_holder = d;

            v = d;
        }
    } else {
        v = get_array_value(e->__array_holder, caller_id);
    }

    uint_fast32_t i = 0;
    string msg = e->__identifier;
    if (v->__type != __TYPE_OBJECT__) error_message(msg + " is not an object");
    Object* temp = v->__value_object;

    for (; i < e->__attributes.size() - 1; i++) {
        if (e->__attributes.at(i)->__type == __AST_VARIABLE__) {
            string idx = ((AST_Variable*) e->__attributes.at(i))->__identifier;
            v = temp->__attributes[idx];
        } else {
            v = get_attribute_array_value(temp, e->__attributes.at(i), caller_id);
        }

        if (v == NULL) error_message_object(msg, "is undefined", i, e->__attributes, caller_id);
        if (v->__type != __TYPE_OBJECT__) error_message_object(msg, "is not an object", i, e->__attributes, caller_id);

        temp = v->__value_object;
    }

    return temp;
}

bool variable_exists(string var_name, uint_fast32_t& caller_id) {
    bool e = __variables.count(to_string(caller_id) + var_name) == 1;

    if (e) {
        return e;
    } else {
        return __variables.count("1" + var_name) == 1;
    }
}

void error_message_array(string v, string msg, uint_fast32_t& idx, vector<AST*> indices, uint_fast32_t& caller_id) {
    for (uint_fast32_t i = 0; i <= idx; i++) {
        DataType* index = get_value(indices.at(i), caller_id);
        string sidx;

        if (index->__type == __TYPE_DOUBLE__) {
            sidx = to_string((int) (index->__value_double));
        } else if (index->__type == __TYPE_STRING__) {
            sidx = index->__value_string;
        }

        v += "[" + sidx + "]";
    }

    error_message(v + " " + msg);
}

void error_message_object(string v, string msg, uint_fast32_t& idx, vector<AST*> attributes, uint_fast32_t& caller_id) {
    for (uint_fast32_t i = 0; i <= idx; i++) {
        string sidx = (attributes.at(i)->__type == __AST_VARIABLE__) ?
                      ((AST_Variable*) attributes.at(i))->__identifier :
                      ((AST_Array*) attributes.at(i))->__identifier + "[...]";
        
        v += "." + sidx;
    }

    error_message(v + " " + msg);
}
