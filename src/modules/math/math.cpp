/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2024. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - Math
-------------------------------------------------------------------
*/

#include <random>

#ifdef _WIN32
#include <chrono>
#endif

#include "dinfio_module.h"

Connector* connector;
uint_fast16_t __math_getnumber, __math_sin, __math_cos, __math_tan, __math_sind, __math_cosd, __math_tand;
uint_fast16_t __math_asin, __math_acos, __math_atan, __math_asind, __math_acosd, __math_atand;
uint_fast16_t __math_sinh, __math_cosh, __math_tanh, __math_asinh, __math_acosh, __math_atanh;
uint_fast16_t __math_abs, __math_sign, __math_sqrt, __math_exp, __math_ln, __math_log, __math_logn;
uint_fast16_t __math_floor, __math_ceil, __math_int, __math_random, __math_randomint, __math_round;

double __MATH_PI__ = 3.14159265358979;
double __MATH_E__ = 2.71828182845905;

#ifdef _WIN32
int random_int(int min, int max) {
    mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distr(min, max);

	return distr(generator);
}

double random_double(double min, double max) {
    mt19937 generator(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> distr(min, max);

	return distr(generator);
}
#else
int random_int(int min, int max) {
	random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(min, max);

	return distr(generator);
}

double random_double(double min, double max) {
	random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> distr(min, max);

	return distr(generator);
}
#endif

void add_constant_double(string name, double value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
    d->__value_double = value;
    connector->__add_constant(name, d);
}

void add_constant_string(string name, string value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
    d->__value_string = value;
    connector->__add_constant(name, d);
}

extern "C" Module* create_module() {
    return new Module();
}

extern "C" void destroy_module(Module* object) {
    delete object;
}

void Module::__init(Connector* c) {
    connector = c;


    // Add constants

    add_constant_double("math_pi", __MATH_PI__);
    add_constant_double("math_e", __MATH_E__);


    // Register functions

    __math_getnumber = connector->__register_function("getnumber");
    __math_sin = connector->__register_function("sin");
    __math_cos = connector->__register_function("cos");
    __math_tan = connector->__register_function("tan");
    __math_sind = connector->__register_function("sind");
    __math_cosd = connector->__register_function("cosd");
    __math_tand = connector->__register_function("tand");
    __math_asin = connector->__register_function("asin");
    __math_acos = connector->__register_function("acos");
    __math_atan = connector->__register_function("atan");
    __math_asind = connector->__register_function("asind");
    __math_acosd = connector->__register_function("acosd");
    __math_atand = connector->__register_function("atand");
    __math_sinh = connector->__register_function("sinh");
    __math_cosh = connector->__register_function("cosh");
    __math_tanh = connector->__register_function("tanh");
    __math_asinh = connector->__register_function("asinh");
    __math_acosh = connector->__register_function("acosh");
    __math_atanh = connector->__register_function("atanh");
    __math_abs = connector->__register_function("abs");
    __math_sign = connector->__register_function("sign");
    __math_sqrt = connector->__register_function("sqrt");
    __math_exp = connector->__register_function("exp");
    __math_ln = connector->__register_function("ln");
    __math_log = connector->__register_function("log");
    __math_logn = connector->__register_function("logn");
    __math_floor = connector->__register_function("floor");
    __math_ceil = connector->__register_function("ceil");
    __math_int = connector->__register_function("int");
    __math_random = connector->__register_function("random");
    __math_randomint = connector->__register_function("randomint");
    __math_round = connector->__register_function("round");


    // Set function addresses boundary

    __min = __math_getnumber;
    __max = __math_round;   // DO NOT FORGET THIS!
}

gc<DataType> Module::__call(uint_fast16_t& func_id, AST* func, gc<Object> obj, uint_fast32_t& caller_id) {
    gc<DataType> result = new_gc<DataType>(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __math_getnumber) {
        if (params.size() < 1) connector->__error_message_param("getnumber");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        result->__type = __TYPE_DOUBLE__;

        if (d->__type == __TYPE_STRING__) {
            try {
                result->__value_double = stod(d->__value_string);
            } catch (exception& e) {
                result->__value_double = 0;
            }
        } else if (d->__type == __TYPE_DOUBLE__) {
            result->__value_double = d->__value_double;
        } else if (d->__type == __TYPE_BOOL__) {
            result->__value_double = d->__value_bool ? 1 : 0;
        } else {
            result->__value_double = 0;
        }

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    
    } else if (func_id == __math_sin) {
        if (params.size() < 1) connector->__error_message_param("sin");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sin(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = sin(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_cos) {
        if (params.size() < 1) connector->__error_message_param("cos");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("cos(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = cos(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_tan) {
        if (params.size() < 1) connector->__error_message_param("tan");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("tan(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = tan(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __math_sind) {
        if (params.size() < 1) connector->__error_message_param("sind");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sind(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = sin(v * __MATH_PI__ / 180);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_cosd) {
        if (params.size() < 1) connector->__error_message_param("cosd");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("cosd(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = cos(v * __MATH_PI__ / 180);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_tand) {
        if (params.size() < 1) connector->__error_message_param("tand");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("tand(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = tan(v * __MATH_PI__ / 180);

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __math_asin) {
        if (params.size() < 1) connector->__error_message_param("asin");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("asin(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = asin(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_acos) {
        if (params.size() < 1) connector->__error_message_param("acos");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("acos(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = acos(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_atan) {
        if (params.size() < 1) connector->__error_message_param("atan");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("atan(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = atan(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __math_asind) {
        if (params.size() < 1) connector->__error_message_param("asind");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("asin(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = asin(v) * 180 / __MATH_PI__;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_acosd) {
        if (params.size() < 1) connector->__error_message_param("acosd");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("acos(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = acos(v) * 180 / __MATH_PI__;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_atand) {
        if (params.size() < 1) connector->__error_message_param("atand");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("atan(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = atan(v) * 180 / __MATH_PI__;

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __math_sinh) {
        if (params.size() < 1) connector->__error_message_param("sinh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sinh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = sinh(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_cosh) {
        if (params.size() < 1) connector->__error_message_param("cosh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("cosh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = cosh(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __math_tanh) {
        if (params.size() < 1) connector->__error_message_param("tanh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("tanh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = tanh(v);

        connector->__remove_garbage(params.at(0), d);

        return result;
    
    } else if (func_id == __math_asinh) {
        if (params.size() < 1) connector->__error_message_param("asinh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sinh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = asinh(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_acosh) {
        if (params.size() < 1) connector->__error_message_param("acosh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("cosh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = acosh(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_atanh) {
        if (params.size() < 1) connector->__error_message_param("atanh");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("tanh(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = atanh(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    
    } else if (func_id == __math_abs) {
        if (params.size() < 1) connector->__error_message_param("abs");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("abs(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = abs(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_sign) {
        if (params.size() < 1) connector->__error_message_param("sign");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sign(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = (v > 0) ? 1 : (v == 0) ? 0 : -1;

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_sqrt) {
        if (params.size() < 1) connector->__error_message_param("sqrt");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sqrt(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = pow(v, 0.5);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_exp) {
        if (params.size() < 1) connector->__error_message_param("exp");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("exp(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = exp(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_ln) {
        if (params.size() < 1) connector->__error_message_param("ln");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("ln(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = log(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_log) {
        if (params.size() < 1) connector->__error_message_param("log");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("log(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = log10(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_logn) {
        if (params.size() < 2) connector->__error_message_params("logn", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("logn(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("logn(): parameter #2 must be a number");
        double v = d->__value_double;
        double w = e->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = log(v) / log(w);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __math_floor) {
        if (params.size() < 1) connector->__error_message_param("floor");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("floor(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = floor(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_ceil) {
        if (params.size() < 1) connector->__error_message_param("ceil");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("ceil(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ceil(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_int) {
        if (params.size() < 1) connector->__error_message_param("int");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("int(): parameter #1 must be a number");
        double v = d->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = trunc(v);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __math_round) {
        if (params.size() < 1) connector->__error_message_param("round");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("round(): parameter #1 must be a number");
        double v = d->__value_double;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("round(): parameter #2 must be a number");
            int w = (int) e->__value_double;
            result->__type = __TYPE_DOUBLE__;

            char buffer[255];
            string fmt = "%." + to_string(w) + "f";
            sprintf(buffer, fmt.c_str(), v);

            connector->__remove_garbage(params.at(1), e);
        
            result->__value_double = stod(buffer);
        } else {
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = round(v);
        }

        connector->__remove_garbage(params.at(0), d);

        return result;

    } else if (func_id == __math_random) {
        if (params.size() < 2) connector->__error_message_params("random", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("random(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("random(): parameter #2 must be a number");
        double v = d->__value_double;
        double w = e->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = random_double(v, w);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __math_randomint) {
        if (params.size() < 2) connector->__error_message_params("randomint", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("randomint(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("randomint(): parameter #2 must be a number");
        int v = (int) d->__value_double;
        int w = (int) e->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = random_int(v, w);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    }

    return result;
}
