#include "api.h"

NAMESPACE_BEGIN(smartqq)

const std::string ApiUrl::USER_AGENT = "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36";

const ApiUrl
__GET_QR_CODE (
    "https://ssl.ptlogin2.qq.com/ptqrshow?appid=501004106&e=0&l=M&s=5&d=72&v=4&t=0.1",
    "https://ui.ptlogin2.qq.com/cgi-bin/login"
),
__VERIFY_QR_CODE (
    "https://ssl.ptlogin2.qq.com/ptqrlogin?webqq_type=10&remember_uin=1&login2qq=1&aid=501004106&u1=http%3A%2F%2Fw.qq.com%2Fproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=0-0-157510&mibao_css=m_webqq&t=1&g=1&js_type=0&js_ver=10143&login_sig=&pt_randsalt=0",
    "https://ui.ptlogin2.qq.com/cgi-bin/login"
),
__GET_PTWEBQQ (
    "{##}",
    ""
),
__GET_VFWEBQQ (
    "http://s.web2.qq.com/api/getvfwebqq?ptwebqq={##}&clientid=53999199&psessionid=&t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__GET_UIN_AND_PSESSIONID (
    "http://d1.web2.qq.com/channel/login2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_GROUP_LIST (
    "http://s.web2.qq.com/api/get_group_name_list_mask2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__POLL_MESSAGE (
    "http://d1.web2.qq.com/channel/poll2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__SEND_MESSAGE_TO_GROUP (
    "http://d1.web2.qq.com/channel/send_qun_msg2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_FRIEND_LIST (
    "http://s.web2.qq.com/api/get_user_friends2",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__SEND_MESSAGE_TO_FRIEND (
    "http://d1.web2.qq.com/channel/send_buddy_msg2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_DISCUSS_LIST (
    "http://s.web2.qq.com/api/get_discus_list?clientid=53999199&psessionid={##}&vfwebqq={##}&t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__SEND_MESSAGE_TO_DISCUSS (
    "http://d1.web2.qq.com/channel/send_discu_msg2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_ACCOUNT_INFO (
    "http://s.web2.qq.com/api/get_self_info2?t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__GET_RECENT_LIST (
    "http://d1.web2.qq.com/channel/get_recent_list2",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_FRIEND_STATUS (
    "http://d1.web2.qq.com/channel/get_online_buddies2?vfwebqq={##}&clientid=53999199&psessionid={##}&t=0.1",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_GROUP_INFO (
    "http://s.web2.qq.com/api/get_group_info_ext2?gcode={##}&vfwebqq={##}&t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__GET_QQ_BY_ID (
    "http://s.web2.qq.com/api/get_friend_uin2?tuin={##}&type=1&vfwebqq={##}&t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
),
__GET_DISCUSS_INFO (
    "http://d1.web2.qq.com/channel/get_discu_info?did={##}&vfwebqq={##}&clientid=53999199&psessionid={##}&t=0.1",
    "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
),
__GET_FRIEND_INFO (
    "http://s.web2.qq.com/api/get_friend_info2?tuin={##}&vfwebqq={##}&clientid=53999199&psessionid={##}&t=0.1",
    "http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1"
);

NAMESPACE_END(smartqq)
