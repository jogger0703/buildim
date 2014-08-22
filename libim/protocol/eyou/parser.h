#ifndef ___LIBIM_EYOU_PARSER_H__
#define ___LIBIM_EYOU_PARSER_H__

#include "packet.h"

class eyou;

void eyou_parser_process(eyou* e, const char *buf, int len);

eyou_packet* make_packet(eyou* e, const char* xml, int xmllen);


#endif