#ifndef ___EX_STRING__H__
#define ___EX_STRING__H__

#include <iostream>
#include <string>

std::string string_format(char* format, ...);
std::string string_append_format(std::string src, char* format, ...);

#endif //___EX_STRING__H__