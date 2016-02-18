#include "client.h"

#include <iostream>
using namespace smartqq;

#ifdef SMARTQQ_DEBUG
#define log(str) std::cout << str << std::endl
#else
#define log(str)
#endif

SmartQQClient::SmartQQClient(MessageCallback& callback)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    login();
}

void SmartQQClient::login()
{
    getQRCode();
    string url = verifyQRCode();
    getPtwebqq(url);
    getVfwebqq();
    getUinAndPsessionid();
}

void SmartQQClient::getQRCode()
{
    log("Getting QRCode.");

    /*
     *get(SMARTQQ_API_URL(GET_QR_CODE));
     */
}

string SmartQQClient::verifyQRCode()
{
    log("Waiting for scan.");

    while (true) {
        sleep(1);
        string response = get(SMARTQQ_API_URL(VERIFY_QR_CODE));
        if (response.find("成功") != string::npos) {
            for (string::size_type i = 0, j = 0; i != string::npos; i = j + 3) {
                j = response.find("','", i);
                string content = response.substr(i, j);
                if(content.find_first_of("http") == 0)
                    return content;
            }
        } else if (response.find("已失效") != string::npos)  {
            log("QR Code's outdated. Please recquire the QR Code.");
            getQRCode();
        }
    }

}

void SmartQQClient::getPtwebqq(const string& url)
{
    log("Getting ptwebqq.");

    list<string> params;
    params.push_back(url);
    string response = get(SMARTQQ_API_URL(GET_PTWEBQQ), params);

    /* Get ptwebqq from cookies */
}

void SmartQQClient::getVfwebqq()
{
    log("Getting vfwebqq.");

    list<string> params;
    params.push_back(ptwebqq);
    string response = get(SMARTQQ_API_URL(GET_PTWEBQQ), params);

    /* Get vfwebqq from cookies */

}

void SmartQQClient::getUinAndPsessionid()
{
    log("Getting uin and psessionid.");

    /* Post JSON data */
}

list<Group> SmartQQClient::getGroupList()
{
    log("Getting group list.");

    list<Group> groups;

    return groups;
}

void SmartQQClient::pollMessage(MessageCallback &callback)
{
    log("Polling message.");
}

void SmartQQClient::sendMessageToGroup(int64_t groupId, const string &msg)
{
    log(string("Sending message to group ").append(to_string(groupId))
            .append("."));
}

void SmartQQClient::sendMessageToDiscuss(int discussId, const string& msg)
{
    log(string("Sending message to discuss ").append(to_string(discussId))
            .append("."));
}

void SmartQQClient::sendMessageToFriend(int64_t friendId, const string& msg)
{
    log(string("Sending message to friend ").append(to_string(friendId))
            .append("."));
}

list<Discuss> SmartQQClient::getDiscussList()
{
    log("Getting discuss list.");
    list<Discuss> discusses;

    return discusses;
}


list<Category> SmartQQClient::getFriendListWithCategory()
{
    log("Getting friend list with category.");
    list<Category> categories;

    return categories;
}

list<Friend> SmartQQClient::getFriendList()
{
    log("Getting friend list.");
    list<Friend> friends;

    return friends;
}

UserInfo SmartQQClient::getAccountInfo()
{
    log("Getting account info.");
    UserInfo uinfo;

    return uinfo;
}

UserInfo SmartQQClient::getFriendInfo()
{
    log("Getting friend info.");
    UserInfo uinfo;

    return uinfo;
}

list<Recent> SmartQQClient::getRecentList()
{
    log("Getting recent list.");
    list<Recent> recents;

    return recents;
}

int64_t SmartQQClient::getQQById(int64_t friendId)
{
    log(string("Getting qq by id ").append(to_string(friendId))
            .append("."));
    int64_t qq = -1;

    return qq;
}

list<FriendStatus> SmartQQClient::getFriendStatus()
{
    log("Getting friend status.");
    list<FriendStatus> fses;

    return fses;
}

GroupInfo SmartQQClient::getGroupInfo(int64_t groupCode)
{
    log(string("Getting group info of ").append(to_string(groupCode))
            .append("."));
    GroupInfo ginfo;

    return ginfo;
}

DiscussInfo SmartQQClient::getDiscussInfo(int64_t discussId)
{
    log(string("Getting group info of ").append(to_string(discussId))
            .append("."));
    DiscussInfo dinfo;

    return dinfo;
}

map<int64_t, Friend> SmartQQClient::parseFriendMap()
{
    map<int64_t, Friend> friendMap;

    return friendMap;
}

string SmartQQClient::get(const ApiUrl& url, const list<string>& params)
{

}

string SmartQQClient::post(const ApiUrl& url, const list<string>& params)
{

}

void SmartQQClient::checkSendMsgResult(string response)
{

}

string SmartQQClient::hash()
{
    return hash(uin, ptwebqq);
}

string SmartQQClient::hash(int64_t x, string K)
{
    int N[4];
    for (string::size_type T = 0; T < K.length(); T ++) {
        N[T & 0x3] ^= K.at(T);
    }
    string U[2] = {"EC", "OK"};
    int64_t V[4];
    V[0] = x >> 24 & 255 ^ U[0].at(0);
    V[1] = x >> 16 & 255 ^ U[0].at(1);
    V[2] = x >> 8 & 255 ^ U[1].at(0);
    V[3] = x & 255 ^ U[1].at(1);

    int64_t U1[8];

    for (int T = 0; T < 8; T ++) {
        U1[T] = T % 2 == 0 ? N[T >> 1] : V[T >> 1];
    }

    string N1[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    string V1 = "";
    for (int64_t i : U1) {
        V1 = V1.append(N1[(int)((i >> 4) & 0xf)])
            .append(N1[(int)(i & 15)]);
    }
    return V1;
}
