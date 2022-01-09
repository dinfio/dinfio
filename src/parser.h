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
 Parser
------------------------------------------------------------
*/

#define __H_EMPTY__ 0
#define __H_COMMENT__ 1
#define __H_IF__ 2
#define __H_ELSE__ 3
#define __H_ELSE_IF__ 4
#define __H_END_IF__ 5
#define __H_WHILE__ 6
#define __H_END_WHILE__  7
#define __H_DO_WHILE__ 8
#define __H_END_DO_WHILE__ 9
#define __H_FOR__ 10
#define __H_END_FOR__ 11
#define __H_RETURN__ 12
#define __H_RETURN_VOID__ 13
#define __H_YIELD__ 14
#define __H_STOP__ 15
#define __H_FUNCTION__ 16
#define __H_EXIT_LOOP__ 17
#define __H_VAR__ 18
#define __H_GLOBAL__ 19
#define __H_IMPORT__ 20
#define __H_VARIABLE_ASSIGNMENT__ 21
#define __H_VARIABLE_ASSIGNMENT_EXTENDED__ 22
#define __H_PROCEDURE_CALL__ 23
#define __H_CLASS__ 24
#define __H_END_CLASS__ 25
#define __H_FIELD__ 26

#define __H_FOR_WITHOUT_STEP__ 1
#define __H_FOR_WITH_STEP__ 2

void parse_code(char* filename) {
    __codes_raw = get_source(filename);
    string fullpath = full_path(filename);

    parse_multiline(fullpath);
    uint_fast32_t index = __codes.size();

    vector<Code*> fios;

    for (int i = 0; i < __codes_raw.size(); i++) {
        string l = __codes_raw.at(i);

        l = remove_tabs(l);
        vector<string> line_codes = split(l, "\n");

        for (int j = 0; j < line_codes.size(); j++) {
            string lc = trim(line_codes.at(j));

            if (lc != "" && lc.substr(0, 1) != "'" && lc.substr(0, 1) != "#") {
                __n_codes++;

                __cur_file_line = i + 1;
                __cur_original = lc;
                __cur_file = fullpath;

                Code* c = parse_line_code(lc);
                CodeInfo* ci = new CodeInfo();

                c->__index = index++;

                ci->__original = lc;
                ci->__line = i + 1;
                ci->__file = fullpath;

                __codes_info.push_back(ci);
                __codes.push_back(c);

                if (c->__header == __H_IMPORT__) fios.push_back(c);
            }
        }
    }


    // Import modules

    for (int i = 0; i < fios.size(); i++) {
        Code* f = fios.at(i);
        vector<AST*> m = ((AST_Parameter*) f->__body)->__parameters;

        for (int j = 0; j < m.size(); j++) {
            string so = ((AST_Variable*) m.at(j))->__identifier;
            string mod = so + ".fio";

            if (get_file_size(__MODULES_PATH__ + so + "/" + so + __MODULE_EXTENSION__) != -1) {
                if (__imported_modules.find(so + ";") == string::npos) {
                    __cur_file_line = __codes_info[f->__index]->__line;
                    __cur_original = __codes_info[f->__index]->__original;
                    __cur_file = __codes_info[f->__index]->__file;

                    __imported_modules += so + ";";
                    import_module(so);
                    
                    if (get_file_size(__MODULES_PATH__ + so + "/extra.fio") != -1) parse_code(const_cast<char*>((__MODULES_PATH__ + so + "/extra.fio").c_str()));
                }

                continue;
            }

            if (get_file_size(__MODULES_PATH__ + so + "/main.fio") != -1) {
                if (__imported_modules.find(__MODULES_PATH__ + so + "/main.fio;") == string::npos) {
                    __imported_modules += __MODULES_PATH__ + so + "/main.fio;";
                    parse_code(const_cast<char*>((__MODULES_PATH__ + so + "/main.fio").c_str()));
                }
            } else {
                string mmod = (left(mod, 1) != "/") ? dirname(fullpath) + "/" + mod : mod;

                if (mmod == fullpath) {
                    __cur_file_line = __codes_info[f->__index]->__line;
                    __cur_original = __codes_info[f->__index]->__original;
                    __cur_file = __codes_info[f->__index]->__file;

                    error_message("Cannot import itself");
                }
                
                if (get_file_size(mmod) != -1) {
                    if (__imported_modules.find(mmod + ";") == string::npos) {
                        __imported_modules += mmod + ";";
                        parse_code(const_cast<char*>(mmod.c_str()));
                    }
                } else {
                    __cur_file_line = __codes_info[f->__index]->__line;
                    __cur_original = __codes_info[f->__index]->__original;
                    __cur_file = __codes_info[f->__index]->__file;

                    error_message("Module '" + so + "' is not found");
                }
            }
        }
    }
}

