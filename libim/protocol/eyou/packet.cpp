#include "packet.h"
#include "eyou.h"
#include "libxml/tree.h"
#include "iq.h"
#include "message.h"
#include "presence.h"


static std::string xmlnode_to_string(xmlNodePtr root)
{
	xmlDocPtr doc;
	xmlChar *xmlbuff;
	int buffersize;

	doc = xmlNewDoc(BAD_CAST "1.0");
	xmlDocSetRootElement(doc, root);

	xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
	std::string ret((char *)xmlbuff);

	xmlFree(xmlbuff);
	xmlFreeDoc(doc);

	return ret;
}

/************************************************************************/
/* eyou_packet interfaces                                               */
/************************************************************************/

eyou_packet::eyou_packet()
{

}
eyou_packet::~eyou_packet()
{
	if (_doc)
		xmlFreeDoc(_doc);
// 	if (_root)
// 		xmlFreeNode(_root);
}

std::string eyou_packet::to_string(void)
{
	return xmlnode_to_string(_root);
}

bool eyou_packet::from_string(const char* xml, int xmllen)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;

	if ((doc = xmlParseMemory(xml, xmllen)) == NULL)
		return NULL;

	if ((root = xmlDocGetRootElement(doc)) == NULL) {
		xmlFreeDoc(doc);
		return NULL;
	}

	_doc = doc;
	_root = root;
	_str = xml;
	_name = (const char*)root->name;
	if (xmlGetProp(root, (const xmlChar*)"id"))
		_id = (const char*)xmlGetProp(root, (const xmlChar*)"id");

	return true;
}

std::string eyou_packet::get_xmlnode_prop(xmlNodePtr node, const char* prop)
{
	if (xmlGetProp(node, (const xmlChar*)prop))
		return (const char*)xmlGetProp(node, (const xmlChar*)prop);
	return "";
}
std::string eyou_packet::get_xmlnode_value(xmlNodePtr node)
{
	return (const char*)xmlNodeGetContent(node);
}

xmlNodePtr eyou_packet::get_xmlnode_child_by_name(xmlNodePtr node, const char* child_name)
{
	xmlNodePtr it = node->children;
	while (it != NULL) {
		if (xmlStrcmp(it->name, (const xmlChar *)child_name) == 0)
			return it;
		it = it->next;
	}
	return NULL;
}

/**
 * 根据xml生成一个packet。
 * @return 成功返回packet指针，失败返回NULL
 * ！ 注意外部销毁packet
 */
eyou_packet* eyou_packet::make_packet_from_string(const char* xml, int xmllen)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;

	if ((doc = xmlParseMemory(xml, xmllen)) == NULL)
		return NULL;

	if ((root = xmlDocGetRootElement(doc)) == NULL) {
		xmlFreeDoc(doc);
		return NULL;
	}

	eyou_packet* p = NULL;
	std::string packname = (const char*)root->name;
	if (packname == "iq")
		p = new eyou_iq();
	else if (packname == "message")
		p = new eyou_message();
	else if (packname  == "presence")
		p = new eyou_presence();
	else {
		DPRINT(LOG_ERROR, "unknow protocol packet :%s", xml);
	}

	p->_doc = doc;
	p->_root = root;
	p->_str = xml;
	p->_name = (const char*)root->name;
	p->_method = get_xmlnode_prop(root, "method");
	p->_type = get_xmlnode_prop(root, "type");
	p->_id = get_xmlnode_prop(root, "id");
	p->_from = get_xmlnode_prop(root, "from");
	p->_to = get_xmlnode_prop(root, "to");
	p->_time = get_xmlnode_prop(root, "time");

	return p;
}

void eyou_packet::process(void)
{

}