#include "smartqq.h"
#include "client.h"
#include "robot.h"
#include "botplugin/dice.h"
#include "botplugin/turingbot.h"

#include <iostream>
#include <memory>
using namespace std;

class PluginTest : public smartqq::RobotPlugin {
public:
    PluginTest(smartqq::Robot& robot) : RobotPlugin(robot) {}
    void onMessage(const smartqq::Message& message) {
        cout << "Message: " << message.content << endl;
    }

    void onGroupMessage(const smartqq::GroupMessage& message) {
        cout << "Group message: " << message.content << endl;
    }

    void onDiscussMessage(const smartqq::DiscussMessage& message) {
        cout << "Discuss message: " << message.content << endl;
    }
};

int main(int argc, char *argv[])
{
    smartqq::SmartQQClient c;
    smartqq::Robot r(c);
    shared_ptr<smartqq::RobotPlugin> p(new PluginTest(r));
    shared_ptr<smartqq::RobotPlugin> d(new smartqq::BotDice(r));
    shared_ptr<smartqq::TuringBot> t(new smartqq::TuringBot(r));
    r.AddPlugin(p);
    r.AddPlugin(d);
    r.AddPlugin(t);

    r.Run();

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(3600));
    }
    return 0;
}
