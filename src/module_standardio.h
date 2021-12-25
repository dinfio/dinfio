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
 Module - Standard I/O
------------------------------------------------------------
*/

namespace standardIO {
    uint_fast16_t __write, __writeln, __read, __readln, __eof, __writer;

    void __init() {
        __write = register_function("write", __REG_BUILT_IN_FUNCTION__);
        __writeln = register_function("writeln", __REG_BUILT_IN_FUNCTION__);
        __read = register_function("read", __REG_BUILT_IN_FUNCTION__);
        __readln = register_function("readln", __REG_BUILT_IN_FUNCTION__);
        __eof = register_function("eof", __REG_BUILT_IN_FUNCTION__);
        __writer = register_function("writer", __REG_BUILT_IN_FUNCTION__);

        __min = __write;
        __max = __writer;   // DO NOT FORGET THIS!
    }

    DataType* construct(uint_fast16_t& func, AST* ast_func, uint_fast32_t& caller_id) {
        DataType* result = new DataType(__TYPE_NULL__);
        vector<AST*> params = ((AST_FunctionCall*) ast_func)->__parameters;

        if (func == __write) {
            if (params.size() < 1) error_message_param("write");
            DataType* d = get_value(params.at(0), caller_id);

            if (d->__type == __TYPE_DOUBLE__) {
                cout << d->__value_double << flush;
            } else if (d->__type == __TYPE_STRING__) {
                cout << d->__value_string << flush;
            } else if (d->__type == __TYPE_BOOL__) {
                string s = d->__value_bool ? "true" : "false";
                cout << s << flush;
            } else if (d->__type == __TYPE_ARRAY__) {
                stringstream sstream;
                sstream << std::hex << d->__value_array->__address;
                string result = sstream.str();

                cout << "array@0x0" << result << flush;
            } else if (d->__type == __TYPE_OBJECT__) {
                stringstream sstream;
                sstream << std::hex << d->__value_object->__address;
                string result = sstream.str();

                cout << d->__value_object->__name << "@0x0" << result << flush;
            } else {
                cout << "nothing" << flush;
            }

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            remove_garbage(params.at(0), d);

            return result;
        } else if (func == __writeln) {
            if (params.size() > 0) {
                DataType* d = get_value(params.at(0), caller_id);

                if (d->__type == __TYPE_DOUBLE__) {
                    cout << d->__value_double << endl;
                } else if (d->__type == __TYPE_STRING__) {
                    cout << d->__value_string << endl;
                } else if (d->__type == __TYPE_BOOL__) {
                    string s = d->__value_bool ? "true" : "false";
                    cout << s << endl;
                } else if (d->__type == __TYPE_ARRAY__) {
                    stringstream sstream;
                    sstream << std::hex << d->__value_array->__address;
                    string result = sstream.str();

                    cout << "array@0x0" << result << endl;
                } else if (d->__type == __TYPE_OBJECT__) {
                    stringstream sstream;
                    sstream << std::hex << d->__value_object->__address;
                    string result = sstream.str();

                    cout << d->__value_object->__name << "@0x0" << result << endl;
                } else {
                    cout << "nothing" << endl;
                }

                remove_garbage(params.at(0), d);
            } else {
                cout << endl;
            }

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;

            return result;
        } else if (func == __read) {
            string s = "";
            cin >> s;

            if (s != "" && is_number(s)) {
                result->__type = __TYPE_DOUBLE__;
                result->__value_double = stod(s);
            } else if (s == "true") {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = true;
            } else if (s == "false") {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = false;
            } else {
                result->__type = __TYPE_STRING__;
                result->__value_string = s;
            }

            return result;
        } else if (func == __readln) {
            string s;
            getline(cin, s);

            if (s != "" && is_number(s)) {
                result->__type = __TYPE_DOUBLE__;
                result->__value_double = stod(s);
            } else if (s == "true") {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = true;
            } else if (s == "false") {
                result->__type = __TYPE_BOOL__;
                result->__value_bool = false;
            } else {
                result->__type = __TYPE_STRING__;
                result->__value_string = s;
            }

            return result;
        
        } else if (func == __eof) {
            result->__type = __TYPE_BOOL__;
            result->__value_bool = cin.eof();

            return result;
        
        } else if (func == __writer) {
            if (params.size() < 1) error_message_param("writer");
            DataType* d = get_value(params.at(0), caller_id);

            standardIO::write_recursive(d, 0);
            cout << endl;

            result->__type = __TYPE_BOOL__;
            result->__value_bool = true;
            
            remove_garbage(params.at(0), d);

            return result;
        }

        return result;
    }

    void write_recursive(DataType* d, int level) {
        string spaces = repeat(" ", level * 4);
        string spaces2 = repeat(" ", (level + 1) * 4);

        if (level > 50) {
            cout << "...";
            return;
        }

        if (d->__type != __TYPE_ARRAY__ && d->__type != __TYPE_OBJECT__) {
            if (d->__type == __TYPE_DOUBLE__) {
                cout << d->__value_double;
            } else if (d->__type == __TYPE_STRING__) {
                cout << "\"" << d->__value_string << "\"";
            } else if (d->__type == __TYPE_BOOL__) {
                string s = d->__value_bool ? "true" : "false";
                cout << s;
            } else {
                cout << "nothing";
            }
        } else {
            if (d->__type == __TYPE_ARRAY__) {
                cout << "array(" << endl;
                Array* arr = ((Array*) d->__value_array);

                for (int i = 0; i < arr->__elements.size(); i++) {
                    cout << spaces2 << "[" << i << "] = ";
                    standardIO::write_recursive(arr->__elements[i], level + 1);
                    cout << endl;
                }
                
                cout << spaces << ")";
            } else {
                Object* obj = ((Object*) d->__value_object);
                cout << obj->__name << "(" << endl;
                map<string, DataType*> e;

                for (const auto &attr: obj->__attributes) {
                    e[attr.first] = attr.second;
                }

                for (const auto &attr: e) {
                    cout << spaces2 << "." << attr.first << " = ";

                    standardIO::write_recursive(obj->__attributes[attr.first], level + 1);
                    cout << endl;
                }

                e.clear();

                for (const auto &attr: obj->__functions) {
                    e[attr.first] = NULL;
                }

                for (const auto &attr: e) {
                    if (attr.first != "construct") cout << spaces2 << "." << attr.first << "()" << endl;
                }

                cout << spaces << ")";
            }
        }
    }
}
