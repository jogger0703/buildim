/**************************************************/
/*
* config.h
* 
*
*
*
*/
/**************************************************/

#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#include <iostream>
#include <hash_map>
#include <string>

class hash_config
{
public:
	bool				read_file(const char* filepath);
	bool				save_file(const char* filepath);

	std::string			get_string(const char* k, const char* default_value);
	int					get_int(const char* k, int default_value);
	bool				get_bool(const char* k, bool default_value);
	void				set_string(const char* k, const char* val);
	void				set_int(const char* k, int val);
	void				set_bool(const char* k, bool val);
private:
	std::hash_map<std::string, std::string> _hash;
};



#endif // ~INCLUDED_CONFIG_H