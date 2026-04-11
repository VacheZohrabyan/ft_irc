#pragma once

#include "include.hpp"

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
    static void errorBadChanMask(const std::string& chanelName, int fd);
    static void errorNoSuchChannel(const std::string& chanelName, int fd);
    static void errorTooManyChannels(const std::string& chanelName, int fd);
    static void errorChannelIsFull(const std::string& chanelName, int fd);
    static void errorNoSuchNick(const std::string& chanelName, int fd);
    static void errorNoTestToSend(int fd);
    static void errorNotOnChannel(const std::string& chanelName, int fd);
    static void errorUnknownMode(const std::string& c, int fd);
    static void errorErroneUsNickName(const std::string& nick, int fd);
    static void errorBadChannelKey(const std::string& nick, int fd);
    static void errorChanOprivsNeed(const std::string& nick, const std::string& chanelName, int fd);
    static void errorNoSuchNick(const std::string& nick, const std::string& targetNick, int fd);
    static void errorUserNotInChannel(const std::string& nick, const std::string& chanel, int fd);
    static void errorInviteOnlyChan(const std::string& nick, const std::string& chanelName, int fd);
    static void errorNotOnChannel(const std::string& nick, const std::string chanelName, int fd);
    static void errorUserOnChannel(const std::string& user, const std::string& chanelName, int fd);

};