#ifndef __SMARTQQ_MODEL_H__
#define __SMARTQQ_MODEL_H__

#include <string>
#include <cstring>
#include <list>
#include <cstdlib>
#include <sstream>

#include "smartqq.h"

#include "json.hpp"

NAMESPACE_BEGIN(smartqq)

using namespace std;

struct Birthday {
    int year;
    int month;
    int day;

    Birthday() {}

    Birthday(nlohmann::json json) {
        year = json["year"];
        month = json["month"];
        day = json["day"];
    }
};

struct Friend;

struct Category {
    int index;
    int sort;
    string name;
    list<Friend> friends;

    Category() {}

    Category(nlohmann::json json) {
        index = json["index"];
        sort = json["sort"];
        name = json["name"];
    }

    static Category defaultCategory() {
        Category c;
        c.index = 0;
        c.sort = 0;
        c.name = "我的好友";
        return c;
    }
};

struct Discuss {
    int64_t id;
    string name;

    Discuss() {}

    Discuss(nlohmann::json json) {
        id = json["did"].get<int64_t>();
        name = json["name"];
    }
};

struct DiscussUser {
    int64_t uin;
    string nick;
    int clientType;
    string status;

    string toString() const {
        string ret = "DiscussUser{";
        return ret.append("uin=").append(to_string(uin))
            .append(", nick='").append(nick).append("'")
            .append(", cliendType='").append(to_string(clientType)).append("'")
            .append(", status='").append(status).append("'")
            .append("}");
    }

    DiscussUser() {}

    DiscussUser(nlohmann::json json) {
        uin = json["uin"];
        nick = json["nick"];
        clientType = json["client_type"];
        status = json["status"];
    }
};

struct DiscussInfo {
    int64_t id;
    string name;
    list<DiscussUser> users;

    DiscussInfo() {}

    DiscussInfo(nlohmann::json json) {
        id = json["did"];
        name = json["discu_name"];
    }
};

struct Font;

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

    Font() {}

    Font(nlohmann::json json) {
        color = json["color"].get<string>();
        name = json["name"].get<string>();
        size = json["size"].get<int>();
        int j = 0;
        for (auto i : json["style"].get<vector<int>>()) {
            style[j ++] = i;
        }
    }

    string toString() const {
        nlohmann::json _j;
        nlohmann::json j;
        j["style"] = {style[0], style[1], style[2]};
        j["color"] = color;
        j["name"] = name;
        j["size"] = size;
        _j["Font"] = j;
        return _j.dump();
    }
};

struct DiscussMessage {
    int64_t did;
    int64_t time;
    string content;
    int64_t uid;
    Font font;

    DiscussMessage() {}

    DiscussMessage(nlohmann::json json) {
        time = json["time"].get<int64_t>();
        did = json["did"].get<int64_t>();
        uid = json["send_uin"].get<int64_t>();
        auto _content = json["content"].get<vector<nlohmann::json>>();
        font = Font(_content.front().
                get<list<nlohmann::json>>().back());
        auto msg = _content.back();
        if(msg.is_array()) {
            // ["face", 10]
            auto _face = msg.get<vector<nlohmann::json>>();
            content = string("/").append(_face.front().get<string>())
                .append("#")
                .append(std::to_string(_face.back().get<int>()));
            // "/face#10"
        } else content = msg.get<string>();
    }
};

struct Friend {
    int64_t userId;
    string markname;
    string nickname;
    bool vip;
    int vipLevel;

    string toString() const {
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

    FriendStatus() {}

    FriendStatus(nlohmann::json json) {
        uin = json["uin"];
        status = json["status"];
        clientType = json["client_type"];
    }
};

struct Group {
    int64_t id;
    string name;
    int64_t flag;
    int64_t code;

    static Group parseJson(const nlohmann::json& json) {
        Group g;
        g.id = json["gid"].get<int64_t>();
        g.name = json["name"].get<string>();
        g.flag = json["flag"].get<int64_t>();
        g.code = json["code"].get<int64_t>();
        return g;
    }
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

    GroupUser() {}

    GroupUser(nlohmann::json json) {
        nick = json["nick"];
        province = json["province"];
        gender = json["gender"];
        uin = json["uin"];
        country = json["country"];
        city = json["city"];
        card = json["card"];
        clientType = json["client_type"];
        status = json["status"];
        vip = json["vip"];
        vipLevel = json["vipLevel"];
    }
};

struct GroupInfo {
    int64_t gid;
    int64_t createtime;
    string memo;
    string name;
    int64_t owner;
    string markname;
    list<GroupUser> users;

    GroupInfo() {}

    GroupInfo(nlohmann::json json) {
        gid = json["gid"];
        createtime = json["createtime"];
        memo = json["memo"];
        name = json["name"];
        owner = json["owner"];
        markname = json["markname"];
    }
};

struct GroupMessage {
    int64_t gid;
    int64_t time;
    string content;
    int64_t uid;
    Font font;

    GroupMessage() {}

    GroupMessage(nlohmann::json json) {
        time = json["time"].get<int64_t>();
        gid = json["group_code"].get<int64_t>();
        uid = json["send_uin"].get<int64_t>();
        auto _content = json["content"].get<list<nlohmann::json>>();
        font = Font(_content.front().
                get<list<nlohmann::json>>().back());
        auto msg = _content.back();
        if(msg.is_array()) {
            // ["face", 10]
            auto _face = msg.get<vector<nlohmann::json>>();
            content = string("/").append(_face.front().get<string>())
                .append("#")
                .append(std::to_string(_face.back().get<int>()));
            // "/face#10"
        } else content = msg.get<string>();
    }
};

struct Message {
    int64_t time;
    string content;
    int64_t uid;
    Font font;

    Message() {}
    Message(nlohmann::json json) {
        time = json["time"].get<int64_t>();
        uid = json["from_uin"].get<int64_t>();
        auto _content = json["content"].get<list<nlohmann::json>>();
        font = Font(_content.front().
                get<list<nlohmann::json>>().back());
        auto msg = _content.back();
        if(msg.is_array()) {
            // ["face", 10]
            auto _face = msg.get<vector<nlohmann::json>>();
            content = string("/").append(_face.front().get<string>())
                .append("#")
                .append(std::to_string(_face.back().get<int>()));
            // "/face#10"
        } else content = msg.get<string>();
    }
};

struct Recent {
    int64_t uin;
    // 0:Friend, 1:Group, 2:Discuss
    int type;

    Recent() {}

    Recent(nlohmann::json json) {
        uin = json["uin"];
        type = json["type"];
    }
};

struct UserInfo {
    Birthday birthday;
    string phone;
    string occupation;
    string college;
    string uin;
    int blood;
    string lnick;
    string homepage;
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

    UserInfo() {}

    UserInfo(nlohmann::json json) {
        birthday = json["birthday"];
        phone = json["phone"];
        occupation = json["occupation"];
        college = json["college"];
        uin = json["uin"];
        blood = json["blood"];
        lnick = json["lnick"];
        homepage = json["homepage"];
        vipInfo = json["vip_info"];
        city = json["city"];
        country = json["country"];
        province = json["province"];
        personal = json["personal"];
        shengxiao = json["shengxiao"];
        nick = json["nick"];
        email = json["email"];
        account = json["account"];
        gender = json["gender"];
        mobile = json["mobile"];
    }
};

NAMESPACE_END(smartqq)

#endif
