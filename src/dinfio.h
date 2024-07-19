/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2024. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Init
------------------------------------------------------------
*/

#include "header.h"
#ifdef _WIN32
    #include "global_win32.h"
#else
    #include "global.h"
#endif
#include "ast.h"
#include "parser.h"
#include "expression_parser.h"
#include "variable.h"
#include "control_flow.h"
#include "function.h"
#include "walker.h"
#include "module.h"
#include "module_core.h"
#include "module_standardio.h"

int dinfio_init(int argc, char* argv[]) {
    parse_arguments(argc, argv);

    try {
        uint_fast32_t caller_id = 1;
        uint_fast32_t start = 0;
        bool stop_loop = false;
        bool stop_procedure = false;
        
        if (!__default_mode) {
            parse_code(argv[1]);
        } else {
            parse_code(const_cast<char*>(__default_file.c_str()));
        }

        __walked = true;

        parse_flow_control();
        parse_function_class();
        init_builtin(argc, argv);

        walk(start, caller_id, stop_loop, stop_procedure);

        if (__gui_event_loop != 0) {
            uint_fast32_t caller_id_gui = 1;
            __gui_module->__call(__gui_event_loop, NULL, NULL, caller_id_gui);
        } else {
            if (__event_loop != NULL) {
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
