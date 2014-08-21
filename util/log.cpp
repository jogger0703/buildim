#include "log.h"
#include <stdarg.h>
#include <time.h>
#include <sys/timeb.h>
#include <process.h>


Log _mylog;

bool Log::init(const char* path, log_level max_level, bool clr)
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

	_lock_file(m_file);
	fprintf_s(m_file, "%02d-%02d %02d-%02d-%02d-%03d %d %s:%d ", 
			t.tm_mon+1, t.tm_mday, t.tm_hour,
			t.tm_min, t.tm_sec, tmb.millitm, getpid(), file, line);
	fprintf_s(m_file, buf);
	_fflush_nolock(m_file);
	_unlock_file(m_file);
}
