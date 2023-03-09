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
 Expression Parser
------------------------------------------------------------
*/

AST* parse_expression(string& expression) {
    if (is_number(expression)) {
        return new AST_Double(stod(expression));
    } else if (expression == "true") {
        return new AST_Bool(true);
    } else if (expression == "false") {
        return new AST_Bool(false);
    } else if (expression == "nothing") {
        return new AST(__AST_NULL__);
    } else if (expression.substr(0, 1) == "[" && expression.substr(expression.length() - 1, 1) == "]") {
        return parse_array_notation(expression);
    } else if (expression.substr(0, 1) == "{" && expression.substr(expression.length() - 1, 1) == "}") {
        return parse_object_notation(expression);
    }

    int operator_precedence = 0, operator_index = 0, n_parentheses = 0;
    int n_func_parentheses = 0, n_in_func_parentheses = 0, n_square_brackets = 0;
    bool in_quotes = false;
    string opd_left = "";
    string opd_right = "";
    string operator_name = "";

    expression = __remove_unused_parentheses(expression);

    for (int i = 0; i < expression.length(); i++) {
        string m = expression.substr(i, 1);
        string mm = expression.substr(i, 2);
        string p = "";
        string before_piece = "";

        if (i > 0) p = expression.substr(i - 1, 1);
        if (i > 0) before_piece = p;
        else before_piece = " ";

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes) {
            if (m == "(") {
                int ascii = before_piece[0];

                if (before_piece == "_" || (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122) || (ascii >= 48 && ascii <= 57)) {
                    if (n_func_parentheses == 0) {
                        n_func_parentheses++;
                    } else {
                        n_in_func_parentheses++;
                    }
                } else {
                    if (n_func_parentheses != 0) n_in_func_parentheses++;
                }

                if (n_func_parentheses == 0 && n_in_func_parentheses == 0) n_parentheses++;
            }

            if (m == "[") n_square_brackets++;
            if (m == "]") n_square_brackets--;

            if (m == ")") {
                if (n_func_parentheses == 0 && n_in_func_parentheses == 0) n_parentheses--;

                if (n_in_func_parentheses == 0 && n_func_parentheses > 0) n_func_parentheses--;
                if (n_func_parentheses != 0 && n_in_func_parentheses > 0) n_in_func_parentheses--;
            }
        }

        if (!in_quotes && n_parentheses == 0 && n_func_parentheses == 0 && n_square_brackets == 0) {
            string o = "";

            if (mm == "&&" || mm == "||" || mm == "^^" || mm == "==" || mm == "!=" || mm == "<=" || mm == ">=") {
                o = mm;
            } else if (m == "+" || m == "*" || m == "/" || m == "\\" || m == "%" || m == "<" || m == ">") {
                o = m;
            } else if (m == "-") {
                string le = "";
                if (i > 0) le = left(expression, i);

                if (i > 0 && !__is_operator(le)) {
                    o = m;
                }
            } else if (m == "&" && p != "&") {
                o = m;
            } else if (m == "^" && p != "^") {
                o = m;
            }

            if (o != "") {
                int precedence = __get_precedence(o);

                if (precedence == 1) {   // Exponentiation operator
                    if (precedence > operator_precedence) {
                        operator_index = i;
                        operator_name = o;
                        operator_precedence = precedence;
                    }
                } else {
                    if (precedence >= operator_precedence) {
                        operator_index = i;
                        operator_name = o;
                        operator_precedence = precedence;
                    }
                }
            }
        }
    }

    if (operator_index > 0) {
        uint_fast8_t opr;
        opd_left = left(expression, operator_index);
        opd_right = expression.substr(operator_index + operator_name.length());

        if      (operator_name == "+")  opr = __AST_OPERATOR_PLUS__;
        else if (operator_name == "-")  opr = __AST_OPERATOR_MINUS__;
        else if (operator_name == "*")  opr = __AST_OPERATOR_MULTIPLY__;
        else if (operator_name == "/")  opr = __AST_OPERATOR_DIVIDE__;
        else if (operator_name == "\\") opr = __AST_OPERATOR_INT_DIVIDE__;
        else if (operator_name == "%")  opr = __AST_OPERATOR_MODULO__;
        else if (operator_name == "&")  opr = __AST_OPERATOR_CONCAT__;
        else if (operator_name == "^")  opr = __AST_OPERATOR_EXPONENT__;
        else if (operator_name == "&&") opr = __AST_OPERATOR_AND__;
        else if (operator_name == "||") opr = __AST_OPERATOR_OR__;
        else if (operator_name == "^^") opr = __AST_OPERATOR_XOR__;
        else if (operator_name == "==") opr = __AST_OPERATOR_EQUAL__;
        else if (operator_name == "!=") opr = __AST_OPERATOR_NOT_EQUAL__;
        else if (operator_name == "<")  opr = __AST_OPERATOR_LESS__;
        else if (operator_name == ">")  opr = __AST_OPERATOR_GREATER__;
        else if (operator_name == "<=") opr = __AST_OPERATOR_LESS_EQUAL__;
        else if (operator_name == ">=") opr = __AST_OPERATOR_GREATER_EQUAL__;

        AST* l = parse_expression(opd_left);
        AST* r = parse_expression(opd_right);

        return new AST_BinaryExpression(l, opr, r);
    } else {
        if (expression.substr(0, 1) == "\"" && expression.substr(expression.length() - 1, 1) == "\"") {
            string s = expression.substr(1, expression.length() - 2);
            replace_all(s, "\\n", "\n");
            replace_all(s, "\\r", "\r");
            replace_all(s, "\\t", "\t");
            replace_all(s, "\\q", "\"");
            replace_all(s, "\\b", "\\");

            return new AST_String(s);
        } else if (left(expression, 1) == "-") {
            string v = expression.substr(1);
            AST* l = new AST_Double(0);
            AST* r = parse_expression(v);

            return new AST_BinaryExpression(l, __AST_OPERATOR_MINUS__, r);
        } else if (left(expression, 1) == "!") {
            string v = expression.substr(1);
            AST* l = new AST_Bool(false);
            AST* r = parse_expression(v);

            return new AST_BinaryExpression(l, __AST_OPERATOR_NOT__, r);
        } else if (is_number(expression)) {
            return new AST_Double(stod(expression));
        } else if (right(expression, 1) == ")") {
            return parse_function_call(expression);
        } else if (is_there_object(expression)) {
            return parse_object(expression);
        } else if (right(expression, 1) == "]") {
            return parse_array(expression);
        } else if (expression.length() > 1 && expression.substr(expression.length() - 1, 1) == "b" && is_number(expression.substr(0, expression.length() - 1))) {
            int b = stoi(expression.substr(0, expression.length() - 1), nullptr, 2);
            return new AST_Double(b);
        } else {
            return new AST_Variable(expression);
        }
    }
}

