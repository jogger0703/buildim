#ifndef ___LIBIM_EYOU_ROSTER_H__
#define ___LIBIM_EYOU_ROSTER_H__

#include "buddy.h"


im_buddy_node* parse_roster_from_xml(im_buddy_node* buddy_root, const char* xml);

#endif