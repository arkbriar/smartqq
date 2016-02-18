#ifndef __SMARTQQ_CALLBACK_H__
#define __SMARTQQ_CALLBACK_H__

#include "model.h"
#include "smartqq.h"

NAMESPACE_BEGIN(smartqq)

class MessageCallback {
protected:
    MessageCallback() {}
public:
    virtual void onMessage(Message message) = 0;
    virtual void onGroupMessage(GroupMessage message) = 0;
    virtual void onDiscussMessage(DiscussMessage message) = 0;
};

NAMESPACE_END(smartqq)
#endif