AST* parse_function_call(string& expression) {
    int ip = expression.find("(");
    string func_name = left(expression, ip);
    string func_params = expression.substr(ip + 1, expression.length() - ip - 2);
    vector<string> parameters = parse_function_parameters(func_params);

    if (is_there_object(func_name)) {
        AST_Object* o = parse_object(func_name);
        string id = ((AST_Variable*) (o->__attributes[o->__attributes.size() - 1]))->__identifier;
        AST_ObjectFunctionCall* r = new AST_ObjectFunctionCall(o, id);

        for (int i = 0; i < parameters.size(); i++) {
            r->__parameters.push_back(parse_expression(parameters[i]));
        }

        return r;
    } else {
        AST_FunctionCall* r = new AST_FunctionCall(func_name);
        r->__address = 0;

        for (int i = 0; i < parameters.size(); i++) {
            r->__parameters.push_back(parse_expression(parameters[i]));
        }

        return r;
    }
}

AST_Array* parse_array(string& expression) {
    vector<string> elements = parse_array_elements(expression);
    AST_Array* result = new AST_Array(elements[0]);

    for (int i = 1; i < elements.size(); i++) {
        result->__indices.push_back(parse_expression(elements[i]));
    }

    return result;
}

AST_Object* parse_object(string& expression) {
    vector<string> attributes = parse_object_attributes(expression);
    AST_Object* result = new AST_Object(attributes[0]);
    
    result->__array_holder = NULL;
    if (right(attributes[0], 1) == "]") result->__array_holder = parse_array(attributes[0]);

    for (int i = 1; i < attributes.size(); i++) {
        string a = attributes[i];

        if (right(a, 1) == "]") {
            result->__attributes.push_back(parse_array(a));
        } else {
            result->__attributes.push_back(new AST_Variable(a));
        }
    }

    return result;
}

