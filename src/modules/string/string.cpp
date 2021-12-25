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
 Module - String
-------------------------------------------------------------------
 Compilation Instruction:
  - Please see ./compile.sh
-------------------------------------------------------------------
*/

#include <map>
#include "module.h"

Connector* connector;
uint_fast16_t __string_split, __string_length, __string_toascii, __string_fromascii, __string_trim, __string_ltrim, __string_rtrim;
uint_fast16_t __string_lcase, __string_ucase, __string_fcase, __string_reverse, __string_subleft, __string_subright, __string_substring;
uint_fast16_t __string_format, __string_repeat, __string_find, __string_findlast, __string_replace, __string_str;
uint_fast16_t __string_levenshtein, __string_hamming, __string_join;

bool is_number(const string& s) {
    char* p;
    strtod(s.c_str(), &p);
    return *p == 0;
}

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> result;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back (token);
    }

    result.push_back(s.substr(pos_start));
    return result;
}

vector<string> split(string s, string delimiter, int limit) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> result;

    int i = 0;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back (token);

        i++;

        if (i + 1 >= limit) break;
    }

    result.push_back(s.substr(pos_start));
    return result;
}

string rtrim(string s) {
    char t = ' ';
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

string ltrim(string s) {
    char t = ' ';
    s.erase(0, s.find_first_not_of(t));
    return s;
}

string trim(string s) {
    return ltrim(rtrim(s));
}

string lcase(string s) {
    string result = "";

    for (int i = 0; i < s.length(); i++) {
        result += tolower(s[i]);
    }

    return result;
}

string ucase(string s) {
	string result = "";

    for (int i = 0; i < s.length(); i++) {
        result += toupper(s[i]);
    }

    return result;
}

string fcase(string s) {
	string result = "";
    result = toupper(s[0]);

    for (int i = 1; i < s.length(); i++) {
        if (s[i - 1] == ' ' || s[i - 1] == '\n') {
            result += toupper(s[i]);
        } else {
            result += tolower(s[i]);
        }
    }

    return result;
}

string str_reverse(string s) {
	string result = "";

    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }

    return result;
}

string right(string& s, int len) {
	return s.substr(s.length() - len);
}

string left(string& s, int len) {
	return s.substr(0, len);
}

void replace_all(string& str, const string& from, const string& to) {
    if(from.empty()) return;

    size_t start_pos = 0;

    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void replace_count(string& str, const string& from, const string& to, int count) {
    if(from.empty()) return;

    size_t start_pos = 0;
    int i = 0;

    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();

        i++;
        if (i >= count) break;
    }
}

string repeat(string str, int n) {
	string result = "";

	for (int i = 1; i <= n; i++) {
		result += str;
	}

	return result;
}

size_t levenshtein(const string& s1, const string& s2) {
    const size_t m(s1.size());
    const size_t n(s2.size());

    if (m == 0) return n;
    if (n == 0) return m;

    size_t* costs = new size_t[n + 1];

    for (size_t k = 0; k <= n; k++) costs[k] = k;
    size_t i = 0;

    for (string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
        costs[0] = i + 1;
        size_t corner = i;
        size_t j = 0;

        for (string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
            size_t upper = costs[j+1];

            if (*it1 == *it2) {
                costs[j + 1] = corner;
            } else {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }

            corner = upper;
        }
    }

    size_t result = costs[n];
    delete [] costs;

    return result;
}

void add_constant_double(string name, double value) {
    DataType* d = new DataType(__TYPE_DOUBLE__);
    d->__value_double = value;
    connector->__add_constant(name, d);
}

void add_constant_string(string name, string value) {
    DataType* d = new DataType(__TYPE_STRING__);
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


    // Register functions

    __string_split = connector->__register_function("split");
    __string_str = connector->__register_function("str");
    __string_length = connector->__register_function("length");
    __string_toascii = connector->__register_function("toascii");
    __string_fromascii = connector->__register_function("fromascii");
    __string_trim = connector->__register_function("trim");
    __string_ltrim = connector->__register_function("ltrim");
    __string_rtrim = connector->__register_function("rtrim");
    __string_lcase = connector->__register_function("lcase");
    __string_ucase = connector->__register_function("ucase");
    __string_fcase = connector->__register_function("fcase");
    __string_reverse = connector->__register_function("reverse");
    __string_subleft = connector->__register_function("subleft");
    __string_subright = connector->__register_function("subright");
    __string_substring = connector->__register_function("substring");
    __string_repeat = connector->__register_function("repeat");
    __string_format = connector->__register_function("format");
    __string_find = connector->__register_function("find");
    __string_findlast = connector->__register_function("findlast");
    __string_replace = connector->__register_function("replace");
    __string_levenshtein = connector->__register_function("levenshtein");
    __string_hamming = connector->__register_function("hamming");
    __string_join = connector->__register_function("join");


    // Set function addresses boundary

    __min = __string_split;
    __max = __string_join;   // DO NOT FORGET THIS!
}

