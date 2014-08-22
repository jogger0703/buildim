#ifndef ___LIBIM_EYOU_PACKET_H__
#define ___LIBIM_EYOU_PACKET_H__

#include "value.h"
#include "account.h"
#include "connection.h"
#include "libxml\tree.h"

class eyou;
class eyou_packet
{
public:
	eyou_packet();
	virtual ~eyou_packet();

	eyou			*_client;
	std::string		_name;
	std::string		_method;
	std::string		_id;
	std::string		_type;
	xmlNodePtr		_root;
	xmlDocPtr		_doc;
	std::string		_str;

	std::string		to_string(void);
	bool			from_string(const char* xml, int xmllen);
	static eyou_packet* make_packet_from_string(const char* xml, int xmllen);

	virtual void	process(void);
};


#endif