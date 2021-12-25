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
 Global
------------------------------------------------------------
*/

class Base {
public:
    uint_fast8_t __type;
};

namespace Color {
    enum ColorCode {
        FG_RED = 31,
        FG_GREEN = 32,
        FG_BLUE = 34,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    class Modifier {
        ColorCode code;
        public:
            Modifier(ColorCode pCode) : code(pCode) {}
        friend ostream& operator<<(ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

void parse_arguments(int argc, char* argv[]) {
    if (argc == 2) {
        string a = argv[1];

        if (a == "-v" || a == "--version") {
            cout << "Dinfio Interpreter\n\nVersion: " << __DINFIO_VERSION__ + " (" + __DINFIO_PLATFORM__ + ")" << "\nBuild date: " << __DINFIO_BUILD_DATE__ << "\nPlease visit https://dinfio.org/ for more information.\n";
            exit(0);
        }

        if (a == "-h" || a == "--help") {
            __default_mode = true;
            __default_file = __DINFIO_PATH__ + "help.fio";
        }
    }

    if (argc == 3) {
        string a = argv[2];
        if (a == "-i") __interactive_mode = true;
    }

    if (argc == 1) {
        __default_mode = true;
        __default_file = __DINFIO_PATH__ + "interactive.fio";
    }
}

void error_message(string error) {
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);

    if (!__interactive_mode) {
        cout << endl << red << error << def << endl << endl;

        if (!__walked) {
            cout << "Syntax: " << __cur_original << endl;
            cout << "Line: " << __cur_file_line << endl;
            cout << "File: " << __cur_file << endl;
        } else {
            cout << "Syntax: " << __codes_info[__cur_i]->__original << endl;
            cout << "Line: " << __codes_info[__cur_i]->__line << endl;
            cout << "File: " << __codes_info[__cur_i]->__file << endl;
        }
    } else {
        cout << red << error << def << endl;
    }

    exit(EXIT_FAILURE);
}

void error_message_param(string func) {
    error_message("Function " + func + "() needs at least one parameter");
}

void error_message_params(string func, uint8_t size) {
    if (size <= 1) {
        error_message_param(func);
    } else {
        error_message("Function " + func + "() needs at least " + to_string(size) + " parameters");
    }
}

string read_file(char* filename) {
    string result = "";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        return NULL;
    }

    char* line = NULL;
    size_t len = 0;

    while ((getline(&line, &len, fp)) != -1) {
        result += line;
    }

    fclose(fp);
    if (line) free(line);

    return result;
}

vector<string> get_source(char* filename) {
    vector<string> result;
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        Color::Modifier red(Color::FG_RED);
        Color::Modifier def(Color::FG_DEFAULT);

        cout << red << "Dinfio Interpreter: " << def << "No such file or directory: " << filename << endl;
        exit(EXIT_FAILURE);

        return result;
    }

    char* line = NULL;
    size_t len = 0;

    while ((getline(&line, &len, fp)) != -1) {
        string ln = line;

        replace_all(ln, "\r", "");
        replace_all(ln, "\n", "");

        result.push_back(ln);
    }

    fclose(fp);
    if (line) free(line);

    return result;
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

int random_int(int min, int max) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(min, max);

    return distr(generator);
}

bool is_number(const string& s) {
    char* p;
    strtod(s.c_str(), &p);
    return *p == 0;
}

bool valid_name(const string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.' || s[i] == ',' || s[i] == ':' || s[i] == '[' || s[i] == ']' ||
            s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == '-' ||
            s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '\\' || s[i] == '%' || s[i] == '&' || s[i] == '^' || s[i] == '|') return false;
    }

    return true;
}

string trim(const string& s) {
    string::const_iterator it = s.begin();

    while (it != s.end() && isspace(*it))
        it++;

    string::const_reverse_iterator rit = s.rbegin();

    while (rit.base() != it && isspace(*rit))
        rit++;

    return string(it, rit.base());
}

string lcase(string s) {
    for_each(s.begin(), s.end(), [](char & c){
        c = tolower(c);
    });

    return s;
}

string ucase(string s) {
    for_each(s.begin(), s.end(), [](char & c){
        c = toupper(c);
    });

    return s;
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

string repeat(string str, int n) {
    string result = "";

    for (int i = 1; i <= n; i++) {
        result += str;
    }

    return result;
}

string dirname(const string& fname) {
    size_t pos = fname.find_last_of("\\/");
    return (string::npos == pos) ? "" : fname.substr(0, pos);
}

string fname(const string& filename) {
    size_t pos = filename.find_last_of("\\/");
    return (string::npos == pos) ? "" : filename.substr(pos + 1);
}

long get_file_size(string filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

string full_path(char* filename) {
    char* path = realpath(filename, NULL);

    if(path == NULL) {
        return "";
    } else {
        string result = path;
        return result;
    }
}

char* full_path_char(char* filename) {
    char* path = realpath(filename, NULL);

    if(path == NULL) {
        return NULL;
    } else {
        return path;
    }
}
