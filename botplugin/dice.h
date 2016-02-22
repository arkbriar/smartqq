#ifndef __BOTPLUGIN_DICE_H__
#define __BOTPLUGIN_DICE_H__

#include "../robot.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

NAMESPACE_BEGIN(smartqq)

class BotDice : public RobotPlugin {
public:
    BotDice(Robot& robot) : RobotPlugin(robot) {}

    void onMessage(const Message& message) {
        if(message.content == "$Dice") {
            GetClient().sendMessageToFriend(
                    message.uid,
                    std::string("Automatic reply: Dice result's "
                        ).append(to_string(std::rand() % 6))
                    );
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void onGroupMessage(const GroupMessage& message) {
        // Do nothing
    }

    void onDiscussMessage(const DiscussMessage& message) {
        // Do nothing
    }
};

NAMESPACE_END(smartqq)

#endif
