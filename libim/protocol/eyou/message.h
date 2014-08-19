#ifndef ___LIBIM_EYOU_MESSAGE_H__
#define ___LIBIM_EYOU_MESSAGE_H__

#include "value.h"
#include "packet.h"

class eyou_packet;

class eyou_message : public eyou_packet
{
public:
	std::string		_from;
	std::string		_to;
	std::string		_time;
	std::string		_body;
};


#endif