#ifndef ___LIBIM_EYOU_PRESENCE_H__
#define ___LIBIM_EYOU_PRESENCE_H__

#include "packet.h"

class eyou_packet;


class eyou_presence : public eyou_packet
{
public:
	virtual ~eyou_presence() {}

	virtual void	process(void);
};


#endif