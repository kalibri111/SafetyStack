//
// Created by kalibri on 30.09.2020.
//

#ifndef SAFETYSTACK_DECORATOR_SAFETY_H
#define SAFETYSTACK_DECORATOR_SAFETY_H

#include "stack.h"
#include "../settings.h"
#include "../headers/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "safety_stuff.h"

//------------------------------------------------------------


/*
 * functions determinate stack statement
 * and occurs stack S_STACK_ERR
 * if there is error, writes dump to LOG_FILE_PATH
 * */
sstack_err stack_error_(sstack_t* sstack, const char* file_name, const char* function, int line) {

    stack_t*        stack      = NULL;
    STACK_TYPE*     s_buffer   = NULL;
    int             s_max_size = -1;
    int                 s_size = -1;

#define HTML_LOG(error) __overload__(make_html_log)(sstack, stack, s_buffer, s_max_size, s_size, \
                               file_name, function, line, error);
    if (!sstack) {
        HTML_LOG(STACK_NULL_SSTACK);
        return STACK_NULL_SSTACK;
    }

    if (sstack->stack.size >= 0) {
        s_size = sstack->stack.size;
    } else {
        HTML_LOG(STACK_BAD_SIZE);
        return STACK_BAD_SIZE;
    }

    if (sstack->stack.max_size >= 0) {
        s_max_size = sstack->stack.max_size;
    } else {
        HTML_LOG(STACK_BAD_MAX_SIZE);
        return STACK_BAD_MAX_SIZE;
    }

    if (sstack->stack.size > sstack->stack.max_size) {
        HTML_LOG(STACK_BAD_SIZE);
        return STACK_BAD_SIZE;
    }

    if (&(sstack->stack)) {
        stack = &sstack->stack;
    } else {
        HTML_LOG(STACK_NULL_RAW_STACK);
        return STACK_NULL_RAW_STACK;
    }

    if (sstack->stack.buffer) {
        s_buffer = sstack->stack.buffer;
    } else {
        HTML_LOG(STACK_NULL_BUFFER);
        return STACK_NULL_BUFFER;
    }

#ifdef CANARY_PROTECT
//    петушиная защита структуры
    if (sstack->canary_left != __overload__(CANARY_VALUE) || sstack->canary_right != __overload__(CANARY_VALUE)) {
        HTML_LOG(STACK_CANARY_ERROR);
        return STACK_CANARY_ERROR;
    }
//    буфера
    if (sstack->stack.buffer[-1] != __overload__(CANARY_VALUE) ||
        sstack->stack.buffer[sstack->stack.max_size] != __overload__(CANARY_VALUE)) {
        HTML_LOG(STACK_CANARY_ERROR);
        return STACK_CANARY_ERROR;
    }
#endif

#ifdef HASH_PROTECT
    if (sstack->check_sum != stack_evaluate_crc8(sstack)) {
        sstack->check_sum = stack_evaluate_crc8(sstack);
        HTML_LOG(STACK_CHECKSUM_ERROR);
        return STACK_CHECKSUM_ERROR;
    }
#endif
#undef HTML_LOG
    return STACK_NO_ERROR;
}

/*
 * construct safety decorated stack_t
 * with settings in settings.h
 * */
sstack_t* construct_safety_stack() {
    sstack_t* new_sstack = (sstack_t*)calloc(1, sizeof(sstack_t));
#ifdef CANARY_PROTECT
    new_sstack->canary_left  = __overload__(CANARY_VALUE);
    new_sstack->canary_right = __overload__(CANARY_VALUE);
    stack_t* new_raw_stack = __overload__(new_stack)();

    new_raw_stack->buffer = (STACK_TYPE*)calloc(INIT_BUF_SIZE + 2, sizeof(STACK_TYPE));

    new_raw_stack->buffer[0]                           = __overload__(CANARY_VALUE);
    new_raw_stack->buffer[new_raw_stack->max_size + 1] = __overload__(CANARY_VALUE);

    new_raw_stack->buffer += 1;

    for (int i = 0; i < new_raw_stack->max_size; ++i) {
        new_raw_stack->buffer[i] = POISON_VALUE;
    }

    new_sstack->stack = *new_raw_stack;
#else
    new_sstack->stack = *__overload__(new_stack)();
#endif

#ifdef HASH_PROTECT
    new_sstack->check_sum = stack_evaluate_crc8(new_sstack);
#endif
    VERIFY(new_sstack, __FILE__, __FUNCTION__ , __LINE__);
    return new_sstack;
}

void destruct_safety_stack(sstack_t* s_stack) {
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
#ifdef CANARY_PROTECT
    free(s_stack->stack.buffer - 1);
#else
    __overload__(clear_stack)(&(s_stack->stack));
#endif
    free(s_stack);
    s_stack = NULL;
}

/*
 * resize buffer with canary protect
 * */
#ifdef CANARY_PROTECT
STACK_TYPE* __overload__(resize_safety)(sstack_t* s_stack) {
    s_stack->stack.buffer -= 1;
    int new_size = 2*(s_stack->stack.max_size) + 2;
    s_stack->stack.buffer = (STACK_TYPE*)realloc(s_stack->stack.buffer, new_size * sizeof(STACK_TYPE));
    for (int i = s_stack->stack.max_size + 1; i < 2 * s_stack->stack.max_size + 1; ++i) {
        s_stack->stack.buffer[i] = POISON_VALUE;
    }

    s_stack->stack.max_size *= 2;
    s_stack->stack.buffer += 1;

    s_stack->stack.buffer[s_stack->stack.max_size] = __overload__(CANARY_VALUE);
    return s_stack->stack.buffer;
}
#endif

/*
 * decorate push in stack.h
 * */
void __overload__(push_safety)(sstack_t* s_stack, STACK_TYPE value) {
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
#ifdef CANARY_PROTECT
    if (s_stack->stack.size == s_stack->stack.max_size) {
        s_stack->stack.buffer = __overload__(resize_safety)(s_stack);
    }
#endif
    __overload__(push)(&(s_stack->stack), value);

    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
}

/*
 * decorate top in stack.h
 * */
STACK_TYPE __overload__(top_safety)(sstack_t* s_stack) {
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
    STACK_TYPE value = __overload__(top)(&s_stack->stack);
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
    return value;
}

/*
 * decorate pop in stack.h
 * */
STACK_TYPE __overload__(pop_safety)(sstack_t* s_stack) {
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
    STACK_TYPE value = __overload__(pop)(&s_stack->stack);
    VERIFY(s_stack, __FILE__, __FUNCTION__ , __LINE__);
    return value;
}

//-----------------------------------------------------------------------



#endif //SAFETYSTACK_DECORATOR_SAFETY_H
