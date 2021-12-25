/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.1
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2021. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Module Interface version 3.1.04
------------------------------------------------------------
 NOTE: Please comply with this interface,
       and please do not modify this file.
------------------------------------------------------------
*/

#ifndef __MODULE_H__
#define __MODULE_H__

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

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

#define __TYPE_DOUBLE__ 1
#define __TYPE_STRING__ 2
#define __TYPE_BOOL__ 3
#define __TYPE_ARRAY__ 4
#define __TYPE_OBJECT__ 5
#define __TYPE_NULL__ 6

using namespace std;

class Base {
public:
    uint_fast8_t __type;
};

class Array;
class Object;

class DataType {
public:
    uint_fast8_t __type;

    double __value_double;
    string __value_string;
    bool __value_bool;
    Array* __value_array;
    Object* __value_object;

    DataType(uint_fast8_t type);
};

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

class AST;
class AST_BinaryExpression;
class AST_FunctionCall;
class AST_ObjectFunctionCall;
class AST_ObjectNotation;
class AST_ArrayNotation;
class AST_Parameter;
class AST_Double;
class AST_Bool;
class AST_String;
class AST_Variable;
class AST_Array;
class AST_Object;
class AST_Value;

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
    vector<string> __local_variables;

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
        __caller_id = -1;
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
        __caller_id = -1;
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
        __caller_id = -1;
    }
};

class AST_Value: public AST {
public:
    DataType* __value;

    AST_Value(DataType* value): AST(__AST_VALUE__) {
        __value = value;
    }
};

class Connector {
public:
    virtual uint_fast16_t __register_function(string);
    virtual DataType* __get_value(AST*, uint_fast32_t&);
    virtual void __call_function(AST*, uint_fast32_t&);
    virtual DataType* __create_array(uint_fast32_t);
    virtual DataType* __create_object(const string&);
    virtual void __object_set_attribute(DataType*, string, DataType*);
    virtual void __object_set_function(DataType*, string, uint_fast16_t);
    virtual void __add_constant(const string&, DataType*);
    virtual void __error_message(string);
    virtual void __error_message_param(string);
    virtual void __error_message_params(string, uint8_t);
    virtual bool __variable_exists(string, uint_fast32_t&);
    virtual void __remove_garbage(AST*, DataType*);
    virtual string __get_current_file();
    virtual string __get_version();
    virtual string __get_path();
};

class Module;

class Module {
public:
    uint_fast16_t __min, __max;

    Module() {}

    virtual void __init(Connector*);
    virtual DataType* __call(uint_fast16_t&, AST*, Object*, uint_fast32_t&);
};

#endif
