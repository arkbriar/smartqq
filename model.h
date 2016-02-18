#ifndef __SMARTQQ_MODEL_H__
#define __SMARTQQ_MODEL_H__

#include <string>
#include <cstring>
#include <list>
#include <cstdlib>
#include <sstream>

#include "smartqq.h"

NAMESPACE_BEGIN(smartqq)

using namespace std;

struct Birthday {
    int year;
    int month;
    int day;
};

struct Friend;

struct Category {
    int index;
    int sort;
    string name;
    list<Friend> friends;
};

struct Discuss {
    int64_t id;
    string name;
};

struct DiscussUser {
    int64_t uin;
    string nick;
    int clientType;
    string status;

    string toString() {
        string ret = "DiscussUser{";
        return ret.append("uin=").append(to_string(uin))
            .append(", nick='").append(nick).append("\'")
            .append(", cliendType='").append(to_string(clientType)).append("\'")
            .append(", status='").append(status).append("\'")
            .append("}");
    }
};

struct DiscussInfo {
    int64_t id;
    string name;
    list<DiscussUser> users;
};

struct Font;

struct DiscussMessage {
    int64_t discussId;
    int64_t time;
    string content;
    int64_t userId;
    Font& font;
};

struct Font {
    static const Font DEFAULT_FONT;

    int style[3];
    string color;
    string name;
    int size;

    static Font defaultFont() {
        Font font;
        font.color = "000000";
        memset(font.style, 0, sizeof(font.style));
        font.name = "宋体";
        font.size = 10;
        return font;
    }
};

const Font Font::DEFAULT_FONT = defaultFont();

struct Friend {
    int64_t userId;
    string markname;
    string nickname;
    bool vip;
    int vipLevel;

    string toString() {
        string ret;
        stringstream ss;
        ss << "Friend{" << "userId=" << userId << ", markname='" << markname
            << "', nickname'" << nickname << "'" << ", vip=" << vip << ", vipLevel=" << vipLevel << "}";

        ss >> ret;
        return ret;
    }
};

struct FriendStatus {
    int64_t uin;
    string status;
    int clientType;
};

struct Group {
    int64_t id;
    string name;
    int64_t flag;
    int64_t code;
};

struct GroupUser {
    string nick;
    string province;
    string gender;
    int64_t uin;
    string country;
    string city;
    string card;
    int clientType;
    int status;
    bool vip;
    int vipLevel;
};

struct GroupInfo {
    int64_t gid;
    int64_t createtime;
    string memo;
    string name;
    int64_t owner;
    string markname;
    list<GroupUser> users;
};

struct GroupMessage {
    int64_t gid;
    int64_t time;
    string content;
    int64_t uid;
    Font& font;
};

struct Message {
    int64_t time;
    string content;
    int64_t uid;
    Font& font;
};

struct Recent {
    int64_t uin;
    int type;
};

struct UserInfo {
    Birthday birthday;
    string phone;
    string occupation;
    string college;
    string uin;
    int blood;
    string lnick;
    string homoepage;
    int vipInfo;
    string city;
    string country;
    string province;
    string personal;
    int shengxiao;
    string nick;
    string email;
    string account;
    string gender;
    string mobile;
};

NAMESPACE_END(smartqq)

#endif
