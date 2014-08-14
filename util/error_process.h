#ifndef ___ERROR__H__
#define ___ERROR__H__

#include <iostream>
#include <Windows.h>

/** 
 * 将错误号翻译成错误信息
 * 返回的数据需要销毁
 */
std::string errno2msg(int err)
{
	LPVOID buf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPSTR)&buf,
		0,
		NULL
		);

	std::string msg = (char*)buf;
	LocalFree(buf);

	return msg;
}

#endif