#ifndef ___ERROR__H__
#define ___ERROR__H__

#include <iostream>
#include <Windows.h>
#include <assert.h>

/** 
 * 将错误号翻译成错误信息
 * 返回的数据需要销毁
 */
static std::string errno2msg(int err)
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


/*
  弹框提醒，警告提示
*/
static void
error_box(const char *s)
{
	std::string content = s ? s : "";
	std::string error_info = errno2msg(GetLastError());
	content += error_info;
	MessageBoxA(NULL, content.c_str(), "error", MB_OK | MB_ICONWARNING);
}

/*
  弹框提醒，警告提示，并且退出
*/
static void
error_quit(const char *s)
{
	error_box(s);
	exit(0);
}

/*
  清空错误值
*/
static void
error_clear(void)
{
	SetLastError(0);
}

/*
  DEBUG模式下的弹框提醒
*/
static void
error_debug(const char *s)
{
#ifdef _DEBUG
	error_box(s);
//	ASSERT(0);
#endif
}

#endif