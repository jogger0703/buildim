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
	xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "iq");
	if (!_method.empty())
		xmlSetProp(root, (const xmlChar*)"method", (const xmlChar*)_method.c_str());
	if (!_type.empty())
		xmlSetProp(root, (const xmlChar*)"type", (const xmlChar*)_type.c_str());
	if (!_id.empty())
		xmlSetProp(root, (const xmlChar*)"id", (const xmlChar*)_id.c_str());


	return xmlnode_to_string(root);
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
	if (xmlGetProp(root, (const xmlChar*)"method"))
		p->_method = (const char*)xmlGetProp(root, (const xmlChar*)"method");
	if (xmlGetProp(root, (const xmlChar*)"type"))
		p->_type = (const char*)xmlGetProp(root, (const xmlChar*)"type");
	if (xmlGetProp(root, (const xmlChar*)"id"))
		p->_id = (const char*)xmlGetProp(root, (const xmlChar*)"id");

	return p;
}

void eyou_packet::process(void)
{

}