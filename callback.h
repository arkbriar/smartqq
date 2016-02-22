#ifndef __SMARTQQ_CALLBACK_H__
#define __SMARTQQ_CALLBACK_H__

#include "model.h"
#include "smartqq.h"

NAMESPACE_BEGIN(smartqq)

class MessageCallback {
protected:
    MessageCallback() {}
public:
    virtual void onMessage(const Message& message) = 0;
    virtual void onGroupMessage(const GroupMessage& message) = 0;
    virtual void onDiscussMessage(const DiscussMessage& message) = 0;
};

NAMESPACE_END(smartqq)
#endif
