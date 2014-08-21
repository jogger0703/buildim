#include "exstring.h"
#include <stdarg.h>

/**
 * ��ʽ���ַ����������仺�������д洢��
 * ��ע�⣬�ⲿӦ�����ٻ�����
 */
static char* strdup_vprintf(const char* format, va_list args)
{
	// ��ȡ����������
	int len = _vscprintf(format, args);
	char *buffer = new char[len + 1];

	// ��ʽ��
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