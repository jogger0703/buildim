#ifndef ___LIBIM_LOG__H__
#define ___LIBIM_LOG__H__

#include <stdio.h>
#include <stdarg.h>

typedef enum {
	LOG_FATAL = 0,
	LOG_ERROR,
	LOG_WARING,
	LOG_INFO
} log_level;


class Log
{
	FILE				*m_file;
	log_level			m_maxlevel;
	bool				m_detail;
public:
	bool init(const char* path, log_level max_level, bool clr, bool pref_detail);
	void write_line(log_level level, const char* file, int line, char* format, ...);
};


extern Log _mylog;

#define DPRINT_INIT(path, level, clr, detail) (_mylog.init(path, level, clr, detail))
#define DPRINT(level, format, ...) (_mylog.write_line(level, __FILE__, __LINE__, format, ## __VA_ARGS__))


#endif