//
// Created by kalibri on 30.09.2020.
//

#ifndef SAFETYSTACK_STACK_H
#define SAFETYSTACK_STACK_H

#include <stdlib.h>
#include <stdio.h>

//-----------------------------------------------------------------------


#define __concat__( obj, type)  obj ## _ ## type
#define __overload_helper__(obj, type)  __concat__ (obj, type)
#define __overload__(obj)        __overload_helper__(obj, STACK_TYPE)

//-----------------------------------------------------------------------

const size_t INIT_BUF_SIZE = 2;

typedef struct __overload__(stack) {
    STACK_TYPE* buffer;
    int  size;
    int  max_size;
} stack_t;

stack_t* __overload__(new_stack)();

void __overload__(clear_stack)(stack_t* stack);

void __overload__(push)(stack_t* stack, STACK_TYPE value);

STACK_TYPE __overload__(top)(stack_t* stack);

STACK_TYPE __overload__(pop)(stack_t* stack);

//-----------------------------------------------------------------------

stack_t* __overload__(new_stack)() {
    stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));

    new_stack->max_size = INIT_BUF_SIZE;
    new_stack->size     = 0;
    new_stack->buffer   = (STACK_TYPE*)calloc(INIT_BUF_SIZE, sizeof(STACK_TYPE));

    return new_stack;
}

void __overload__(clear_stack)(stack_t* stack) {
    free(stack->buffer);
    stack->buffer = NULL;
}

STACK_TYPE* __overload__(resize)(stack_t* stack) {
    stack->max_size += (stack->max_size == 1);
    stack->max_size *= 2;
    return (STACK_TYPE*)realloc(stack->buffer , stack->max_size * sizeof(STACK_TYPE));
}

void __overload__(push)(stack_t* stack, STACK_TYPE value) {
    if (stack->size == stack->max_size) {
        stack->buffer = __overload__(resize)(stack);
    }
    stack->buffer[stack->size++] = value;
}

STACK_TYPE __overload__(top)(stack_t* stack) {
    return stack->buffer[stack->size - 1];
}

STACK_TYPE __overload__(pop)(stack_t* stack) {
    if (stack->size > 0) {
        STACK_TYPE top_value = stack->buffer[stack->size - 1];
        --stack->size;
        return top_value;
    } else {
        fprintf(stderr, "Stack underflow");
        abort();
    }
}

//-----------------------------------------------------------------------

#endif //SAFETYSTACK_STACK_H
