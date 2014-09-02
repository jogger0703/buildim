#include "roster.h"
#include "xmlnode.h"


/**
 * ��xml�н�������ϵ�˵Ľṹ����䵽������������
 * @root ��ϵ�˸������������������û����ʵ�Ŀ�������
 * @xml xml�ڵ�
 * @�ɹ�����������ʧ�ܷ���NULL
 */
im_buddy_node* parse_roster_from_xml(im_buddy_node* buddy_root, const char* xml)
{
// <iq id="2" type="ok" to="im@eyou.net" method="roster">
// 	<group name="������" type="sys" pos="0">
// 		<item uid="chenna@eyou.net" name="����-890" realname = "����"/>
// 		<item uid="lilijuan@eyou.net" name="������-325" realname = "������"/>
// 		<item uid="zhangyue@eyou.net" name="��Ծ-376" realname = "��Ծ"/>
// 	</group>
// 	<group name="�г���" type="sys" pos="0">
// 		<item uid="xiangwenwen@eyou.net" name="������-271" realname = "������"/>
// 	</group>
// </iq>
	xmlNodePtr root = xmlnode_from_string(xml);

	xmlNodePtr group = xmlnode_get_child_by_name(root, "group");
	while (group) {
		im_group* gnode = new im_group();
		gnode->_name = xmlnode_get_prop(group, "name");
		gnode->_pos = xmlnode_get_prop(group, "pos");
		gnode->_goup_type = xmlnode_get_prop(group, "type");

		buddy_root->add_child(gnode);

		xmlNodePtr item = xmlnode_get_child_by_name(group, "item");
		while (item) {
			im_contact* buddy = new im_contact();
			buddy->_id = xmlnode_get_prop(item, "uid");
			buddy->_name = xmlnode_get_prop(item, "realname");
			buddy->_alias = xmlnode_get_prop(item, "name");

			gnode->add_child(buddy);

			item = xmlnode_get_next(item);
		}

		group = xmlnode_get_next(group);
	}

	return buddy_root;
}