DataType* Module::__call(uint_fast16_t& func_id, AST* func, Object* obj, uint_fast32_t& caller_id) {
    DataType* result = new DataType(__TYPE_NULL__);
    vector<AST*> params = ((AST_FunctionCall*) func)->__parameters;

    if (func_id == __string_split) {
        if (params.size() < 2) connector->__error_message_params("split", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("split(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("split(): parameter #2 must be a string");

        uint_fast32_t limit = -1;
        vector<string> v;

        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("split(): parameter #3 must be a number");
            limit = f->__value_double;

            v = split(d->__value_string, e->__value_string, limit);
            connector->__remove_garbage(params.at(2), f);
        } else {
            v = split(d->__value_string, e->__value_string);
        }

        DataType* da = connector->__create_array(0);

        for (int i = 0; i < v.size(); i++) {
            DataType* el = new DataType(__TYPE_STRING__);
            el->__value_string = v.at(i);
            da->__value_array->__elements.push_back(el);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return da;
    } else if (func_id == __string_length) {
        if (params.size() < 1) connector->__error_message_param("length");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("length(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = s.length();

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __string_toascii) {
        if (params.size() < 1) connector->__error_message_param("toascii");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("toascii(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = (int) s[0];

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_fromascii) {
        if (params.size() < 1) connector->__error_message_param("fromascii");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("fromascii(): parameter #1 must be a number");
        char s = (char) d->__value_double;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_trim) {
        if (params.size() < 1) connector->__error_message_param("trim");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("trim(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = trim(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_ltrim) {
        if (params.size() < 1) connector->__error_message_param("ltrim");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("ltrim(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = ltrim(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_rtrim) {
        if (params.size() < 1) connector->__error_message_param("rtrim");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("rtrim(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = rtrim(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_lcase) {
        if (params.size() < 1) connector->__error_message_param("lcase");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("lcase(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = lcase(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_ucase) {
        if (params.size() < 1) connector->__error_message_param("ucase");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("ucase(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = ucase(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_fcase) {
        if (params.size() < 1) connector->__error_message_param("fcase");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("fcase(): parameter #1 must be a string");
        string s = d->__value_string;
        
        result->__type = __TYPE_STRING__;
        result->__value_string = fcase(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_reverse) {
        if (params.size() < 1) connector->__error_message_param("reverse");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("reverse(): parameter #1 must be a string");
        string s = d->__value_string;

        result->__type = __TYPE_STRING__;
        result->__value_string = str_reverse(s);

        connector->__remove_garbage(params.at(0), d);
        
        return result;
    } else if (func_id == __string_subleft) {
        if (params.size() < 2) connector->__error_message_params("subleft", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("subleft(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("subleft(): parameter #2 must be a number");
        string s = d->__value_string;

        result->__type = __TYPE_STRING__;
        result->__value_string = left(s, e->__value_double);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_subright) {
        if (params.size() < 2) connector->__error_message_params("subright", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("subright(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("subright(): parameter #2 must be a number");
        string s = d->__value_string;

        result->__type = __TYPE_STRING__;
        result->__value_string = right(s, e->__value_double);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_substring) {
        if (params.size() < 2) connector->__error_message_params("substring", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("substring(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("substring(): parameter #2 must be a number");
        string s = d->__value_string;

        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("substring(): parameter #3 must be a number");
            s = s.substr(e->__value_double, f->__value_double);

            connector->__remove_garbage(params.at(2), f);
        } else {
            s = s.substr(e->__value_double);
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_repeat) {
        if (params.size() < 2) connector->__error_message_params("repeat", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("repeat(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("repeat(): parameter #2 must be a number");
        string s = d->__value_string;

        result->__type = __TYPE_STRING__;
        result->__value_string = repeat(s, e->__value_double);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_format) {
        if (params.size() < 2) connector->__error_message_params("format", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("format(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("format(): parameter #2 must be a number");
        
        string s = "";
        string x = d->__value_string;
        char buffer[255];

        if (x == "%s" || x == "%c") connector->__error_message("format(): cannot use '%s' or '%c' format");

        if (x == "%d" || x == "%i" || x == "%x" || x == "%X" || x == "%o") {
            sprintf(buffer, x.c_str(), (int) e->__value_double);
        } else {
            sprintf(buffer, x.c_str(), e->__value_double);
        }

        s = buffer;

        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_find) {
        if (params.size() < 2) connector->__error_message_params("find", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("find(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("find(): parameter #2 must be a string");
        string s = d->__value_string;
        size_t start = 0;
        int rslt = -1;
        size_t pos;

        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("find(): parameter #3 must be a number");
            start = (size_t) f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }

        pos = s.find(e->__value_string, start);
        if (pos == string::npos) rslt = -1; else rslt = pos;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = rslt;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_findlast) {
        if (params.size() < 2) connector->__error_message_params("findlast", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("findlast(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("findlast(): parameter #2 must be a string");
        string s = d->__value_string;
        size_t start = string::npos;
        int rslt = -1;
        size_t pos;

        if (params.size() > 2) {
            DataType* f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("findlast(): parameter #3 must be a number");
            start = (size_t) f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }

        pos = s.rfind(e->__value_string, start);
        if (pos == string::npos) rslt = -1; else rslt = pos;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = rslt;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_replace) {
        if (params.size() < 3) connector->__error_message_params("replace", 3);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        DataType* f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("replace(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("replace(): parameter #2 must be a string");
        if (f->__type != __TYPE_STRING__) connector->__error_message("replace(): parameter #3 must be a string");
        string s = d->__value_string;
        
        if (params.size() > 3) {
            DataType* g = connector->__get_value(params.at(3), caller_id);
            if (g->__type != __TYPE_DOUBLE__) connector->__error_message("find(): parameter #4 must be a number");
            int count = g->__value_double;

            replace_count(s, e->__value_string, f->__value_string, count);
            connector->__remove_garbage(params.at(3), g);   
        } else {
            replace_all(s, e->__value_string, f->__value_string);
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        
        return result;
    } else if (func_id == __string_str) {
        if (params.size() < 1) connector->__error_message_param("str");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        string s = "";

        if (d->__type == __TYPE_DOUBLE__) {
            char buffer[255];
            sprintf(buffer, "%g", d->__value_double);
            s = buffer;
        } else if (d->__type == __TYPE_STRING__) {
            s = d->__value_string;
        } else if (d->__type == __TYPE_BOOL__) {
            s = d->__value_bool ? "true" : "false";
        } else if (d->__type == __TYPE_ARRAY__) {
            stringstream sstream;
            sstream << std::hex << d->__value_array->__address;
            string result = sstream.str();

            s = "array@0x0" + result;
        } else if (d->__type == __TYPE_OBJECT__) {
            stringstream sstream;
            sstream << std::hex << d->__value_object->__address;
            string result = sstream.str();

            s = d->__value_object->__name + "@0x0" + result;
        } else {
            s = "nothing";
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = s;

        connector->__remove_garbage(params.at(0), d);

        return result;
    } else if (func_id == __string_levenshtein) {
        if (params.size() < 2) connector->__error_message_params("levenshtein", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("levenshtein(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("levenshtein(): parameter #2 must be a string");
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = (long) levenshtein(d->__value_string, e->__value_string);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_hamming) {
        if (params.size() < 2) connector->__error_message_params("hamming", 2);
        DataType* d = connector->__get_value(params.at(0), caller_id);
        DataType* e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("hamming(): parameter #1 must be a string");
        if (e->__type != __TYPE_STRING__) connector->__error_message("hamming(): parameter #2 must be a string");
        string a = d->__value_string;
        string b = e->__value_string;

        if (a.length() != b.length()) connector->__error_message("hamming(): length of parameter #1 and parameter #2 must equal");
        int r = 0;

        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) r++;
        }
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = r;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return result;
    } else if (func_id == __string_join) {
        if (params.size() < 1) connector->__error_message_param("join");
        DataType* d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("join(): parameter #1 must be an array");
        string glue = "";
        string rslt = "";

        if (params.size() > 1) {
            DataType* e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_STRING__) connector->__error_message("join(): parameter #2 must be a string");
            glue = e->__value_string;

            connector->__remove_garbage(params.at(1), e);
        }

        Array* arr = ((Array*) d->__value_array);
        connector->__remove_garbage(params.at(0), d);
        
        for (const auto t: arr->__elements) {
            string s = "";

            if (t->__type == __TYPE_DOUBLE__) {
                char buffer[255];
                sprintf(buffer, "%g", t->__value_double);
                s = buffer;
            } else if (t->__type == __TYPE_STRING__) {
                s = t->__value_string;
            } else if (t->__type == __TYPE_BOOL__) {
                s = t->__value_bool ? "true" : "false";
            } else if (t->__type == __TYPE_ARRAY__) {
                stringstream sstream;
                sstream << std::hex << t->__value_array->__address;
                string result = sstream.str();

                s = "array@0x0" + result;
            } else if (t->__type == __TYPE_OBJECT__) {
                stringstream sstream;
                sstream << std::hex << t->__value_object->__address;
                string result = sstream.str();

                s = t->__value_object->__name + "@0x0" + result;
            } else {
                s = "nothing";
            }

            rslt += s + glue;
        }

        for (int i = 1; i <= glue.length(); i++) rslt.pop_back();

        result->__type = __TYPE_STRING__;
        result->__value_string = rslt;

        return result;
    }

    return result;
}