AST_FunctionCall* parse_function_declaration(string& expression) {
    int ip = expression.find("(");
    string func_name = left(expression, ip);
    string func_params = expression.substr(ip + 1, expression.length() - ip - 2);
    vector<string> parameters = parse_function_parameters(func_params);

    AST_FunctionCall* r = new AST_FunctionCall(func_name);
    r->__required_params = parameters.size();

    for (int i = 0; i < parameters.size(); i++) {
        vector<string> p = split(parameters[i], ":");

        if (p.size() > 1) {
            if (p[0] == "ref") {
                r->__parameters_type.push_back(__AST_PARAMETER_REF__);
            } else {
                r->__parameters_type.push_back(__AST_PARAMETER_ANY__);
            }

            vector<string> q = split(p[1], "=", 2);

            if (q.size() > 1) {
                r->__parameters.push_back(new AST_Variable(q[0]));
                r->__optional_parameters.push_back(parse_expression(q[1]));

                if (r->__required_params == parameters.size()) {
                    r->__required_params = i;
                }
            } else {
                r->__parameters.push_back(new AST_Variable(p[1]));
                r->__optional_parameters.push_back(NULL);

                if (r->__required_params != parameters.size()) {
                    error_message("Parameter '" + p[1] + "' must have default value");
                }
            }
        } else {
            r->__parameters_type.push_back(__AST_PARAMETER_ANY__);

            vector<string> q = split(p[0], "=", 2);

            if (q.size() > 1) {
                r->__parameters.push_back(new AST_Variable(q[0]));
                r->__optional_parameters.push_back(parse_expression(q[1]));

                if (r->__required_params == parameters.size()) {
                    r->__required_params = i;
                }
            } else {
                r->__parameters.push_back(new AST_Variable(p[0]));
                r->__optional_parameters.push_back(NULL);

                if (r->__required_params != parameters.size()) {
                    error_message("Parameter '" + p[0] + "' must have default value");
                }
            }
        }
    }

    return r;
}

AST_Parameter* parse_class_declaration(string& expression) {
    AST_Parameter* result = new AST_Parameter();

    bool in_quotes = false;
    string obj = "";

    for (int i = 0; i < expression.length(); i++) {
        string m = expression.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (m == "," || m == ":") {
            result->__parameters.push_back(new AST_Variable(obj));
            obj = "";
            m = "";
        }

        obj += m;
    }

    if (obj != "") {
        result->__parameters.push_back(new AST_Variable(obj));
    }

    return result;
}

AST_Parameter* parse_field_declaration(string& expression) {
    vector<string> parameters = parse_function_parameters(expression);

    AST_Parameter* r = new AST_Parameter();

    for (int i = 0; i < parameters.size(); i++) {
        vector<string> p = split(parameters[i], ":");

        if (p.size() > 1) {
            r->__parameters.push_back(new AST_Variable(p[1]));
        } else {
            r->__parameters.push_back(new AST_Variable(p[0]));
        }
    }

    return r;
}

AST_Parameter* parse_var_declaration_name(string& expression) {
    vector<string> parameters = parse_function_parameters(expression);

    AST_Parameter* r = new AST_Parameter();

    for (int i = 0; i < parameters.size(); i++) {
        vector<string> q = split(parameters[i], "=", 2);
        vector<string> p = split(q[0], ":");

        if (p.size() > 1) {
            if (!valid_name(p[1])) error_message("Invalid variable name '" + p[1] + "'");
            r->__parameters.push_back(new AST_Variable(p[1]));
        } else {
            if (!valid_name(p[0])) error_message("Invalid variable name '" + p[0] + "'");
            r->__parameters.push_back(new AST_Variable(p[0]));
        }
    }

    return r;
}

