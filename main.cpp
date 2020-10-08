#include <iostream>

#define STACK_TYPE int
#include "headers/decorator_safety.h"


int main() {
    init_log();
    sstack_t* sstack = construct_safety_stack();
    __overload__(push_safety)(sstack, 1);
    __overload__(push_safety)(sstack, 2);
    __overload__(push_safety)(sstack, 3);
    __overload__(push_safety)(sstack, 4);
    __overload__(push_safety)(sstack, 5);
    __overload__(push_safety)(sstack, 6);
    __overload__(push_safety)(sstack, 7);
    __overload__(push_safety)(sstack, 8);
    __overload__(push_safety)(sstack, 1);
    destruct_safety_stack(sstack);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