void parse_multiline(string filename) {
    try {
        for (int i = 0; i < __codes_raw.size(); i++) {
            __cur_file_line = i + 1;
            __cur_original = __codes_raw.at(i);
            __cur_file = filename;

            int j = i + 1;

            while (!bracket_complete(__codes_raw.at(i))) {
                __codes_raw.at(i) += " " + remove_comments(__codes_raw.at(j));
                __codes_raw.at(j) = "'.";

                j++;
            }

            i = j - 1;
        }
    } catch (exception& e) {
        __cur_original = remove_spaces_tabs(__cur_original);
        error_message("Syntax error: incomplete brackets");
    }
}

Code* parse_line_code(string& line_code) {
    Code* c = new Code();
    string l = "";
    string r = "";
    string o = "";

    if (line_code.substr(0, 3) == "if ") {
        string lc = remove_spaces(line_code.substr(3));
        c->__header = __H_IF__;
        c->__body = parse_expression(lc);

        __flow_controls.push_back(c);
    } else if (line_code == "endif") {
        c->__header = __H_END_IF__;
        __flow_controls.push_back(c);
    } else if (line_code == "else") {
        c->__header = __H_ELSE__;
        __flow_controls.push_back(c);
    } else if (line_code.substr(0, 7) == "elseif ") {
        string lc = remove_spaces(line_code.substr(7));
        c->__header = __H_ELSE_IF__;
        c->__body = parse_expression(lc);

        __flow_controls.push_back(c);
    } else if (line_code.substr(0, 6) == "while ") {
        string lc = remove_spaces(line_code.substr(6));
        c->__header = __H_WHILE__;
        c->__body = parse_expression(lc);

        __flow_controls.push_back(c);
    } else if (line_code == "endwhile") {
        c->__header = __H_END_WHILE__;
        __flow_controls.push_back(c);
    } else if (line_code.substr(0, 4) == "for ") {
        string lc = remove_spaces(line_code.substr(4));
        c->__header = __H_FOR__;
        c->__body = parse_parameters(lc);

        if (((AST_Parameter*) c->__body)->__parameters.size() < 3) error_message("Syntax 'for' needs at least 3 parameters");

        __flow_controls.push_back(c);
        __functions_classes.push_back(c);

        if (((AST_Parameter*) c->__body)->__parameters.size() > 3) {
            c->__additional_header = __H_FOR_WITH_STEP__;
        } else {
            c->__additional_header = __H_FOR_WITHOUT_STEP__;
        }
    } else if (line_code == "endfor") {
        c->__header = __H_END_FOR__;
        __flow_controls.push_back(c);
    } else if (line_code.substr(0, 7) == "return ") {
        string ret = "__ret__";
        string lc = remove_spaces(line_code.substr(7));
        c->__header = __H_RETURN__;
        c->__body = parse_expression(ret);
        c->__body2 = parse_expression(lc);
    } else if (line_code == "return") {
        c->__header = __H_RETURN_VOID__;
    } else if (line_code.substr(0, 6) == "yield ") {
        string ret = "__ret__";
        string lc = remove_spaces(line_code.substr(6));
        c->__header = __H_YIELD__;
        c->__body = parse_expression(ret);
        c->__body2 = parse_expression(lc);
    } else if (line_code.substr(0, 9) == "function ") {
        string lc = remove_spaces(line_code.substr(9));
        c->__header = __H_FUNCTION__;
        c->__body = parse_function_declaration(lc);
        __functions_classes.push_back(c);
        
    } else if (line_code == "stop") {
        c->__header = __H_STOP__;
        __flow_controls.push_back(c);
    } else if (line_code.substr(0, 6) == "class ") {
        string lc = remove_spaces(line_code.substr(6));
        c->__header = __H_CLASS__;
        c->__body = parse_class_declaration(lc);
        __functions_classes.push_back(c);
        
    } else if (line_code == "endclass") {
        c->__header = __H_END_CLASS__;
        __functions_classes.push_back(c);
    } else if (line_code.substr(0, 6) == "field ") {
        string lc = remove_spaces(line_code.substr(6));
        c->__header = __H_FIELD__;
        c->__body = parse_field_declaration(lc);
        __functions_classes.push_back(c);
    } else if (line_code == "break") {
        c->__header = __H_EXIT_LOOP__;
    } else if (line_code.substr(0, 4) == "var ") {
        string lc = remove_spaces(line_code.substr(4));
        c->__header = __H_VAR__;
        c->__body = parse_var_declaration_name(lc);
        c->__body2 = parse_var_declaration_value(lc);

        __functions_classes.push_back(c);
    } else if (line_code.substr(0, 7) == "global ") {
        string lc = remove_spaces(line_code.substr(7));
        c->__header = __H_GLOBAL__;
        c->__body = parse_var_declaration_name(lc);
        c->__body2 = parse_var_declaration_value(lc);
    } else if (line_code.substr(0, 7) == "import ") {
        string lc = remove_spaces(line_code.substr(7));
        c->__header = __H_IMPORT__;
        c->__body = parse_import_declaration(lc);
        
    } else if (line_code == "start") {
        c->__header = __H_EMPTY__;
    } else if (is_variable_assignment(remove_spaces(line_code), l, r, o)) {
        c->__header = __H_VARIABLE_ASSIGNMENT__;
        c->__body = parse_expression(l);

        if (c->__body->__type == __AST_VARIABLE__) __functions_classes.push_back(c);
        
        if (o == "+") {
            c->__additional_header = __AST_OPERATOR_PLUS__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_PLUS__, parse_expression(r));
        } else if (o == "-") {
            c->__additional_header = __AST_OPERATOR_MINUS__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_MINUS__, parse_expression(r));
        } else if (o == "*") {
            c->__additional_header = __AST_OPERATOR_MULTIPLY__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_MULTIPLY__, parse_expression(r));
        } else if (o == "/") {
            c->__additional_header = __AST_OPERATOR_DIVIDE__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_DIVIDE__, parse_expression(r));
        } else if (o == "\\") {
            c->__additional_header = __AST_OPERATOR_INT_DIVIDE__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_INT_DIVIDE__, parse_expression(r));
        } else if (o == "%") {
            c->__additional_header = __AST_OPERATOR_MODULO__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_MODULO__, parse_expression(r));
        } else if (o == "&") {
            c->__additional_header = __AST_OPERATOR_CONCAT__;
            c->__body2 = new AST_BinaryExpression(parse_expression(l), __AST_OPERATOR_CONCAT__, parse_expression(r));
        } else {
            c->__body2 = parse_expression(r);
        }
        
    } else if (line_code.find("(") != string::npos && line_code.substr(line_code.length() - 1, 1) == ")") {
        string lc = remove_spaces(line_code);
        c->__header = __H_PROCEDURE_CALL__;
        c->__body = parse_function_call(lc);
        
    } else {
        error_message("Syntax error");
    }

    return c;
}

