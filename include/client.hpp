#ifndef __SMARTQQ_CLIENT_H__
#define __SMARTQQ_CLIENT_H__

#include "smartqq.hpp"
#include "model.hpp"
#include "callback.hpp"
#include "api.hpp"

/* Use JSON library from https://github.com/hlohmann/json
 * Convenient copy 2016.02.18*/
#include <json.hpp>

#include <map>
#include <thread>

#include <cpr/cpr.h>

NAMESPACE_BEGIN(smartqq)

class SmartQQClient {
public:
    static int64_t MESSAGE_ID;
    static const int64_t Client_ID;

    string ptwebqq;
    string vfwebqq;
    int64_t uin;
    string psessionid;

    SmartQQClient();

    void login();

    void getQRCode();

    string verifyQRCode();

    void getPtwebqq(const string& url);

    void cgiReport();

    void getVfwebqq();

    void afterVfwebqq();

    void getUinAndPsessionid();

    void pollMessage(MessageCallback &callback);

    void sendMessageToGroup(int64_t groupId, const string& msg);

    void sendMessageToDiscuss(int discussId, const string& msg);

    void sendMessageToFriend(int64_t friendId, const string& msg);

    list<Group> getGroupList();

    list<Discuss> getDiscussList();

    list<Category> getFriendListWithCategory();

    list<Category> getFriendListWithCategory(std::map<int64_t, Friend>& friendMap);

    list<Friend> getFriendList();

    list<Recent> getRecentList();

    UserInfo getAccountInfo();

    UserInfo getFriendInfo(int64_t friendId);

    list<FriendStatus> getFriendStatus();

    GroupInfo getGroupInfo(int64_t groupCode);

    DiscussInfo getDiscussInfo(int64_t discussId);

    int64_t getQQById(int64_t friendId);

    void startPolling(MessageCallback& callback);

private:

    void pollThread(MessageCallback &callback);

    static map<int64_t, Friend> parseFriendMap(const nlohmann::json& json);

    cpr::Response get(const ApiUrl& url);

    cpr::Response get(const ApiUrl& url, const list<string>& params);

    cpr::Response get(const ApiUrl& url, const map<string, string>& params);

    cpr::Response post(const ApiUrl& url);

    cpr::Response post(const ApiUrl& url, const nlohmann::json& jparam);

    static void checkSendMsgResult(const cpr::Response& r);

    string hash();

    static void sleep(int64_t seconds);

    static string hash(int64_t x, string K);

    void close();

    static nlohmann::json getResponseJson(const cpr::Response& r);

    static nlohmann::json::array_t getJsonArrayResult(const cpr::Response& r);

    static nlohmann::json getJsonObjectResult(const cpr::Response& r);

    cpr::Session session;

    cpr::Cookies cookies;

    bool pollStarted;

    std::mutex mutex;
};

NAMESPACE_END(smartqq)

#endif
