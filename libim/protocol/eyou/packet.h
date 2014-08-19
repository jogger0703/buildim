#ifndef ___LIBIM_EYOU_PACKET_H__
#define ___LIBIM_EYOU_PACKET_H__

#include "value.h"


class eyou_packet
{
public:
	std::string		_method;
	std::string		_id;
	std::string		_type;
	

	std::string		to_string(void);
};


#endif