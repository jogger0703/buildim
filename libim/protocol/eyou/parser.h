#ifndef ___LIBIM_EYOU_PARSER_H__
#define ___LIBIM_EYOU_PARSER_H__

#include "eyou.h"

class eyou;

void eyou_parser_process(eyou* e, const char *buf, int len);

eyou_packet* make_packet(const char* xml, int xmllen);


#endif