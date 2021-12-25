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
 Header
------------------------------------------------------------
*/

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;


// Dinfio Information

#ifdef __linux__
    const uint_fast8_t __DINFIO_PLATFORM_RAW__ = 0;
    const string __DINFIO_PLATFORM__ = "Linux x86_64";
    const string __DINFIO_PATH__ = "/usr/local/dinfio/";
    const string __MODULE_EXTENSION__ = ".so";

    #define __RTLD_TYPE__ RTLD_LAZY
#elif __APPLE__
    const uint_fast8_t __DINFIO_PLATFORM_RAW__ = 1;
    const string __DINFIO_PLATFORM__ = "macOS";
    const string __DINFIO_PATH__ = "/Library/Dinfio/3.1/";
    const string __MODULE_EXTENSION__ = ".so";

    #define __RTLD_TYPE__ RTLD_LOCAL
#else
    const uint_fast8_t __DINFIO_PLATFORM_RAW__ = 2;
    const string __DINFIO_PLATFORM__ = "Windows";
    const string __DINFIO_PATH__ = "C:\\Dinfio\\";
    const string __MODULE_EXTENSION__ = ".dll";

    #define __RTLD_TYPE__ RTLD_LOCAL
#endif

const int __DINFIO_VERSION_NUMBER__ = 30106;
const string __DINFIO_VERSION_MAJOR__ = "3";
const string __DINFIO_VERSION_MINOR__ = "1";
const string __DINFIO_VERSION_REVISION__ = "06";
const string __DINFIO_VERSION__ =  __DINFIO_VERSION_MAJOR__ + "." + __DINFIO_VERSION_MINOR__ + "." + __DINFIO_VERSION_REVISION__;
const string __DINFIO_BUILD_DATE_RAW__ = "2021-12-22";
const string __DINFIO_BUILD_DATE__ = "22 December 2021";
const string __MODULES_PATH__ = __DINFIO_PATH__ + "modules/";


// Abstract Syntax Tree (AST)

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


// Abstract Syntax Tree Builder (FIO Parser)

class Code {
public:
    uint_fast8_t __header;
    uint_fast8_t __additional_header;
    AST* __body;
    AST* __body2;

    uint_fast32_t __endclause;
    uint_fast32_t __endclause2;
    uint_fast32_t __index;
};

class CodeInfo {
public:
    string __original;
    uint_fast32_t __line;
    string __file;
};

vector<string> __codes_raw;
vector<Code*> __codes;
vector<CodeInfo*> __codes_info;
uint_fast32_t __n_codes = 0;

string __cur_original;
uint_fast32_t __cur_file_line;
string __cur_file;
uint_fast32_t __cur_i;
uint_fast32_t __last_cur_i = 0;
bool __walked = false;
bool __interactive_mode = false;
bool __default_mode = false;
string __default_file;

void parse_code(char*);
string remove_tabs(string&);
string remove_spaces(string);
string remove_spaces_tabs(string&);
string remove_comments(string);
Code* parse_line_code(string&);
void parse_multiline(string);
bool bracket_complete(string&);
bool is_variable_assignment(string, string&, string&, string&);


// Global

class Base;

void parse_arguments(int, char*);
void error_message(string);
void error_message_param(string);
void error_message_params(string, uint8_t);
string read_file(char*);
vector<string> get_source(char*);
vector<string> split(string, string);
vector<string> split(string, string, int);
bool is_number(const string&);
bool valid_name(const string&);
string trim(const string&);
string lcase(string);
string ucase(string);
string right(string&, int);
string left(string&, int);
void replace_all(string&, const string&, const string&);
string full_path(char*);
char* full_path_char(char*);


// Variable Layer

#define __TYPE_DOUBLE__ 1
#define __TYPE_STRING__ 2
#define __TYPE_BOOL__ 3
#define __TYPE_ARRAY__ 4
#define __TYPE_OBJECT__ 5
#define __TYPE_NULL__ 6
#define __TYPE_UNDEFINED_FUNC__ 7

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

DataType* get_value(AST*, uint_fast32_t&);
void declare_variables(AST*, AST*, uint_fast32_t&, bool);
DataType* get_variable_value(string&, uint_fast32_t&);
DataType* get_array_value(AST*, uint_fast32_t&);
void set_array_value(DataType*, AST_Array*, DataType*, uint_fast32_t&);
DataType* get_object_value(AST*, uint_fast32_t&);
void set_object_value(DataType*, AST_Object*, DataType*, uint_fast32_t&);
DataType* get_attribute_array_value(Object*, AST*, uint_fast32_t&);
void set_attribute_array_value(Object*, AST*, DataType*, uint_fast32_t&);
Object* get_pure_object_value(AST*, uint_fast32_t&);
bool variable_exists(string, uint_fast32_t&);
void error_message_array(string, string, uint_fast32_t&, vector<AST*>, uint_fast32_t&);
void error_message_object(string, string, uint_fast32_t&, vector<AST*>, uint_fast32_t&);


