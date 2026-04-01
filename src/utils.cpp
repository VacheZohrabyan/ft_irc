#include "../inc/utils.hpp"

std::vector<std::string> Utils::mySplit(const std::string& message, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(message);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Utils::sendMessage(int fd, const std::string& message)
{
    send(fd, message.c_str(), message.length(), 0);
}

void Utils::errorMoreParams(const std::string& nick, int fd)
{
    std::string tmpMsg = ":localhost 461 " + (nick.empty() ? "*" : nick) + "PASS" + std::string(ERR_NEEDMOREPARAMS);
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorAlreadyRegister(const std::string& nick, int fd)
{
    std::string tmpMsg =  ":localhost 462 " + (nick.empty() ? "*" : nick) + ERR_ALREADYREGISTRED;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorNickNameInUse(const std::string& nick, int fd)
{
    std::string tmpMsg = ":localhost 433 " + nick + ERR_NICKNAMEINUSE;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorChanelIsFull(const std::string& chanelName, int fd)
{
    std::string tmpMsg = chanelName + ERR_CHANNELISFULL;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}