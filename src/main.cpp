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
 Main
------------------------------------------------------------
*/

#include "header.h"
#ifdef _WIN32
    #include "global_win32.h"
#else
    #include "global.h"
#endif
#include "ast.h"
#include "variable.h"
#include "parser.h"
#include "expression_parser.h"
#include "flow_control.h"
#include "function.h"
#include "walker.h"
#include "module.h"
#include "module_standardio.h"
#include "module_core.h"

int main(int argc, char* argv[]) {
    parse_arguments(argc, argv);
    
    try {
        uint_fast32_t caller_id = 1;
        uint_fast32_t start = 0;
        
        if (!__default_mode) {
            parse_code(argv[1]);
        } else {
            parse_code(const_cast<char*>(__default_file.c_str()));
        }

        __walked = true;

        parse_flow_control();
        parse_function_class();
        init_builtin(argc, argv);

        walk(start, caller_id);

        if (__gui_event_loop != 0) {
            __stop_procedure = false;
            uint_fast32_t caller_id_gui = 1;
            __gui_module->__call(__gui_event_loop, NULL, NULL, caller_id_gui);
        } else {
            if (__event_loop != NULL) {
                __stop_procedure = false;
                uint_fast32_t caller_id_el = 1;
                call_function(__event_loop, caller_id_el);
            }
        }

        return EXIT_SUCCESS;
    } catch (exception& e) {
        string error = e.what();
        error_message("Runtime error: " + error);

        return EXIT_FAILURE;
    }
}
