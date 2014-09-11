#ifndef ___ERROR__H__
#define ___ERROR__H__

#include <iostream>
#include <Windows.h>
#include <assert.h>

/** 
 * ������ŷ���ɴ�����Ϣ
 * ���ص�������Ҫ����
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
  �������ѣ�������ʾ
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
  �������ѣ�������ʾ�������˳�
*/
static void
error_quit(const char *s)
{
	error_box(s);
	exit(0);
}

/*
  ��մ���ֵ
*/
static void
error_clear(void)
{
	SetLastError(0);
}

/*
  DEBUGģʽ�µĵ�������
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