AST_Parameter* parse_var_declaration_value(string& expression) {
    vector<string> parameters = parse_function_parameters(expression);

    AST_Parameter* r = new AST_Parameter();

    for (int i = 0; i < parameters.size(); i++) {
        vector<string> p = split(parameters[i], "=", 2);

        if (p.size() > 1) {
            r->__parameters.push_back(parse_expression(p[1]));
        } else {
            r->__parameters.push_back(new AST(__AST_NULL__));
        }
    }

    return r;
}

AST_ObjectNotation* parse_object_notation(string& expression) {
    string func_params = expression.substr(1, expression.length() - 2);
    vector<string> parameters = parse_function_parameters(func_params);

    AST_ObjectNotation* r = new AST_ObjectNotation();

    for (int i = 0; i < parameters.size(); i++) {
        vector<string> p = split(parameters[i], ":", 2);

        if (p.size() < 2) error_message("Expected attribute name");
        
        r->__attributes.push_back(parse_expression(p[1]));
        r->__names.push_back(p[0]);
    }

    return r;
}

AST_ArrayNotation* parse_array_notation(string& expression) {
    string func_params = expression.substr(1, expression.length() - 2);
    vector<string> parameters = parse_function_parameters(func_params);

    AST_ArrayNotation* r = new AST_ArrayNotation();

    for (int i = 0; i < parameters.size(); i++) {
        r->__elements.push_back(parse_expression(parameters[i]));
    }

    return r;
}

AST_Parameter* parse_parameters(string& expression) {
    AST_Parameter* result = new AST_Parameter();

    bool in_quotes = false;
    int n_parentheses = 0;
    string obj = "";

    for (int i = 0; i < expression.length(); i++) {
        string m = expression.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "[") n_parentheses++;
        if (!in_quotes && m == "]") n_parentheses--;
        if (!in_quotes && m == "(") n_parentheses++;
        if (!in_quotes && m == ")") n_parentheses--;
        if (!in_quotes && m == "{") n_parentheses++;
        if (!in_quotes && m == "}") n_parentheses--;

        if (!in_quotes && m == ",") {
            if (n_parentheses == 0) {
                result->__parameters.push_back(parse_expression(obj));
                obj = "";
                m = "";
            }
        }

        obj += m;
    }

    if (obj != "") {
        result->__parameters.push_back(parse_expression(obj));
    }

    return result;
}

vector<string> parse_array_elements(string& name) {
    vector<string> result;

    bool in_quotes = false;
    int n_square_brackets = 0;
    int first_pos = 0;
    string temp = "";

    for (int i = 0; i < name.length(); i++) {
        string m = name.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "["){
            if (first_pos == 0) {
                first_pos = i;
                result.push_back(name.substr(0, first_pos));
            }

            if (n_square_brackets == 0) temp = "";
            n_square_brackets++;
        }

        if (!in_quotes && m == "]"){
            n_square_brackets--;

            if (n_square_brackets == 0) {
                string t = temp.substr(1);
                result.push_back(t);
            }
            
        }

        temp += m;
    }

    return result;
}

vector<string> parse_object_attributes(string& name) {
    vector<string> result;

    bool in_quotes = false;
    int n_square_brackets = 0;
    int n_parentheses = 0;
    string obj = "";

    for (int i = 0; i < name.length(); i++) {
        string m = name.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "[") n_square_brackets++;
        if (!in_quotes && m == "]") n_square_brackets--;
        if (!in_quotes && m == "(") n_parentheses++;
        if (!in_quotes && m == ")") n_parentheses--;

        if (!in_quotes && m == ".") {
            if (n_square_brackets == 0 && n_parentheses == 0) {
                result.push_back(obj);
                obj = "";
                m = "";
            }
        }

        obj += m;
    }

    if (obj != "") {
        result.push_back(obj);
    }

    return result;
}

