#include "robot.h"

using namespace smartqq;

void SuperCallback::onMessage(const Message &message)
{
    for (auto p : plugins_) {
        p->onMessage(message);
    }
}

void SuperCallback::onGroupMessage(const GroupMessage &message)
{
    for (auto p : plugins_) {
        p->onGroupMessage(message);
    }
}

void SuperCallback::onDiscussMessage(const DiscussMessage &message)
{
    for (auto p : plugins_) {
        p->onDiscussMessage(message) ;
    }
}

Robot::Robot(SmartQQClient& client) : client_(client),
    callback_(plugins) {}

void Robot::AddPlugin(std::shared_ptr<RobotPlugin> plugin)
{
    plugins.push_back(plugin);
}

void Robot::Run()
{
    client_.startPolling(callback_);
}

