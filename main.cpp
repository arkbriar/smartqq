#include "smartqq.h"
#include "client.h"
#include "robot.h"
#include "botplugin/dice.h"
#include "botplugin/turingbot.h"

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