vector<string> parse_function_parameters(string& name) {
    vector<string> result;

    bool in_quotes = false;
    int n_parentheses = 0;
    string obj = "";

    for (int i = 0; i < name.length(); i++) {
        string m = name.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "[") n_parentheses++;
        if (!in_quotes && m == "]") n_parentheses--;
        if (!in_quotes && m == "(") n_parentheses++;
        if (!in_quotes && m == ")") n_parentheses--;
        if (!in_quotes && m == "{") n_parentheses++;
        if (!in_quotes && m == "}") n_parentheses--;

        if (!in_quotes && m == ",") {
            if (n_parentheses == 0) {
                result.push_back(obj);
                obj = "";
                m = "";
            }
        }

        obj += m;
    }

    if (obj != "") {
        result.push_back(obj);
    }

    return result;
}

AST_Parameter* parse_import_declaration(string& expression) {
    vector<string> parameters = parse_function_parameters(expression);
    AST_Parameter* r = new AST_Parameter();

    for (int i = 0; i < parameters.size(); i++) {
        string p = parameters[i];

        if (left(p, 1) == "\"" && right(p, 1) == "\"") {
            r->__parameters.push_back(new AST_Variable(p.substr(1, p.length() - 2)));
        } else {
            r->__parameters.push_back(new AST_Variable(p));
        }
    }

    return r;
}

bool is_there_object(string& expression) {
    bool in_quotes = false;
    int n_parentheses = 0;

    for (int i = 0; i < expression.length(); i++) {
        string m = expression.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "[") n_parentheses++;
        if (!in_quotes && m == "]") n_parentheses--;
        if (!in_quotes && m == "(") n_parentheses++;
        if (!in_quotes && m == ")") n_parentheses--;
        if (!in_quotes && m == "{") n_parentheses++;
        if (!in_quotes && m == "}") n_parentheses--;

        if (!in_quotes && n_parentheses == 0 && m == ".") return true;
    }

    return false;
}

string __remove_unused_parentheses(string& expression) {
    string e = expression;
    bool symmetric = false;

    do {
        if (left(e, 1) == "(" && right(e, 1) == ")") {
            string ex = e.substr(1, e.length() - 2);

            if (__parentheses_symmetric(ex)) {
                e = ex;
                symmetric = true;
            } else {
                symmetric = false;
            }
        } else {
            symmetric = false;
        }
    } while (symmetric);

    return e;
}

bool __parentheses_symmetric(string& e) {
    bool result = false;
    bool in_quotes = false;
    int n_parentheses = 0;

    for (int i = 0; i < e.length(); i++) {
        string m = e.substr(i, 1);

        if (m == "\"") {
            if (in_quotes) in_quotes = false;
            else in_quotes = true;
        }

        if (!in_quotes && m == "(") n_parentheses++;

        if (!in_quotes && m == ")") {
            n_parentheses--;
            if (n_parentheses < 0) return false;
        }

        if (n_parentheses == 0) result = true;
        else result = false;
    }

    return result;
}

bool __is_operator(string& e) {
    string o = right(e, 1);

    if      (o == "+") return true;
    else if (o == "-") return true;
    else if (o == "*") return true;
    else if (o == "/") return true;
    else if (o == "\\") return true;
    else if (o == "%") return true;
    else if (o == "<") return true;
    else if (o == ">") return true;
    else if (o == "=") return true;
    else if (o == "!") return true;
    else if (o == "&") return true;
    else if (o == "|") return true;
    else if (o == "^") return true;

    return false;
}

int __get_precedence(string& o) {
    if (o == "^") return 1;
    else if (o == "*" || o == "/" || o == "%" || o == "\\") return 2;
    else if (o == "+" || o == "-") return 3;
    else if (o == "&") return 4;
    else if (o == "<" || o == ">" || o == "<=" || o == ">=") return 5;
    else if (o == "==" || o == "!=") return 6;
    else if (o == "&&") return 7;
    else if (o == "||") return 8;
    else if (o == "^^") return 9;
    else return 10;
}
