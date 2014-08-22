#include "log.h"
#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>
#include <process.h>
#include <Windows.h>


Log _mylog;

bool Log::init(const char* path, log_level max_level, bool clr, bool pref_detail)
{
	char* mode = NULL;
	if (clr)
		mode = "w";
	else
		mode = "a";

	if (path)
		m_file = fopen(path, mode);
	else
		m_file = _fdopen(1, mode); // stdout handle == 1

	if (!m_file)
		return false;

	m_detail = pref_detail;
	m_maxlevel = max_level;
	return true;
}

void Log::write_line(log_level level, const char* file, int line, char* format, ...)
{
	time_t		now;
	struct tm	t;
	struct timeb tmb;

	if (level > m_maxlevel)
		return;

	va_list args;
	va_start(args, format);
	int buflen = _vscprintf(format, args);
	va_end(args);

	char* buf = new char[buflen + 1];
	va_start(args, format);
	vsnprintf(buf, buflen, format, args);
	va_end(args);
	buf[buflen] = '\0';

	time(&now);
	localtime_s(&t, &now);
	ftime(&tmb);

#ifdef WIN32
	if (fileno(m_file) == 1 || fileno(m_file) == 2) {
		/* 调整标准输出字体颜色 */
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD flags = 0;
		if (level == LOG_FATAL)
			flags = FOREGROUND_RED | FOREGROUND_INTENSITY | COMMON_LVB_UNDERSCORE;
		if (level == LOG_ERROR)
			flags = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		if (level == LOG_WARING)
			flags = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
		if (level == LOG_INFO)
			flags = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		SetConsoleTextAttribute(hConsole, flags);
	}
#endif

	_lock_file(m_file);
	if (m_detail) {
		// 打印详细信息，时间，源文件名称，行号，进程id（线程id）
#ifdef WIN32
		fprintf_s(m_file, "%02d-%02d %02d-%02d-%02d-%03d (%d:%d) %s:%d ", 
			t.tm_mon+1, t.tm_mday, t.tm_hour,
			t.tm_min, t.tm_sec, tmb.millitm, 
			getpid(), GetCurrentThreadId(), file, line);
#else
		fprintf_s(m_file, "%02d-%02d %02d-%02d-%02d-%03d %d %s:%d ", 
			t.tm_mon+1, t.tm_mday, t.tm_hour,
			t.tm_min, t.tm_sec, tmb.millitm, 
			getpid(), file, line);
#endif
	}
	fprintf_s(m_file, buf);
	fprintf_s(m_file, "\r\n");
	_fflush_nolock(m_file);
	_unlock_file(m_file);
}
