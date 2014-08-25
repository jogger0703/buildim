#ifndef ___MAKE_UUID__H__
#define ___MAKE_UUID__H__

#include <Objbase.h>
#include "exstring.h"

static std::string make_uuid(void)
{
	GUID guid;
	if (CoCreateGuid(&guid) == S_OK) {
		return string_format("{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1,
			guid.Data2, 
			guid.Data3, 
			guid.Data4[0],   guid.Data4[1],
			guid.Data4[2],   guid.Data4[3],
			guid.Data4[4],   guid.Data4[5],
			guid.Data4[6],   guid.Data4[7]);
	}
	return "";
}

#endif 