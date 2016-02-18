#include "client.h"

#include <iostream>
using namespace smartqq;

#ifdef SMARTQQ_DEBUG
#define log(str) std::cout << str << std::endl
#else
#define log(str)
#endif

#define log_err(str) std::cerr << str << std::endl;

using json = nlohmann::json;

SmartQQClient::SmartQQClient(MessageCallback& callback)
{
    login();

    pollMessage(callback);
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
    cout << "QR Code is on site below, please open in the browser.\n" <<
        SMARTQQ_API_URL(GET_QR_CODE).getUrl() << std::endl;
}

string SmartQQClient::verifyQRCode()
{
    log("Waiting for scan.");

    while (true) {
        sleep(1);
        auto r = get(SMARTQQ_API_URL(VERIFY_QR_CODE));
        string result = r.text;
        if (result.find("成功") != string::npos) {
            for (string::size_type i = 0, j = 0; i != string::npos; i = j + 3) {
                j = result.find("','", i);
                string content = result.substr(i, j);
                if(content.find_first_of("http") == 0)
                    return content;
            }
        } else if (result.find("已失效") != string::npos)  {
            log("QR Code's outdated. Try reacquire the QR Code.");
            getQRCode();
        }
    }

}

void SmartQQClient::getPtwebqq(const string& url)
{
    log("Getting ptwebqq.");

    list<string> params;
    params.push_back(url);
    auto r = get(SMARTQQ_API_URL(GET_PTWEBQQ), params);

    /* Get ptwebqq from cookies */
    ptwebqq = r.cookies["ptwebqq"];
}

void SmartQQClient::getVfwebqq()
{
    log("Getting vfwebqq.");

    list<string> params;
    params.push_back(ptwebqq);
    auto r = get(SMARTQQ_API_URL(GET_PTWEBQQ), params);

    /* Get vfwebqq */
    vfwebqq = getJsonObjectResult(r)["vfwebqq"];
}

void SmartQQClient::getUinAndPsessionid()
{
    log("Getting uin and psessionid.");

    /* Post JSON data */
    json p;
    p["ptwebqq"] = ptwebqq;
    p["clientid"] = Client_ID;
    p["psessionid"] = "";
    p["status"] = "online";

    auto r = post(SMARTQQ_API_URL(GET_UIN_AND_PSESSIONID), p);
    auto jres = getJsonObjectResult(r);
    psessionid = jres["psessionid"];
    uin = jres["uin"].get<int64_t>();
}

list<Group> SmartQQClient::getGroupList()
{
    log("Getting group list.");

    list<Group> groups;

    json j;
    j["vfwebqq"] = vfwebqq;
    j["hash"] = hash();

    auto r = post(SMARTQQ_API_URL(GET_GROUP_LIST), j);
    auto jres = getJsonObjectResult(r);

    /*@Parse JSON result into list
     * */
    return groups;
}

void SmartQQClient::pollMessage(MessageCallback &callback)
{
    log("Polling message.");

    json j;
    j["ptwebqq"] = ptwebqq;
    j["clientid"] = Client_ID;
    j["psessionid"] = psessionid;
    j["key"] = "";

    auto r = post(SMARTQQ_API_URL(POLL_MESSAGE), j);
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into list
     * */
}

void SmartQQClient::sendMessageToGroup(int64_t groupId, const string &msg)
{
    log(string("Sending message to group ").append(to_string(groupId))
            .append("."));

    json j;
    j["group_uin"] = groupId;
    j["content"] = json({msg, {"font", Font::DEFAULT_FONT.toString()}}).dump();
    j["face"] = 573;
    j["clientid"] = Client_ID;
    j["msg_id"]  = MESSAGE_ID ++;
    j["psessionid"] = psessionid;

    auto r = post(SMARTQQ_API_URL(SEND_MESSAGE_TO_GROUP), j);
    checkSendMsgResult(r);
}

void SmartQQClient::sendMessageToDiscuss(int discussId, const string& msg)
{
    log(string("Sending message to discuss ").append(to_string(discussId))
            .append("."));

    json j;
    j["did"] = discussId;
    j["content"] = json({msg, {"font", Font::DEFAULT_FONT.toString()}}).dump();
    j["face"] = 573;
    j["clientid"] = Client_ID;
    j["msg_id"]  = MESSAGE_ID ++;
    j["psessionid"] = psessionid;

    auto r = post(SMARTQQ_API_URL(SEND_MESSAGE_TO_DISCUSS), j);
    checkSendMsgResult(r);
}

void SmartQQClient::sendMessageToFriend(int64_t friendId, const string& msg)
{
    log(string("Sending message to friend ").append(to_string(friendId))
            .append("."));

    json j;
    j["to"] = friendId;
    j["content"] = json({msg, {"font", Font::DEFAULT_FONT.toString()}}).dump();
    j["face"] = 573;
    j["clientid"] = Client_ID;
    j["msg_id"] = MESSAGE_ID ++;
    j["psessionid"] = psessionid;

    auto r = post(SMARTQQ_API_URL(SEND_MESSAGE_TO_FRIEND), j);
    checkSendMsgResult(r);
}

list<Discuss> SmartQQClient::getDiscussList()
{
    log("Getting discuss list.");
    list<Discuss> discusses;

    auto r = get(SMARTQQ_API_URL(GET_DISCUSS_LIST), list<string>({psessionid, vfwebqq}));
    auto jres = getJsonObjectResult(r);
    /*@Parse result into list
     * */

    return discusses;
}


