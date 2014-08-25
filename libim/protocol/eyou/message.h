#ifndef ___LIBIM_EYOU_MESSAGE_H__
#define ___LIBIM_EYOU_MESSAGE_H__

#include "packet.h"

class eyou_message : public eyou_packet
{
public:
	virtual ~eyou_message() {}

	virtual void	process(void);
};


#endif