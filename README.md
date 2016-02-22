Smart QQ C++
================

从[Smart QQ Java](https://github.com/ScienJus/smartqq)改写。

DEPENDENCY
----------------

1\. [CPR](https://github.com/whoshuu/cpr) (LICENSE MIT)

2\. [JSON for Modern C++](https://github.com/nlohmann/json) (LICENSE MIT)

3\. libcurl, version>=7.22

FEATURES
----------------

实现主体对象Robot，可以通过继承RobotPlugin进行插件开发

主要插件如下：

1\. 接入TURING ROBOT，可以进行中文简单问答，格式 !Bot Question，回复会有Bot reply:的头，默认间隔2s回复一次(进程sleep 2s)

2\. 简单Dice，格式 !Dice num，以num为上限输出随机数(num为0会挂)

3\. 消息输出(CommonChat)，将发送人和信息输出到stdout

[**WARNING**]别太快发消息，会发不出去(怕封号)

BUILD
----------------

可以通过以下方式在linux上编译测试

> mkdir build

> cd mkdir

> cmake .. & make

LICENSE
----------------

MIT