list<Category> SmartQQClient::getFriendListWithCategory()
{
    log("Getting friend list with category.");
    list<Category> categories;

    json j;
    j["vfwebqq"] = vfwebqq;
    j["hash"] = hash();

    auto r = post(SMARTQQ_API_URL(GET_FRIEND_LIST), j);
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into list
     * */

    return categories;
}

list<Friend> SmartQQClient::getFriendList()
{
    log("Getting friend list.");
    list<Friend> friends;

    json j;
    j["vfwebqq"] = vfwebqq;
    j["hash"] = hash();

    auto r = post(SMARTQQ_API_URL(GET_FRIEND_LIST), j);
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into list
     * */

    return friends;
}

UserInfo SmartQQClient::getAccountInfo()
{
    log("Getting account info.");
    UserInfo uinfo;

    auto r = get(SMARTQQ_API_URL(GET_ACCOUNT_INFO));
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into info
     * */

    return uinfo;
}

UserInfo SmartQQClient::getFriendInfo(int64_t friendId)
{
    log("Getting friend info.");
    UserInfo uinfo;

    auto r = get(SMARTQQ_API_URL(GET_FRIEND_INFO), list<string>({to_string(friendId), vfwebqq, psessionid}));
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into info
     * */
    return uinfo;
}

list<Recent> SmartQQClient::getRecentList()
{
    log("Getting recent list.");
    list<Recent> recents;

    json j;
    j["vfwebqq"] = vfwebqq;
    j["clientid"] = Client_ID;
    j["psessionid"] = "";

    auto r = post(SMARTQQ_API_URL(GET_RECENT_LIST), j);
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into list
     * */

    return recents;
}

int64_t SmartQQClient::getQQById(int64_t friendId)
{
    log(string("Getting qq by id ").append(to_string(friendId))
            .append("."));

    auto r = get(SMARTQQ_API_URL(GET_QQ_BY_ID), list<string>({to_string(friendId), vfwebqq}));
    int64_t qq = getJsonObjectResult(r)["account"].get<int64_t>();
    return qq;
}

list<FriendStatus> SmartQQClient::getFriendStatus()
{
    log("Getting friend status.");
    list<FriendStatus> fses;

    auto r = get(SMARTQQ_API_URL(GET_FRIEND_STATUS), list<string>({vfwebqq, psessionid}));
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into list
     * */

    return fses;
}

GroupInfo SmartQQClient::getGroupInfo(int64_t groupCode)
{
    log(string("Getting group info of ").append(to_string(groupCode))
            .append("."));
    GroupInfo ginfo;

    auto r = get(SMARTQQ_API_URL(GET_GROUP_INFO), list<string>({to_string(groupCode), vfwebqq}));
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into info
     * */

    return ginfo;
}

DiscussInfo SmartQQClient::getDiscussInfo(int64_t discussId)
{
    log(string("Getting group info of ").append(to_string(discussId))
            .append("."));
    DiscussInfo dinfo;
    auto r = get(SMARTQQ_API_URL(GET_DISCUSS_INFO), list<string>({to_string(discussId), vfwebqq, psessionid}));
    auto jres = getJsonObjectResult(r);
    /*@Parse JSON result into info
     * */

    return dinfo;
}

map<int64_t, Friend> SmartQQClient::parseFriendMap()
{
    map<int64_t, Friend> friendMap;

    /*@TODO
     * */
    return friendMap;
}

cpr::Response SmartQQClient::get(const ApiUrl& url)
{
    return get(url, map<string, string>());
}

cpr::Response SmartQQClient::get(const ApiUrl& url, const list<string>& params)
{
    session.SetUrl(url.buildUrl(params));
    session.SetHeader({{"User-Agent", ApiUrl::USER_AGENT}, {"Referer", url.getReferer()}});

    return session.Get();
}

cpr::Response SmartQQClient::get(const ApiUrl& url, const map<string, string>& params)
{
    session.SetUrl(url.getUrl());
    session.SetHeader({{"User-Agent", ApiUrl::USER_AGENT}, {"Referer", url.getReferer()}});
    cpr::Parameters _cpr_params;
    for (auto pair : params) {
        _cpr_params.AddParameter({pair.first, pair.second});
    }
    session.SetParameters(std::move(_cpr_params));

    return session.Get();
}

cpr::Response SmartQQClient::post(const ApiUrl& url)
{
    return post(url, json());
}

cpr::Response SmartQQClient::post(const ApiUrl& url, const json& jparam)
{
    session.SetUrl(url.getUrl());
    session.SetHeader({{"User-Agent", ApiUrl::USER_AGENT}, {"Referer", url.getReferer()}, {"Origin", url.getOrigin()}});

    cpr::Payload _cpr_form({{"r", jparam.dump()}});
    session.SetPayload(std::move(_cpr_form));

    return session.Get();
}

void SmartQQClient::checkSendMsgResult(cpr::Response r)
{
    if (r.status_code != 200) {
        log_err(string("Send failed. Http status code's ").append(to_string(r.status_code)));
    }

    json j = json::parse(r.text);
    int err_code = j["errCode"].get<int>();
    if (err_code == 0) {
        log("Send succeeded.");
    } else {
        log_err(string("Send failed. Api return code's ").append(to_string(err_code)));
    }
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

void SmartQQClient::sleep(int64_t seconds)
{

}

void SmartQQClient::close()
{

}

json SmartQQClient::getResponseJson(const cpr::Response& r)
{
    json ret;
    /*@TODO
     * */

    return ret;
}

json SmartQQClient::getJsonObjectResult(const cpr::Response& r)
{
    return getResponseJson(r)["result"].get<json>();
}
