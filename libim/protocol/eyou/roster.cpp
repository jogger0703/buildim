#include "roster.h"
#include "xmlnode.h"


/**
 * 从xml中解析出联系人的结构，填充到给定的树根里
 * @root 联系人根。这个根是虚根。里边没有真实的可用数据
 * @xml xml节点
 * @成功返回树根，失败返回NULL
 */
im_buddy_node* parse_roster_from_xml(im_buddy_node* buddy_root, const char* xml)
{
// <iq id="2" type="ok" to="im@eyou.net" method="roster">
// 	<group name="渠道部" type="sys" pos="0">
// 		<item uid="chenna@eyou.net" name="陈娜-890" realname = "陈娜"/>
// 		<item uid="lilijuan@eyou.net" name="李丽娟-325" realname = "李丽娟"/>
// 		<item uid="zhangyue@eyou.net" name="张跃-376" realname = "张跃"/>
// 	</group>
// 	<group name="市场部" type="sys" pos="0">
// 		<item uid="xiangwenwen@eyou.net" name="向文雯-271" realname = "向文雯"/>
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