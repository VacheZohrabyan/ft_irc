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
    std::string tmpMsg = ":localhost 433 * " + nick + ERR_NICKNAMEINUSE;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorChanelIsFull(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 471 " + chanelName + ERR_CHANNELISFULL;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorBadChanMask(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 475 " + chanelName + ERR_BADCHANMASK;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorNoSuchNick(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 401 " + chanelName + ERR_NOSUCHCHANNEL;
    Utils::sendMessage(fd, tmpMsg);
    // throw std::runtime_error("");
}

void Utils::errorNoSuchChannel(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 403 " + chanelName + ERR_NOSUCHCHANNEL;
    Utils::sendMessage(fd, tmpMsg);
    // throw std::runtime_error("");
}

void Utils::errorTooManyChannels(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 405 " + chanelName + ERR_TOOMANYCHANNELS;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorChannelIsFull(const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 471 " + chanelName + ERR_CHANNELISFULL;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorNoTestToSend(int fd)
{
    std::string tmpMsg = ERR_NOTEXTTOSEND;
    Utils::sendMessage(fd, tmpMsg);
    throw std::runtime_error("");
}

void Utils::errorNotOnChannel(const std::string& name, int fd)
{
    std::string tmpMsg = ":localhost 442 " + name + " " + ERR_NOTONCHANNEL + "\r\n";
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorUnknownMode(const std::string& c, int fd)
{
    std::string tmpMsg = ":localhost 472 " + c + " :is unknown mode char to me\r\n";
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorErroneUsNickName(const std::string& nick, int fd)
{
    std::string tmpMsg = ":localhost 432 " + nick + ERR_ERRONEUSNICKNAME;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorBadChannelKey(const std::string& nick, int fd)
{
    std::string tmpMsg = ":localhost 475 " + nick + ERR_BADCHANNELKEY;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorChanOprivsNeed(const std::string& nick,const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 482 " + nick + " " +chanelName + ERR_CHANOPRIVSNEEDED;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorNoSuchNick(const std::string& nick, const std::string& targetNick, int fd)
{
    std::string tmpMsg = ":localhost 401 " + nick + " " + targetNick + ERR_NOSUCHNICK;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorUserNotInChannel(const std::string& nick, const std::string& chanel, int fd)
{
    std::string tmpMsg = ":localhost 441 " + nick + " " + chanel + " " + ERR_USERNOTINCHANNEL;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorInviteOnlyChan(const std::string& nick, const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 473 " + nick + " " + chanelName + ERR_INVITEONLYCHAN;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorNotOnChannel(const std::string& nick, const std::string chanelName, int fd)
{
    std::string tmpMsg = ":localhost 442 " + nick + chanelName + ERR_NOTONCHANNEL;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorUserOnChannel(const std::string& user, const std::string& chanelName, int fd)
{
    std::string tmpMsg = ":localhost 443 " + user + " " + chanelName + ERR_USERONCHANNEL;
    Utils::sendMessage(fd, tmpMsg);
}

void Utils::errorNoNickNameGiven(int fd)
{
    std::string tmpMsg = ":localhost 431" + std::string(ERR_NONICKNAMEGIVEN);
    Utils::sendMessage(fd, tmpMsg);
}