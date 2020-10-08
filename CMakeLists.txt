cmake_minimum_required(VERSION 3.17)
project(StackSafetyCPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(StackSafetyCPP main.cpp settings.h headers/decorator_safety.h headers/logger.h headers/stack.h lib/htmlib.hpp headers/safety_stuff.h)

