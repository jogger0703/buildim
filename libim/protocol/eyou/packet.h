#ifndef ___LIBIM_EYOU_PACKET_H__
#define ___LIBIM_EYOU_PACKET_H__

#include "value.h"
#include "libxml\tree.h"


class eyou_packet
{
public:
	std::string		_name;
	std::string		_method;
	std::string		_id;
	std::string		_type;
	xmlNodePtr		_root;
	xmlDocPtr		_doc;
	std::string		_str;

	std::string		to_string(void);
	bool			from_string(const char* xml, int xmllen);
};


#endif