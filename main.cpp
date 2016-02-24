#include "smartqq.hpp"
#include "client.hpp"
#include "robot.hpp"
#include "botplugin/dice.hpp"
#include "botplugin/turingbot.hpp"

#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char *argv[])
{
    smartqq::SmartQQClient c;
    smartqq::Robot r(c);
    shared_ptr<smartqq::RobotPlugin> d(new smartqq::BotDice(r));
    shared_ptr<smartqq::TuringBot> t(new smartqq::TuringBot(r));
    r.AddPlugin({d, t});

    r.Run();

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(3600));
    }
    return 0;
}
