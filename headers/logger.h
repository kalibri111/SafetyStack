//
// Created by kalibri on 30.09.2020.
//

#ifndef SAFETYSTACK_LOGGER_H
#define SAFETYSTACK_LOGGER_H

#include "stack.h"
#include "../lib/htmlib.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "safety_stuff.h"

//----------------------------------------------------------------------------------------------------------
#define head(header)         {__head__(log_file) fputs((header), log_file);}
#define body                 __body__(log_file)
#define div(cls_name)        __div__(log_file, cls_name, __unique_div__(__LINE__))
#define p(cls_name, text)    {__p__(log_file , cls_name, __unique_p__(__LINE__)) fputs(text, log_file);}
#define h(cls_name, text)    {__h__(log_file , cls_name, __unique_h__(__LINE__)) fputs(text, log_file);}
//----------------------------------------------------------------------------------------------------------

struct SafetyStack;

/*
 * put this function in top of file
 * it writes html header, links bootstrap and writes body tag
 * */
void init_log() {
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    head("StackLog")
    link_bootstrap(log_file);
    body
    fclose(log_file);
}

/*
 * pseudo html written log
 * */
void __overload__(make_html_log)(SafetyStack* s_stack, stack_t* stack, STACK_TYPE* buffer, int max_size, int size,
                   const char* file_name, const char* function, int line, sstack_err err) {
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    {
        div("\"container row justify-content-center\"")
        {
            div("\"col-6\"")
            {
                div("\"card\"")
                char* error_msg = (char*)calloc(20, sizeof(char));
                switch (err) {
                    case STACK_BAD_SIZE:
                        error_msg = "STACK_BAD_SIZE";
                        break;
                    case STACK_BAD_MAX_SIZE:
                        error_msg = "STACK_BAD_MAX_SIZE";
                        break;
                    case STACK_NULL_BUFFER:
                        error_msg = "STACK_NULL_BUFFER";
                        break;
                    case STACK_NULL_RAW_STACK:
                        error_msg = "STACK_NULL_RAW_STACK";
                        break;
                    case STACK_NULL_SSTACK:
                        error_msg = "STACK_NULL_SSTACK";
                        break;
                    case STACK_CANARY_ERROR:
                        error_msg = "STACK_CANARY_ERROR";
                        break;
                    case STACK_CHECKSUM_ERROR:
                        error_msg = "STACK_CHECKSUM_ERROR";
                        break;
                }
                char stack_address[60] = {};
                sprintf(stack_address, "SafetyStack %X because of %s", s_stack, error_msg);
                h("\"card-title\"", stack_address);
                if (s_stack) {
                    {
                        div("\"container\"")
                        {
                            div("\"row\"")
                            {
                                div("\"col-4\"")
                                {
#ifdef CANARY_PROTECT
                                    p("\"card-text\"", "left stack canary")
                                    p("\"card-text\"", "right stack canary")
#endif
                                    p("\"card-text\"", "size")
                                    p("\"card-text\"", "capacity")
#ifdef HASH_PROTECT
                                    p("\"card-text\"", "check sum")
#endif
                                }
                            }
                            {
                                div("\"col-4\"")
                                {
                                    char __buffer[30] = {};
#ifdef CANARY_PROTECT
                                    sprintf(__buffer, "%llx", s_stack->canary_left);

                                    p("\"card-text\"", __buffer)

                                    sprintf(__buffer, "%llx", s_stack->canary_right);

                                    p("\"card-text\"", __buffer)
#endif

                                    sprintf(__buffer, "%d", s_stack->stack.size);

                                    p("\"card-text\"", __buffer)

                                    sprintf(__buffer, "%d", s_stack->stack.max_size);

                                    p("\"card-text\"", __buffer)
#ifdef HASH_PROTECT
                                    sprintf(__buffer, "%d", s_stack->check_sum);

                                    p("\"card-text\"", __buffer)
#endif
                                }
                            }
                        }
                        {
                            div("\"row\"")
                            {
                                div("\"col-2\"")
                                p("\"card-text\"", "buffer: ")
                            }
                            {
                                div("\"col-4\"")

                                char index_buffer[30] = {};
                                for (int i = 0; i < s_stack->stack.max_size; ++i) {
                                    STACK_TYPE value = s_stack->stack.buffer[i];
                                    if (value == POISON_VALUE) {
                                        sprintf(index_buffer, "[%d] : POISON", i);
                                        p("\"card-text text-secondary\"", index_buffer)
                                    } else {
                                        sprintf(index_buffer, "[%d] : %d", i, value);
                                        p("\"card-text text-success\"", index_buffer)
                                    }
                                }

                            }
                        }
                        {
                            div("\"row justify-content-md-left\"")
                            {
                                div("\"col-8\"")
                                char sprintf_buf[1000] = {};
                                sprintf(sprintf_buf, "dump from file: %s, function:  %s , line %d", file_name, function, line);
                                p(
                                        "\"card-text text-danger\"",
                                        sprintf_buf
                                )
                            }

                        }
                    }
                }

            }
        }
    }
    fclose(log_file);
}

#endif //SAFETYSTACK_LOGGER_H
