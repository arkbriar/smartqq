#ifndef __SMARTQQ_API_H__
#define __SMARTQQ_API_H__

#include <string>
#include <list>

#include "smartqq.h"

NAMESPACE_BEGIN(smartqq)

struct ApiUrl {
    static const std::string USER_AGENT;

    ApiUrl(const std::string &url, const std::string &referer) :
        url(url), referer(referer) {}

    std::string getUrl() const {
        return url;
    }

    std::string getReferer() const {
        return referer;
    }

    std::string getOrigin() const {
        return url.substr(0, url.find_last_of('/'));
    }

    std::string buildUrl(const std::list<std::string>& paramList) const {
        std::string __url = this->url;
        for (auto i : paramList) {
            __url = __url.replace(__url.find_first_of("{##}"), 4, i);
        }
        return __url;
    }

private:
    std::string url;
    std::string referer;
};

const std::string ApiUrl::USER_AGENT = "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36";

extern const ApiUrl
__GET_QR_CODE,
__VERIFY_QR_CODE,
__GET_PTWEBQQ,
__GET_VFWEBQQ,
__GET_UIN_AND_PSESSIONID,
__GET_GROUP_LIST,
__POLL_MESSAGE,
__SEND_MESSAGE_TO_GROUP,
__GET_FRIEND_LIST,
__SEND_MESSAGE_TO_FRIEND,
__GET_DISCUSS_LIST,
__SEND_MESSAGE_TO_DISCUSS,
__GET_ACCOUNT_INFO,
__GET_RECENT_LIST,
__GET_FRIEND_STATUS,
__GET_GROUP_INFO,
__GET_QQ_BY_ID,
__GET_DISCUSS_INFO,
__GET_FRIEND_INFO;

#define SMARTQQ_API_URL(URL_NAME) __##URL_NAME

NAMESPACE_END(smartqq)
#endif
