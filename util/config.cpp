#include "config.h"
#include "SimpleIni.h"
#include <locale.h>
#include <cassert>
using namespace std;

bool hash_config::read_file(const char* filepath)
{
 	CSimpleIni ini;
 	if (ini.LoadFile(filepath) < 0)
 		return false;
	CSimpleIni::TNamesDepend keys;
	ini.GetAllKeys("standard", keys);

	CSimpleIni::TNamesDepend::const_iterator iKey = keys.begin();
	for ( ; iKey != keys.end(); ++iKey ) {
		const char* pItem = iKey->pItem;
		const char* val = ini.GetValue("standard", pItem);

		set_string(pItem, val);
	}
	
	return true;
}
bool hash_config::save_file(const char* filepath)
{
 	CSimpleIni ini;
	for (auto it = _hash.begin(); it != _hash.end(); ++it) {
		ini.SetValue("standard", it->first.c_str(), it->second.c_str());
	}

	if (ini.SaveFile(filepath) < 0)
		return false;

	return true;
}


std::string hash_config::get_string(const char* k, const char* default_value)
{
	if (_hash.find(k) == _hash.end())
		return default_value;
	return _hash[k];
}
int	hash_config::get_int(const char* k, int default_value)
{
	std::string val = get_string(k, std::to_string((_LONGLONG)default_value).c_str());
	return std::stoi(val);
}
bool hash_config::get_bool(const char* k, bool default_value)
{
	return (bool)get_int(k, (int)default_value);
}

void hash_config::set_string(const char* k, const char* val)
{
	_hash[k] = std::string(val);
}
void hash_config::set_int(const char* k, int val)
{
	_hash[k] = std::to_string((_LONGLONG)val);
}
void hash_config::set_bool(const char* k, bool val)
{
	set_int(k, (int)val);
}