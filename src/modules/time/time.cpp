/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2026. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - Date and Time
-------------------------------------------------------------------
*/

#include <chrono>
#include <ctime>
#include <time.h>
#include <clocale>
#include <future>

#ifndef _WIN32
    #include <thread>
#else
    #include "mingw.thread.h"
#endif

#include "dinfio_module.h"

using namespace std::chrono;

Connector* connector;
uint_fast16_t __time_now, __time_current_millis, __time_format_datetime, __time_create_datetime;
uint_fast16_t __time_get_year, __time_get_month, __time_get_day, __time_get_weekday, __time_get_yearday;
uint_fast16_t __time_get_hour, __time_get_minute, __time_get_second;
uint_fast16_t __time_is_dst, __time_get_timezone;
uint_fast16_t __time_time_diff;
uint_fast16_t __time_set_locale;
uint_fast16_t __time_sleep, __time_sleep_s;

struct tm __get_time(time_t t, bool utc) {
    struct tm ts;

    if (!utc) {
        ts = *localtime(&t);
    } else {
        ts = *gmtime(&t);
    }

    return ts;
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

    __time_now = connector->__register_function("now");
    __time_current_millis = connector->__register_function("current_millis");
    __time_format_datetime = connector->__register_function("datetime");
    __time_create_datetime = connector->__register_function("create_datetime");
    __time_get_year = connector->__register_function("get_year");
    __time_get_month = connector->__register_function("get_month");
    __time_get_day = connector->__register_function("get_day");
    __time_get_weekday = connector->__register_function("get_weekday");
    __time_get_yearday = connector->__register_function("get_yearday");
    __time_get_hour = connector->__register_function("get_hour");
    __time_get_minute = connector->__register_function("get_minute");
    __time_get_second = connector->__register_function("get_second");
    __time_is_dst = connector->__register_function("is_dst");
    __time_get_timezone = connector->__register_function("get_timezone");
    __time_set_locale = connector->__register_function("set_timelocale");
    __time_time_diff = connector->__register_function("time_diff");
    __time_sleep = connector->__register_function("sleep");
    __time_sleep_s = connector->__register_function("sleep_s");


    // Set function addresses boundary

    __min = __time_now;
    __max = __time_sleep_s;   // DO NOT FORGET THIS!
}

gc<DataType> Module::__call(uint_fast16_t& func_id, AST* func, gc<Object> obj, uint_fast32_t& caller_id) {
    gc<DataType> result = new_gc<DataType>(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __time_now) {
        time_t now = time(0);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = now;

        return result;
    } else if (func_id == __time_current_millis) {
        long long now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = now;

        return result;
    } else if (func_id == __time_time_diff) {
        if (params.size() < 2) connector->__error_message_params("time_diff", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("time_diff(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("time_diff(): parameter #2 must be a number");

        time_t time1 = (time_t) d->__value_double;
        time_t time2 = (time_t) e->__value_double;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = difftime(time1, time2);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return result;
    } else if (func_id == __time_format_datetime) {
        string fmt = "%F %T";
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_STRING__) connector->__error_message("datetime(): parameter #1 must be a string");
            fmt = e->__value_string;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("datetime(): parameter #2 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("datetime(): parameter #3 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(2), e);
        }

        struct tm ts = __get_time(t, utc);
        char buf[255];
        strftime(buf, sizeof(buf), fmt.c_str(), &ts);

        result->__type = __TYPE_STRING__;
        result->__value_string = buf;

        return result;
    } else if (func_id == __time_create_datetime) {
        if (params.size() < 3) connector->__error_message_params("create_datetime", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #3 must be a number");

        int year = (int) d->__value_double;
        int month = (int) e->__value_double;
        int day = (int) f->__value_double;
        int hour = 0;
        int minute = 0;
        int second = 0;
        bool utc = false;

        if (params.size() > 3) {
            gc<DataType> e = connector->__get_value(params.at(3), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #4 must be a number");
            hour = (int) e->__value_double;

            connector->__remove_garbage(params.at(3), e);
        }
        if (params.size() > 4) {
            gc<DataType> e = connector->__get_value(params.at(4), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #5 must be a number");
            minute = (int) e->__value_double;

            connector->__remove_garbage(params.at(4), e);
        }
        if (params.size() > 5) {
            gc<DataType> e = connector->__get_value(params.at(5), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("create_datetime(): parameter #6 must be a number");
            second = (int) e->__value_double;

            connector->__remove_garbage(params.at(5), e);
        }
        if (params.size() > 6) {
            gc<DataType> e = connector->__get_value(params.at(6), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("create_datetime(): parameter #7 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(6), e);
        }

        time_t r;
        struct tm ts;

        ts.tm_year = year - 1900;
        ts.tm_mon = month - 1;
        ts.tm_mday = day;
        ts.tm_hour = hour;
        ts.tm_min = minute;
        ts.tm_sec = second;
        ts.tm_isdst = 0;

        r = mktime(&ts);
        if (utc) r -= timezone;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = r;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);

        return result;
    } else if (func_id == __time_set_locale) {
        if (params.size() < 1) connector->__error_message_param("set_timelocale");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("set_timelocale(): parameter #1 must be a string");

        setlocale(LC_TIME, d->__value_string.c_str());

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __time_get_year) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_year(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_year(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_year + 1900;

        return result;
    } else if (func_id == __time_get_month) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_month(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_month(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_mon + 1;

        return result;
    } else if (func_id == __time_get_day) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_day(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_day(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_mday;

        return result;
    } else if (func_id == __time_get_weekday) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_weekday(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_weekday(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_wday;

        return result;
    } else if (func_id == __time_get_yearday) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_yearday(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_yearday(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_yday + 1;

        return result;
    } else if (func_id == __time_get_hour) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_hour(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_hour(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_hour;

        return result;
    } else if (func_id == __time_get_minute) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_minute(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_minute(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_min;

        return result;
    } else if (func_id == __time_get_second) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_second(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_second(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ts.tm_sec;

        return result;
    } else if (func_id == __time_is_dst) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("is_dst(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("is_dst(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_BOOL__;
        result->__value_bool = (ts.tm_isdst == 0) ? false : true;

        return result;
    } else if (func_id == __time_get_timezone) {
        time_t t = time(0);
        bool utc = false;

        if (params.size() > 0) {
            gc<DataType> e = connector->__get_value(params.at(0), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("get_timezone(): parameter #1 must be a number");
            t = (time_t) e->__value_double;

            connector->__remove_garbage(params.at(0), e);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("get_timezone(): parameter #2 must be a boolean");
            utc = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        struct tm ts = __get_time(t, utc);
        result->__type = __TYPE_STRING__;

        #ifdef _WIN32
            result->__value_string = "";
        #else
            result->__value_string = ts.tm_zone;
        #endif

        return result;
    
    } else if (func_id == __time_sleep) {
        vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;
        if (params.size() < 1) connector->__error_message_param("sleep");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sleep(): parameter #1 must be a number");

        long ms = d->__value_double;
        connector->__remove_garbage(params.at(0), d);
        
        this_thread::sleep_for(chrono::milliseconds(ms));
    } else if (func_id == __time_sleep_s) {
        vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;
        if (params.size() < 1) connector->__error_message_param("sleep_s");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("sleep_s(): parameter #1 must be a number");

        long s = d->__value_double;
        connector->__remove_garbage(params.at(0), d);
        
        this_thread::sleep_for(chrono::seconds(s));
    }
    
    return result;
}
