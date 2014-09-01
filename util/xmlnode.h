/**************************************************/
/*
* 使用libxml2解析库实现对xml节点的操作
*
*/
/**************************************************/

#ifndef INCLUDED_XMLNODE_H
#define INCLUDED_XMLNODE_H

#include "libxml/tree.h"
#include "exstring.h"

std::string xmlnode_to_string(xmlNodePtr root);
xmlNodePtr	xmlnode_from_string(const char* xml);

std::string	xmlnode_get_prop(xmlNodePtr node, const char* prop);
std::string	xmlnode_get_value(xmlNodePtr node);
xmlNodePtr	xmlnode_get_child_by_name(xmlNodePtr node, const char* child_name);

xmlNodePtr	xmlnode_get_next(xmlNodePtr node);


#endif