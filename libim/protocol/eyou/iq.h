#ifndef ___LIBIM_EYOU_IQ_H__
#define ___LIBIM_EYOU_IQ_H__

#include "packet.h"

class eyou_iq : public eyou_packet
{
public:
	virtual ~eyou_iq() {}

	virtual void	process(void);
};


#endif