bool is_variable_assignment(string line_code, string& l, string& r, string& o) {
    bool result = false;
    vector<string> scr;
    string r2;

    if (line_code.find("=") != string::npos) {
        scr = split(line_code, "=", 2);

        if (scr.at(0).length() > 1) {
            r2 = scr.at(0).substr(scr.at(0).length() - 2, 1);
        } else {
            r2 = scr.at(0);
        }

        if (scr.at(0).find("(") == string::npos || scr.at(0).substr(scr.at(0).length() - 1, 1) == "]" || r2 == "]") {
            result = true;
            l = scr.at(0);
            r = scr.at(1);
            o = scr.at(0).substr(scr.at(0).length() - 1, 1);

            if (o == "+" || o == "-" || o == "*" || o == "/" || o == "\\" || o == "^" || o == "&" || o == "%") {
                l = l.substr(0, l.length() - 1);
            } else {
                o = "";
            }
        }
    }

    return result;
}

bool bracket_complete(string& line_code) {
    bool in_comment = false;
    bool in_quotes = false;
    int n_parentheses = 0;

    for (int i = 0; i < line_code.length(); i++) {
        string m = line_code.substr(i, 1);

        if (m == "'" || m == "#") {
            if (!in_quotes) in_comment = true;
        }

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_comment) {
            if (!in_quotes) {
                if (m == "(") n_parentheses++;
                if (m == ")") n_parentheses--;
                if (m == "[") n_parentheses++;
                if (m == "]") n_parentheses--;
                if (m == "{") n_parentheses++;
                if (m == "}") n_parentheses--;
            }
        }
    }

    return n_parentheses == 0;
}

string remove_tabs(string& line_code) {
    bool in_comment = false;
    bool in_quotes = false;
    string result = "";

    if (trim(line_code) == "") return " ";

    for (int i = 0; i < line_code.length(); i++){
        string m = line_code.substr(i, 1);

        if (m == "'" || m == "#") {
            if (!in_quotes) in_comment = true;
        }

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_comment) {
            if (!in_quotes) {
                if (m != "\t") {
                    if (m != ";") {
                        result += m;
                    } else {
                        if (!in_comment) result += "\n";
                    }
                }
            } else {
                result += m;
            }
        }
    }

    return result;
}

string remove_spaces(string line_code) {
    bool in_quotes = false;
    string result = "";

    for (int i = 0; i < line_code.length(); i++){
        string m = line_code.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes) {
            if (m != " ") {
                result += m;
            }
        } else {
            result += m;
        }
    }

    return result;
}

string remove_spaces_tabs(string& line_code) {
    bool in_quotes = false;
    string result = "";

    for (int i = 0; i < line_code.length(); i++){
        string m = line_code.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes) {
            if (m != "\t") {
                result += m;
            }
        } else {
            result += m;
        }
    }

    return trim(result);
}

string remove_comments(string line_code) {
    bool in_quotes = false;
    string result = "";

    for (int i = 0; i < line_code.length(); i++){
        string m = line_code.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes) {
            if (m == "'" || m == "#") {
                return result;
            }
        }
        
        result += m;
    }

    return result;
}
