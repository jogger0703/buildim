#ifndef ___CHAR_OPERATION__H__
#define ___CHAR_OPERATION__H__

#include <iostream>
#include <string>

std::string unicode2utf8(const char* src, int len);

std::wstring ansi2unicode(const char* src, int len);
std::string unicode2ansi(const wchar_t* src, int len);

std::string utf82ansi(const char* src, int len);
std::string ansi2utf8(const char* src, int len);

#endif //___CHAR_OPERATION__H__