// Expression Parser

AST* parse_expression(string&);
AST* parse_function_call(string&);
AST_Array* parse_array(string&);
AST_Object* parse_object(string&);
AST_FunctionCall* parse_function_declaration(string&);
AST_Parameter* parse_class_declaration(string&);
AST_Parameter* parse_field_declaration(string&);
AST_Parameter* parse_var_declaration_name(string&);
AST_Parameter* parse_var_declaration_value(string&);
AST_ObjectNotation* parse_object_notation(string&);
AST_ArrayNotation* parse_array_notation(string&);
AST_Parameter* parse_parameters(string&);
vector<string> parse_array_elements(string&);
vector<string> parse_object_attributes(string&);
vector<string> parse_function_parameters(string&);
bool is_there_object(string&);
string __remove_unused_parentheses(string&);
bool __parentheses_symmetric(string&);
bool __is_operator(string&);
int __get_precedence(string&);


// Flow Controls

vector<Code*> __flow_controls;
bool __stop_loop = false;
bool __stop_procedure = false;

void loop_for(AST*, uint_fast8_t&, uint_fast8_t&, uint_fast32_t&);
void loop_while(AST*, uint_fast32_t&, uint_fast32_t&);
void branch_if(AST*, uint_fast32_t&, uint_fast32_t&, bool, uint_fast32_t&);
void parse_flow_control();


// Functions and Classes

#define __REG_CLASS__ 0
#define __REG_UDEF_FUNCTION__ 1
#define __REG_BUILT_IN_FUNCTION__ 2
#define __REG_EXTERNAL_FUNCTION__ 3

#define __BUCKET_CLASS__ 0
#define __BUCKET_UDEF_FUNCTION__ 1000
#define __BUCKET_BUILT_IN_FUNCTION__ 2000
#define __BUCKET_EXTERNAL_FUNCTION__ 3000

vector<Code*> __functions_classes;
unordered_map<string, uint_fast16_t> __registered_functions;
unordered_map<uint_fast16_t, Code*> __udef_function_map;
unordered_map<uint_fast16_t, Object*> __class_map;

uint_fast32_t __function_caller_id = 2;
uint_fast16_t __address_external = 1;
uint_fast16_t __address_builtin = 1;
uint_fast16_t __address_udef = 1;
uint_fast16_t __address_class = 1;
uint_fast32_t __object_address = 0;

vector<AST_FunctionCall*> __init_functions;

uint_fast16_t register_function(string, uint_fast8_t);
DataType* get_function_value(AST_FunctionCall*, uint_fast32_t&, bool);
DataType* get_object_function_value(AST_ObjectFunctionCall*, uint_fast32_t&, bool);
void call_function(AST*, uint_fast32_t&);
void remove_garbage(AST*, DataType*);
void parse_function_class();


// AST Walker

void walk(uint_fast32_t, uint_fast32_t&);
void assignment(AST*, AST*, uint_fast32_t&);


// Module

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

class Module {
public:
    uint_fast16_t __min, __max;

    virtual void __init(Connector*);
    virtual DataType* __call(uint_fast16_t&, AST*, Object*, uint_fast32_t&);
};

vector<Module*> __modules;
Connector* __module_connector = new Connector();
string __imported_modules;
Module* __gui_module;
uint_fast16_t __gui_event_loop = 0;
AST* __event_loop = NULL;

void init_builtin(int, char*);
void import_module(string);


// Module - Standard I/O

namespace standardIO {
    uint_fast16_t __min, __max;

    void __init();
    DataType* construct(uint_fast16_t&, AST*, uint_fast32_t&);
    void write_recursive(DataType*, int);
}


// Module - Core

namespace core {
    uint_fast16_t __min, __max;

    void __init();
    DataType* construct(uint_fast16_t&, AST*, uint_fast32_t&);
    DataType* create_ref(AST*, string, uint_fast8_t, uint_fast32_t&);
    DataType* create_array(uint_fast32_t);
    DataType* create_array_2d(uint_fast32_t, uint_fast32_t);
    DataType* create_filled_array(AST_ArrayNotation*, uint_fast32_t&);
    DataType* create_empty_object(const string&);
    DataType* create_object(AST_ObjectNotation*, uint_fast32_t&);
    double bitwise_operation(double, double, int, char, bool);
}
