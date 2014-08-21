#ifndef ___LIBIM_EYOU_IO_H__
#define ___LIBIM_EYOU_IO_H__

#include "eyou.h"

void eyou_write_packet(im_connection* conn, eyou_packet* pack);
void eyou_write_plain(im_connection* conn, const char* text, int len);
void eyou_read_socket(im_connection* conn);


#endif