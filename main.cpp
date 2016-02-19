#include "smartqq.h"
#include "client.h"

#include <iostream>
using namespace std;

class _MessageCallback : public smartqq::MessageCallback {
public:
    void onMessage(smartqq::Message message) {
        cout << "Message: " << message.content << endl;
    }

    void onGroupMessage(smartqq::GroupMessage message) {
        cout << "Group message: " << message.content << endl;
    }

    void onDiscussMessage(smartqq::DiscussMessage message) {
        cout << "Discuss message: " << message.content << endl;
    }
};

int main(int argc, char *argv[])
{
    _MessageCallback t;
    smartqq::SmartQQClient client(t);
    return 0;
}
