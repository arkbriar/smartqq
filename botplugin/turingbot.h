#ifndef __BOTPLUGIN_TURINGBOT_H__
#define __BOTPLUGIN_TURINGBOT_H__

#include "../robot.h"
#include "../json.hpp"
#include "../utils.h"
#include <cpr/session.h>

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <vector>
#include <map>
#include <regex>

NAMESPACE_BEGIN(smartqq)

class TuringException : public std::exception {
public:
    TuringException() {}
    TuringException(const std::string& msg) : error_msg(msg) {}
    const char* what() const noexcept {
        return error_msg.data();
    }

private:
    std::string error_msg;
};

class TuringRobotClient {
public:
    static std::string GenerateId() {
        static int now_length = 1;
        static char now_char = '0';

        static std::string last_ret_before_length_increase = "";

        std::string ret;

        if(now_length > (int)last_ret_before_length_increase.length()) {
            ret = last_ret_before_length_increase + now_char;
        }

        now_char ++;
        if(now_char > '9') {
            now_length ++;
            now_char= '0';
            last_ret_before_length_increase = ret;
        }

        return ret;
    }

    std::string Ask(std::string msg, std::string userid = "", std::string loc = "") {
        if(stows(msg).length() > 30 || userid.length() > 30 || loc.length() > 30) {
            throw TuringException("Some of params is too long.");
        } else if(msg == "") {
            throw TuringException("Message is empty.");
        }
        nlohmann::json query;
        query["key"] = key;
        query["info"] = msg;
        if(userid != "") query["userid"] = userid;
        if(loc != "") query["loc"] = loc;

        auto r = Post(query);

        return Process(r);
    }

private:

    cpr::Session session;

    const std::string API_URL = "http://www.tuling123.com/openapi/api";

    const std::string USER_AGENT = "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36";

    const std::string key = "3ad88a315d25403cc9e74f9b627735e9";

    cpr::Response Post(const nlohmann::json& query) {
        session.SetUrl(API_URL);
        session.SetHeader({{"User-Agent", USER_AGENT}, {"Content-Type", "application/x-www-form-urlencoded"}});

        cpr::Payload _cpr_form({});
        for (auto it = query.begin(); it != query.end(); ++ it) {
            _cpr_form.AddPair({std::string(it.key()),
                    it.value().get<std::string>()});
        }

        session.SetPayload(_cpr_form);

        return session.Post();
    }

    std::string Process(const cpr::Response& response) {
        if(response.status_code != 200) {
            throw TuringException(string("Http request failed. Http status code's").append(std::to_string(response.status_code)));
        }

        nlohmann::json res_json = nlohmann::json::parse(response.text);
        auto code = res_json["code"].get<int>();

        std::string ret;
        // API exceptions
        switch (code) {
            case 40001:
            case 40002:
            case 40004:
            case 40007:
                throw TuringException(res_json["text"].get<std::string>());
                break;

            //Talk
            case 100000:
                return res_json["text"];
                break;

            //Url
            case 200000:
                return ret.append(res_json["text"]).append("\n")
                    .append(res_json["url"]);
                break;

            //News
            case 302000:
                {
                    auto newslist = res_json["list"].get<std::vector<nlohmann::json>>();
                    ret.append(res_json["text"]).append("\n");
                    for (auto news : newslist) {
                        ret.append(news.dump()).append("\n");
                        break;
                    }

                    return ret;
                }
                break;

            // Recipe
            case 308000:
                {
                    auto newslist = res_json["list"].get<std::vector<nlohmann::json>>();
                    ret.append(res_json["text"]).append("\n");
                    for (auto news : newslist) {
                        ret.append(news.dump()).append("\n");
                        break;
                    }

                    return ret;
                }
                break;
            default:
                throw TuringException("Invalid code.");
                break;
        }
    }
};

class TuringBot : public RobotPlugin {
public:
    TuringBot(Robot& robot) : RobotPlugin(robot),
        pattern("(!Bot\\s)(.+)"){}

    void onMessage(const Message& message) {
        std::smatch match;
        if(std::regex_search(message.content, match, pattern)) {
            // check id map
            if(idmap_.find(message.uid) == idmap_.end()) {
                idmap_.insert({message.uid, TuringRobotClient::GenerateId()});
            }
            auto msg = match[2];

            try {
                auto reply = client.Ask(msg, idmap_.at(message.uid));

                GetClient().sendMessageToFriend(message.uid, reply.insert(0, "Bot reply: "));

                std::this_thread::sleep_for(std::chrono::seconds(2));
            } catch (TuringException e) {
                std::cerr << e.what() << endl;
            }
        }
    }

    void onGroupMessage(const GroupMessage& message) {
        // Do nothing
    }

    void onDiscussMessage(const DiscussMessage& message) {
        // Do nothing
    }

private:
    std::regex pattern;

    TuringRobotClient client;

    // map qq's uid to turingbot's userid
    std::map<int64_t, std::string> idmap_;
};

NAMESPACE_END(smartqq)


#endif
