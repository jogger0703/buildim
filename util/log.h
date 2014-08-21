#ifndef ___LIBIM_LOG__H__
#define ___LIBIM_LOG__H__

#include <stdio.h>
#include <stdarg.h>

typedef enum {
	LOG_INFO = 0,
	LOG_WARING,
	LOG_ERROR,
	LOG_FATAL
} log_level;


class Log
{
	//CRITICAL_SECTION	m_section;
	//fstream				m_stream;
	FILE				*m_file;
	log_level			m_maxlevel;
public:
	bool init(const char* path, log_level max_level, bool clr);
	void write_line(log_level level, const char* file, int line, char* format, ...);
};


extern Log _mylog;

#define DPRINT_INIT(path, level, clr) (_mylog.init(path, level, clr))
#define DPRINT(level, format, ...) (_mylog.write_line(level, __FILE__, __LINE__, format, ## __VA_ARGS__))


#endif