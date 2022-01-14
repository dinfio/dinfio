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
 Abstract Syntax Tree (AST)
------------------------------------------------------------
*/

#define __AST_DOUBLE__ 1
#define __AST_BOOL__ 2
#define __AST_STRING__ 3
#define __AST_VARIABLE__ 4
#define __AST_ARRAY__ 5
#define __AST_OBJECT__ 6
#define __AST_BINARY_EXPRESSION__ 7
#define __AST_FUNCTION_CALL__ 8
#define __AST_OBJECT_FUNCTION_CALL__ 9
#define __AST_PARAMETER__ 10
#define __AST_OBJECT_NOTATION__ 11
#define __AST_ARRAY_NOTATION__ 12
#define __AST_VALUE__ 13
#define __AST_NULL__ 14

#define __AST_OPERATOR_PLUS__ 1
#define __AST_OPERATOR_MINUS__ 2
#define __AST_OPERATOR_MULTIPLY__ 3
#define __AST_OPERATOR_DIVIDE__ 4
#define __AST_OPERATOR_INT_DIVIDE__ 5
#define __AST_OPERATOR_MODULO__ 6
#define __AST_OPERATOR_CONCAT__ 7
#define __AST_OPERATOR_EXPONENT__ 8
#define __AST_OPERATOR_AND__ 9
#define __AST_OPERATOR_OR__ 10
#define __AST_OPERATOR_XOR__ 11
#define __AST_OPERATOR_EQUAL__ 12
#define __AST_OPERATOR_NOT_EQUAL__ 13
#define __AST_OPERATOR_LESS__ 14
#define __AST_OPERATOR_GREATER__ 15
#define __AST_OPERATOR_LESS_EQUAL__ 16
#define __AST_OPERATOR_GREATER_EQUAL__ 17
#define __AST_OPERATOR_NOT__ 18

#define __AST_PARAMETER_ANY__ 1
#define __AST_PARAMETER_REF__ 2

class AST {
public:
    uint_fast8_t __type;

    AST(uint_fast8_t type) {
        __type = type;
    }
};

class AST_BinaryExpression: public AST {
public:
    AST* __left;
    AST* __right;
    uint_fast8_t __operator;
    
    AST_BinaryExpression(AST* left, uint_fast8_t opr, AST* right): AST(__AST_BINARY_EXPRESSION__) {
        __left = left;
        __right = right;
        __operator = opr;
    }
};

class AST_FunctionCall: public AST {
public:
    string __identifier;
    uint_fast16_t __address;
    vector<AST*> __parameters;
    vector<uint_fast8_t> __parameters_type;
    vector<AST*> __optional_parameters;
    vector<string> __local_variables;
    uint_fast8_t __required_params;

    AST_FunctionCall(string identifier): AST(__AST_FUNCTION_CALL__) {
        __identifier = identifier;
    }
};

class AST_ObjectFunctionCall: public AST {
public:
    AST_Object* __object;   // Last attribute is not used. Address is stored in object.functions[]
    string __identifier;
    vector<AST*> __parameters;

    AST_ObjectFunctionCall(AST_Object* object, string identifier): AST(__AST_OBJECT_FUNCTION_CALL__) {
        __identifier = identifier;
        __object = object;
    }
};

class AST_ObjectNotation: public AST {
public:
    vector<string> __names;
    vector<AST*> __attributes;

    AST_ObjectNotation(): AST(__AST_OBJECT_NOTATION__) {}
};

class AST_ArrayNotation: public AST {
public:
    vector<AST*> __elements;

    AST_ArrayNotation(): AST(__AST_ARRAY_NOTATION__) {}
};

class AST_Parameter: public AST {
public:
    vector<AST*> __parameters;

    AST_Parameter(): AST(__AST_PARAMETER__) {}
};

class AST_Double: public AST {
public:
    DataType* __value;

    AST_Double(double value): AST(__AST_DOUBLE__) {
        DataType* d = new DataType(__TYPE_DOUBLE__);
        d->__value_double = value;
        __value = d;
    }
};

class AST_Bool: public AST {
public:
    DataType* __value;

    AST_Bool(bool value): AST(__AST_BOOL__) {
        DataType* d = new DataType(__TYPE_BOOL__);
        d->__value_bool = value;
        __value = d;
    }
};

class AST_String: public AST {
public:
    DataType* __value;

    AST_String(string value): AST(__AST_STRING__) {
        DataType* d = new DataType(__TYPE_STRING__);
        d->__value_string = value;
        __value = d;
    }
};

class AST_Variable: public AST {
public:
    string __identifier;
    uint_fast32_t __caller_id;
    DataType* __variable_holder;

    AST_Variable(string identifier): AST(__AST_VARIABLE__) {
        __identifier = identifier;
        __caller_id = 0;
    }
};

class AST_Array: public AST {
public:
    string __identifier;
    uint_fast32_t __caller_id;
    DataType* __variable_holder;
    vector<AST*> __indices;

    AST_Array(string identifier): AST(__AST_ARRAY__) {
        __identifier = identifier;
        __caller_id = 0;
    }
};

class AST_Object: public AST {
public:
    string __identifier;
    uint_fast32_t __caller_id;
    DataType* __variable_holder;
    AST_Array* __array_holder;
    vector<AST*> __attributes;   // This is only AST_Variable (just literal) or AST_Array

    AST_Object(string identifier): AST(__AST_OBJECT__) {
        __identifier = identifier;
        __caller_id = 0;
    }
};

class AST_Value: public AST {
public:
    DataType* __value;

    AST_Value(DataType* value): AST(__AST_VALUE__) {
        __value = value;
    }
};
