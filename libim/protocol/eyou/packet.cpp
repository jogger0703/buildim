#include "packet.h"
#include "eyou.h"
#include "iq.h"
#include "message.h"
#include "presence.h"



/************************************************************************/
/* eyou_packet interfaces                                               */
/************************************************************************/

eyou_packet::eyou_packet()
{

}
eyou_packet::~eyou_packet()
{
	if (_root)
		xmlFreeNode(_root);
}

std::string eyou_packet::to_string(void)
{
	return xmlnode_to_string(_root);
}

bool eyou_packet::from_string(const char* xml, int xmllen)
{
	_root = xmlnode_from_string(xml);
	_str = xml;
	_name = (const char*)_root->name;
	if (xmlGetProp(_root, (const xmlChar*)"id"))
		_id = (const char*)xmlGetProp(_root, (const xmlChar*)"id");

	return true;
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

	p->_root = root;
	p->_str = xml;
	p->_name = (const char*)root->name;
	p->_method = xmlnode_get_prop(root, "method");
	p->_type = xmlnode_get_prop(root, "type");
	p->_id = xmlnode_get_prop(root, "id");
	p->_from = xmlnode_get_prop(root, "from");
	p->_to = xmlnode_get_prop(root, "to");
	p->_time = xmlnode_get_prop(root, "time");

	return p;
}

void eyou_packet::process(void)
{

}