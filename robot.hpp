#ifndef __SMARTQQ_ROBOT_H__
#define __SMARTQQ_ROBOT_H__

#include "client.hpp"
#include "callback.hpp"
#include "smartqq.hpp"

#include <vector>
#include <list>
#include <map>
#include <memory>

NAMESPACE_BEGIN(smartqq)

class RobotPlugin;

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

    void AddPlugin(const std::list<std::shared_ptr<RobotPlugin>>& plugin_list);

    void Run();
private:
    friend class RobotPlugin;

    SmartQQClient& client_;
    // SuperCallback will call plugins' one by one
    SuperCallback callback_;
    std::vector<std::shared_ptr<RobotPlugin>> plugins;

    std::list<Category> categories_;
    std::list<Group> groups_;
    std::list<Discuss> discusses_;
    std::map<int64_t, Friend> friendMap_;
};

class RobotPlugin : public MessageCallback{
public:
    RobotPlugin(Robot& robot) : robot_(robot) {};

    virtual void onMessage(const Message& message) = 0;
    virtual void onGroupMessage(const GroupMessage& message) = 0;
    virtual void onDiscussMessage(const DiscussMessage& message) = 0;

    SmartQQClient& GetClient() const {
        return robot_.client_;
    }

    const std::list<Category>& GetCategories() const {
        return robot_.categories_;
    }

    const std::list<Group>& GetGroups() const {
        return robot_.groups_;
    }

    const std::list<Discuss>& GetDiscusses() const {
        return robot_.discusses_;
    }

    const std::map<int64_t, Friend>& GetFriendMap() const {
        return robot_.friendMap_;
    }

    void UpdateFriendList() const {
        robot_.categories_ = robot_.client_.getFriendListWithCategory(robot_.friendMap_);
    }

    void UpdateGroupList() const {

        robot_.groups_ = robot_.client_.getGroupList();

        for (auto& i : robot_.groups_) {
            i.ginfo = robot_.client_.getGroupInfo(i.code);
        }

    }

    void UpdateDiscussList() const {
        robot_.discusses_ = robot_.client_.getDiscussList();

        for (auto& i : robot_.discusses_) {
            i.dinfo = robot_.client_.getDiscussInfo(i.id);
        }

    }

protected:
    Robot& robot_;
};

NAMESPACE_END(smartqq)

#endif
