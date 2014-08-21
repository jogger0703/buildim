#include "packet.h"
#include "libxml/tree.h"


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

	if ((doc = xmlParseMemory(xml, strlen(xml))) == NULL)
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