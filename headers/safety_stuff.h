//
// Created by kalibri on 07.10.2020.
//

#ifndef STACKSAFETYCPP_SAFETY_STUFF_H
#define STACKSAFETYCPP_SAFETY_STUFF_H
#include "stack.h"
#include "../settings.h"
#include <typeinfo>

#define typename(x) typeid(x).name()

#define VERIFY(sstack, file, func, line) if(stack_error_(sstack, file, func, line)) {          \
    fprintf(stderr, "Stack broken, more info in log.html \n"); \
}

// TODO STACK_NO_ERROR == 0?
typedef enum S_STACK_ERR {
    STACK_NO_ERROR = 0,
    STACK_BAD_SIZE,
    STACK_BAD_MAX_SIZE,
    STACK_NULL_BUFFER,
    STACK_NULL_RAW_STACK,
    STACK_NULL_SSTACK,
    STACK_CANARY_ERROR,
    STACK_CHECKSUM_ERROR
} sstack_err;

const int  CANARY_VALUE_int = 0xDEADDEAD;
const char CANARY_VALUE_char = 'O';
const int POISON_VALUE = 0xDEAD10C;

typedef struct SafetyStack {
#ifdef CANARY_PROTECT
    long long canary_left;
#endif

#ifdef HASH_PROTECT
    int check_sum;
#endif

    stack_t stack;

#ifdef CANARY_PROTECT
    long long canary_right;
#endif
} sstack_t;

#ifdef HASH_PROTECT
unsigned char crc8(unsigned char *pcBlock, unsigned int len) {
    unsigned char crc = 0xFF;
    unsigned int i;

    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }

    return crc;
}

int stack_evaluate_crc8(sstack_t* sstack) {
#ifdef CANARY_PROTECT
    size_t check_sum = (size_t)sstack + (size_t)(&sstack->stack);
    unsigned char r = crc8(reinterpret_cast<unsigned char *>(&check_sum), sizeof(size_t));
    return r;
#endif

}
#endif

#endif //STACKSAFETYCPP_SAFETY_STUFF_H
