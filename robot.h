#ifndef __SMARTQQ_ROBOT_H__
#define __SMARTQQ_ROBOT_H__

#include "client.h"
#include "callback.h"
#include "smartqq.h"

#include <vector>
#include <memory>

NAMESPACE_BEGIN(smartqq)

class Robot;

class RobotPlugin : public MessageCallback{
public:
    RobotPlugin(Robot& robot) : robot_(robot) {};

    virtual void onMessage(const Message& message) = 0;
    virtual void onGroupMessage(const GroupMessage& message) = 0;
    virtual void onDiscussMessage(const DiscussMessage& message) = 0;

private:
    Robot& robot_;
};

class SuperCallback : public MessageCallback {
public:
    SuperCallback(std::vector<std::shared_ptr<RobotPlugin>>& plugins_) : plugins_(plugins_){};

    void onMessage(const Message& message);
    void onGroupMessage(const GroupMessage& message);
    void onDiscussMessage(const DiscussMessage& message);
private:
    std::vector<std::shared_ptr<RobotPlugin>>& plugins_;
};

class Robot {
public:
    Robot(SmartQQClient& client);

    void AddPlugin(std::shared_ptr<RobotPlugin> plugin);

    void Run();
private:
    SmartQQClient& client_;
    // SuperCallback will call plugins' one by one
    SuperCallback callback_;
    std::vector<std::shared_ptr<RobotPlugin>> plugins;
    friend class RobotPlugin;
};

NAMESPACE_END(smartqq)

#endif
