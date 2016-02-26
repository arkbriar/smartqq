#ifndef __BOTPLUGIN_DICE_H__
#define __BOTPLUGIN_DICE_H__

#include "../include/robot.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <regex>

NAMESPACE_BEGIN(smartqq)

class BotDice : public RobotPlugin {
public:
    BotDice(Robot& robot) : RobotPlugin(robot) {}

    void onMessage(const Message& message) {
        static const std::regex pattern("(!Dice\\s)([0-9]+)");
        std::smatch match;
        if(std::regex_search(message.content, match, pattern)) {
            int dice_max = std::atoi(match[2].str().data());

            if(dice_max != 0) {
                GetClient().sendMessageToFriend(
                        message.uid,
                        std::string("Automatic reply: Dice result's "
                            ).append(to_string(std::rand() % dice_max))
                        );
            } else {
                GetClient().sendMessageToFriend(
                        message.uid,
                        std::string("Automatic reply: Can not do dice with upper limit equals to 0")
                        );
            }
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
