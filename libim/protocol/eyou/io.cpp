#include "io.h"
#include "parser.h"
#include "char_operation.h"


typedef struct {
	__int32 head_len;
	__int32 pack_len;
	__int32 version; // Ŀǰʹ��6�� 2014.08.20
} packet_head;

static const int packet_head_len = sizeof(packet_head);

static void eyou_write_head(im_connection* conn, int pack_len)
{
	// ��ͷ����Ϊ12��3��int32�ĳ���
	packet_head h = {packet_head_len, pack_len, 6};

	conn->write((char*)&h, packet_head_len);
}

void eyou_write_packet(im_connection* conn, eyou_packet* pack)
{
	eyou_write_plain(conn, pack->to_string().c_str(), pack->to_string().length());
}

void eyou_write_plain(im_connection* conn, const char* text, int len)
{
	eyou_write_head(conn, len);

	/* �������շ����ַ�������utf8 */
	std::string utf8 = ansi2utf8(text, len);
	conn->write(utf8.c_str(), utf8.length());
}

void eyou_read_socket(im_connection* conn)
{
	packet_head h;
	int nread = conn->peek((char*)(&h), packet_head_len);
	if (nread < packet_head_len)
		return;

	nread = conn->peek(NULL, packet_head_len+h.pack_len);
	if (nread < packet_head_len+h.pack_len)
		return;

	conn->read((char*)&h, packet_head_len);
	char* buf = new char[h.pack_len + 1];
	conn->read(buf, h.pack_len);
	buf[h.pack_len] = '\0';

	/* �������շ����ַ�������utf8 */
	//std::string mbcs = utf82ansi(buf, h.pack_len);
	std::string mbcs = buf;

	/* ��Ҫ���߽�����xml����iso-8859-1���룬�������Ĭ�ϵ�utf8���봦�� */
	//ISO-8859-1
	//Windows-1252
	std::string full_xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
	full_xml += mbcs;
	delete []buf;

	eyou_parser_process((eyou*)conn->_proto_data, full_xml.c_str(), full_xml.length());
}