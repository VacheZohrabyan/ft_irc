#pragma once

#include "include.hpp"

#define ERR_CHANNELISFULL " :Cannot join channel (+l)"

class Utils
{
public:
    static std::vector<std::string> mySplit(const std::string& message, char delimiter);
    static void sendMessage(int fd, const std::string& message);

public:
    static void errorMoreParams(const std::string& nick, int fd);
    static void errorAlreadyRegister(const std::string& nick, int fd);
    static void errorNickNameInUse(const std::string& nick, int fd);
    static void errorChanelIsFull(const std::string& chanelName, int fd);
};