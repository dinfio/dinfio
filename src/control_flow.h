/*
------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2025. All Rights Reserved.
------------------------------------------------------------
 Platform: Linux, macOS, Windows
------------------------------------------------------------
 Control Flow
------------------------------------------------------------
*/

void loop_for(AST* body, uint_fast32_t& start_i, uint_fast8_t& additional_header, uint_fast32_t& endclause, uint_fast32_t& caller_id, bool& stop_loop, bool& stop_procedure) {
    AST* a_counter = ((AST_Parameter*) body)->__parameters[0];
    AST* a_start = ((AST_Parameter*) body)->__parameters[1];
    AST* a_end = ((AST_Parameter*) body)->__parameters[2];

    double step = 0;
    __cur_i = start_i;

    if (a_counter->__type != __AST_VARIABLE__) error_message("Parameter 'counter' must be a variable");

    if (additional_header == __H_FOR_WITH_STEP__) {
        AST* st = ((AST_Parameter*) body)->__parameters[3];
        gc<DataType> dst = get_value(st, caller_id);
        step = dst->__value_double;

        if (step == 0) error_message("Unable to use 0 in the parameter 'step'");
    } else {
        step = 1;
    }

    gc<DataType> d_start = get_value(a_start, caller_id);
    gc<DataType> d_end = get_value(a_end, caller_id);

    double start = d_start->__value_double;
    double end = d_end->__value_double;

    AST_Variable* e = (AST_Variable*) a_counter;
    gc<DataType> counter;
    string c = to_string(caller_id);

    if (__variables.count(c + e->__identifier) == 1) {
        counter = __variables.at(c + e->__identifier);
        counter->__type = __TYPE_DOUBLE__;
    } else {
        counter = new_gc<DataType>(__TYPE_DOUBLE__);
        __variables.insert(pair<string, gc<DataType>>(c + e->__identifier, counter));
    }

    if (step > 0) {
        for (double i = start; i <= end; i += step) {
            if (stop_loop || stop_procedure) break;
            
            counter->__value_double = i;
            walk(start_i + 1, caller_id, stop_loop, stop_procedure);
        }
    } else {
        for (double i = start; i >= end; i += step) {
            if (stop_loop || stop_procedure) break;

            counter->__value_double = i;
            walk(start_i + 1, caller_id, stop_loop, stop_procedure);
        }
    }

    stop_loop = false;
    walk(endclause + 1, caller_id, stop_loop, stop_procedure);
}

void loop_while(AST* body, uint_fast32_t& start_i, uint_fast32_t& endclause, uint_fast32_t& caller_id, bool& stop_loop, bool& stop_procedure) {
    __cur_i = start_i;
    gc<DataType> dc = get_value(body, caller_id);
    bool condition = dc->__value_bool;

    while (condition) {
        if (stop_loop || stop_procedure) break;
        walk(start_i + 1, caller_id, stop_loop, stop_procedure);

        dc = get_value(body, caller_id);
        condition = dc->__value_bool;
    }

    stop_loop = false;
    walk(endclause + 1, caller_id, stop_loop, stop_procedure);
}

void branch_if(AST* body, uint_fast32_t& start_i, uint_fast32_t& endclause, uint_fast32_t& endclause2, bool is_elseif, uint_fast32_t& caller_id, bool& stop_loop, bool& stop_procedure) {
    __cur_i = start_i;
    gc<DataType> dc = get_value(body, caller_id);
    bool condition = dc->__value_bool;

    if (condition) {
        walk(start_i + 1, caller_id, stop_loop, stop_procedure);
    } else {
        if (endclause2 != 0) {
            Code* c = __codes[endclause2];

            if (c->__header == __H_ELSE_IF__) {
                __cur_i = endclause2;
                branch_if(c->__body, endclause2, c->__endclause, c->__endclause2, true, caller_id, stop_loop, stop_procedure);
            } else {
                walk(endclause2 + 1, caller_id, stop_loop, stop_procedure);
            }
        }
    }

    if (!is_elseif) walk(endclause + 1, caller_id, stop_loop, stop_procedure);
}

void parse_flow_control() {
    uint_fast32_t count = __flow_controls.size();

    for (uint_fast32_t i = 0; i < count; i++) {
        Code* c = __flow_controls.at(i);
        __cur_i = c->__index;

        if (c->__header == __H_IF__ || c->__header == __H_ELSE_IF__) {
            uint_fast32_t n_if = 0;
            uint_fast32_t i_else = 0;
            uint_fast32_t i_endif = 0;

            for (uint_fast32_t j = i + 1; j < count; j++) {
                if (j >= count) break;
                Code* d = __flow_controls.at(j);

                if (d->__header == __H_STOP__) break;
                if (d->__header == __H_IF__) n_if++;

                if (d->__header == __H_END_IF__) {
                    if (n_if == 0) {
                        i_endif = d->__index;
                        break;
                    }

                    if (n_if > 0) n_if--;
                }

                if (n_if == 0 && (d->__header == __H_ELSE__ || d->__header == __H_ELSE_IF__) && i_else == 0) i_else = d->__index;
            }

            if (i_endif == 0) error_message("No 'endif' found");

            c->__endclause = i_endif;
            c->__endclause2 = i_else;
        } else if (c->__header == __H_FOR__) {
            uint_fast32_t n_for = 0;
            uint_fast32_t i_endfor = 0;

            for (uint_fast32_t j = i + 1; j < count; j++) {
                if (j >= count) break;
                Code* d = __flow_controls.at(j);

                if (d->__header == __H_STOP__) break;
                if (d->__header == __H_FOR__) n_for++;

                if (d->__header == __H_END_FOR__) {
                    if (n_for == 0) {
                        i_endfor = d->__index;
                        break;
                    }

                    if (n_for > 0) n_for--;
                }
            }

            if (i_endfor == 0) error_message("No 'endfor' found");

            c->__endclause = i_endfor;
        } else if (c->__header == __H_WHILE__) {
            uint_fast32_t n_while = 0;
            uint_fast32_t i_endwhile = 0;

            for (uint_fast32_t j = i + 1; j < count; j++) {
                if (j >= count) break;
                Code* d = __flow_controls.at(j);

                if (d->__header == __H_STOP__) break;
                if (d->__header == __H_WHILE__) n_while++;

                if (d->__header == __H_END_WHILE__) {
                    if (n_while == 0) {
                        i_endwhile = d->__index;
                        break;
                    }

                    if (n_while > 0) n_while--;
                }
            }

            if (i_endwhile == 0) error_message("No 'endwhile' found");

            c->__endclause = i_endwhile;
        }
    }
}
