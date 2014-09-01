#include "xmlnode.h"


xmlNodePtr	xmlnode_from_string(const char* xml)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root = NULL;

	if ((doc = xmlParseMemory(xml, strlen(xml))) == NULL)
		return NULL;

	if ((root = xmlDocGetRootElement(doc)) == NULL) {
		xmlFreeDoc(doc);
		return NULL;
	}

	return root;
}

std::string xmlnode_to_string(xmlNodePtr root)
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


std::string xmlnode_get_prop(xmlNodePtr node, const char* prop)
{
	if (xmlGetProp(node, (const xmlChar*)prop))
		return (const char*)xmlGetProp(node, (const xmlChar*)prop);
	return "";
}
std::string xmlnode_get_value(xmlNodePtr node)
{
	return (const char*)xmlNodeGetContent(node);
}

xmlNodePtr xmlnode_get_child_by_name(xmlNodePtr node, const char* child_name)
{
	xmlNodePtr it = node->children;
	while (it != NULL) {
		if (xmlStrcmp(it->name, (const xmlChar *)child_name) == 0)
			return it;
		it = it->next;
	}
	return NULL;
}

xmlNodePtr xmlnode_get_next(xmlNodePtr node)
{
	return node->next;
}