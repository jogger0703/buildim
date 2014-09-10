#ifndef ___LIBIM_EYOU_MESSAGE_H__
#define ___LIBIM_EYOU_MESSAGE_H__

#include "packet.h"

class eyou_message : public eyou_packet
{
public:
	virtual ~eyou_message() {}

	virtual void	process(void);

	static void		send_message_plain(im_conversation* conv, const char* who, const char* content, im_message_flags flags, time_t mtime);
	static void		send_message(im_conversation* conv, im_conversation_message* m);
};


#endif