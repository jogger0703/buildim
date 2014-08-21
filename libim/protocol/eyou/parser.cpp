#include "parser.h"
#include "eyou.h"
#include <libxml/parser.h>

static void
eyou_parser_element_start_libxml(void *user_data,
				   const xmlChar *element_name, const xmlChar *prefix, const xmlChar *ns,
				   int nb_namespaces, const xmlChar **namespaces,
				   int nb_attributes, int nb_defaulted, const xmlChar **attributes)
{
	eyou* e = (eyou*)user_data;

	if (!element_name)
		return;
	else {
		for (int i=0; i<nb_attributes*5; i+=5) {
			const char* name = (const char*)attributes[i];
			const char* prefix = (const char*)attributes[i+1];
			const char* attrib_ns = (const char*)attributes[i+2];
			int attrib_len = attributes[i+4] - attributes[i+3];
		}
	}
}

static void
eyou_parser_element_end_libxml(void *user_data, const xmlChar *element_name,
				 const xmlChar *prefix, const xmlChar *ns)
{
}

static void
eyou_parser_element_text_libxml(void *user_data, const xmlChar *text, int text_len)
{
}

static void
eyou_parser_structured_error_handler(void *user_data, xmlErrorPtr error)
{
}

static xmlSAXHandler jabber_parser_libxml = {
	NULL,									/*internalSubset*/
	NULL,									/*isStandalone*/
	NULL,									/*hasInternalSubset*/
	NULL,									/*hasExternalSubset*/
	NULL,									/*resolveEntity*/
	NULL,									/*getEntity*/
	NULL,									/*entityDecl*/
	NULL,									/*notationDecl*/
	NULL,									/*attributeDecl*/
	NULL,									/*elementDecl*/
	NULL,									/*unparsedEntityDecl*/
	NULL,									/*setDocumentLocator*/
	NULL,									/*startDocument*/
	NULL,									/*endDocument*/
	NULL,									/*startElement*/
	NULL,									/*endElement*/
	NULL,									/*reference*/
	eyou_parser_element_text_libxml,		/*characters*/
	NULL,									/*ignorableWhitespace*/
	NULL,									/*processingInstruction*/
	NULL,									/*comment*/
	NULL,									/*warning*/
	NULL,									/*error*/
	NULL,									/*fatalError*/
	NULL,									/*getParameterEntity*/
	NULL,									/*cdataBlock*/
	NULL,									/*externalSubset*/
	XML_SAX2_MAGIC,							/*initialized*/
	NULL,									/*_private*/
	eyou_parser_element_start_libxml,		/*startElementNs*/
	eyou_parser_element_end_libxml,			/*endElementNs*/
	eyou_parser_structured_error_handler	/*serror*/
};


void eyou_parser_process(eyou *e, const char *buf, int len)
{
#if 0 // 使用sax进行流式解析
	int ret;

	if (e->_context == NULL) {
		e->_context = xmlCreatePushParserCtxt(&jabber_parser_libxml, e, buf, len, NULL);
		xmlParseChunk(e->_context, "", 0, 0);
	}
	else if ((ret = xmlParseChunk(e->_context, buf, len, 0)) != XML_ERR_OK) {
		xmlError *err = xmlCtxtGetLastError(e->_context);

		xmlErrorLevel level = XML_ERR_WARNING;
		if (err)
			level = err->level;
	}
#else // 块解析
	eyou_packet* p = make_packet(buf, len);
	if (!p) {
		
	}
#endif
}


/**
 * 使用xml字符串创建一个packet，并返回。
 * ！外部需要销毁packet
 *
 * @xml  xmlstring
 * @return 成功返回指针，失败返回NULL
 */
eyou_packet* make_packet(const char* xml, int xmllen)
{
	eyou_packet* p = new eyou_packet();
	if (!p->from_string(xml, xmllen)) {
		delete p;
		return NULL;
	}
	return p;
}