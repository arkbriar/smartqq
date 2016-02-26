#include "robot.hpp"

using namespace smartqq;

class CommonChat : public RobotPlugin {
public:
    CommonChat(smartqq::Robot& robot) : RobotPlugin(robot) {}
    void onMessage(const Message& message) {
        //Deal with new friend
        if (GetFriendMap().find(message.uid) == GetFriendMap().end()) {
            UpdateFriendList();
        }
        std::string name = GetFriendMap().at(message.uid).markname;
        if(name == "") name = GetFriendMap().at(message.uid).nickname;
        cout << "Message from " << name << ": "
            << message.content << endl;
    }

    void onGroupMessage(const GroupMessage& message) {
        std::string groupname;
        for (auto i : GetGroups()) {
            if (i.id == message.gid) {
                groupname = i.name;
                break;
            }
        }
        if (groupname.empty()) {
            UpdateGroupList();

            for (auto i : GetGroups()) {
                if (i.id == message.gid) {
                    groupname = i.name;
                    break;
                }
            }
        }
        if (groupname.empty()) groupname = "NotFound";
        cout << "Group message from user " << std::to_string(message.uid)
            << " in group " << groupname
            << ": " << message.content << endl;
    }

    void onDiscussMessage(const smartqq::DiscussMessage& message) {
        std::string discussname;
        for (auto i : GetDiscusses()) {
            if (i.id == message.did) {
                discussname = i.name;
                break;
            }
        }
        if (discussname.empty()) {
            UpdateDiscussList();

            for (auto i : GetDiscusses()) {
                if (i.id == message.did) {
                    discussname = i.name;
                    break;
                }
            }
        }
        if(discussname.empty()) discussname = "NotFound";
        cout << "Discuss message from user " << std::to_string(message.uid)
            << "in discuss " << discussname
            << ": " << message.content << endl;
    }
};

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
    callback_(plugins)
{
    AddPlugin(std::shared_ptr<RobotPlugin>(new CommonChat(*this)));
}

void Robot::AddPlugin(std::shared_ptr<RobotPlugin> plugin)
{
    plugins.push_back(plugin);
}

void Robot::AddPlugin(const std::list<std::shared_ptr<RobotPlugin>>& plugin_list)
{
    for (auto i : plugin_list) {
        plugins.push_back(i);
    }
}

void Robot::Run()
{
    client_.login();

    categories_ = client_.getFriendListWithCategory(friendMap_);
    groups_ = client_.getGroupList();
    discusses_ = client_.getDiscussList();

    client_.startPolling(callback_);
}

