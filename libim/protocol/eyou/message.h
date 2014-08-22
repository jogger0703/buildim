#ifndef ___LIBIM_EYOU_MESSAGE_H__
#define ___LIBIM_EYOU_MESSAGE_H__

#include "packet.h"

class eyou_message : public eyou_packet
{
public:
	virtual ~eyou_message() {}

	std::string		_from;
	std::string		_to;
	std::string		_time;
	std::string		_body;

	virtual void	process(void);
};


#endif