#ifndef __SMARTQQ_CLIENT_H__
#define __SMARTQQ_CLIENT_H__

#include "smartqq.h"
#include "model.h"
#include "callback.h"
#include "api.h"

/* Use JSON library from https://github.com/hlohmann/json
 * Convenient copy 2016.02.18*/
#include "json.hpp"

#include <map>

#include <cpr/cpr.h>

NAMESPACE_BEGIN(smartqq)

class SmartQQClient {
public:
    static int64_t MESSAGE_ID;
    static const int64_t Client_ID;

    cpr::Session session;

    string ptwebqq;
    string vfwebqq;
    int64_t uin;
    string psessionid;

    bool pollStarted;

    SmartQQClient(MessageCallback& callback);

    void login();

    void getQRCode();

    string verifyQRCode();

    void getPtwebqq(const string& url);

    void getVfwebqq();

    void getUinAndPsessionid();

    list<Group> getGroupList();

    void pollMessage(MessageCallback &callback);

    void sendMessageToGroup(int64_t groupId, const string& msg);

    void sendMessageToDiscuss(int discussId, const string& msg);

    void sendMessageToFriend(int64_t friendId, const string& msg);

    list<Discuss> getDiscussList();

    list<Category> getFriendListWithCategory();

    list<Friend> getFriendList();

    UserInfo getAccountInfo();

    UserInfo getFriendInfo(int64_t friendId);

    list<Recent> getRecentList();

    int64_t getQQById(int64_t friendId);

    list<FriendStatus> getFriendStatus();

    GroupInfo getGroupInfo(int64_t groupCode);

    DiscussInfo getDiscussInfo(int64_t discussId);

private:

    static map<int64_t, Friend> parseFriendMap(nlohmann::json json);

    cpr::Response get(const ApiUrl& url);

    cpr::Response get(const ApiUrl& url, const list<string>& params);

    cpr::Response get(const ApiUrl& url, const map<string, string>& params);

    cpr::Response post(const ApiUrl& url);

    cpr::Response post(const ApiUrl& url, const nlohmann::json& jparam);

    static void checkSendMsgResult(cpr::Response r);

    string hash();

    static void sleep(int64_t seconds);

    static string hash(int64_t x, string K);

    void close();

    static nlohmann::json getResponseJson(const cpr::Response& r);

    static nlohmann::json::array_t getJsonArrayResult(const cpr::Response& r);

    static nlohmann::json getJsonObjectResult(const cpr::Response& r);
};

int64_t SmartQQClient::MESSAGE_ID = 32690001L;
const int64_t SmartQQClient::Client_ID = 53999199L;

NAMESPACE_END(smartqq)

#endif
