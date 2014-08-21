#include "exstring.h"
#include <stdarg.h>

/**
 * 格式化字符串，并分配缓冲区进行存储。
 * ！注意，外部应该销毁缓冲区
 */
static char* strdup_vprintf(const char* format, va_list args)
{
	// 获取缓冲区长度
	int len = _vscprintf(format, args);
	char *buffer = new char[len + 1];

	// 格式化
	vsnprintf(buffer, len, format, args);
	buffer[len] = 0;

	return buffer;
}

std::string string_format(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char* buf = strdup_vprintf(fmt, args);
	va_end(args);

	std::string ret(buf);
	delete []buf;

	return ret;
}

std::string string_append_format(std::string src, char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string suffix = string_format(fmt, args);
	va_end(args);

	return src + suffix;
}