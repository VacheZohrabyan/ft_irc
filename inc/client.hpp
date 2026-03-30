#pragma once

#include "ft_irc.hpp"

// class Server;

class Client
{
private:
    bool _isRegistered;
    bool _sendMessageOne;
    int _fd;

    std::string _serverPass;
    
    std::string _pass;
    std::string _nick;
    std::string _realName;
    std::string _serverName;
    std::string _hostName;
    std::string _userName;

public:
    std::string message;

public:
    Client();
    Client(int fd, const std::string& serverPass);

public:
    void hendleMessage(const std::set<std::string>& nickName, std::string& message);
    void messageToClient(std::string& message);

private:
    void findCapLs(std::string& message);
    void findPass(std::string& message);
    void findNick(std::string& message);
    void findUser(std::string& message);
    void sendMessage(std::string message);

public:
    std::string getNick() const;
    void setNick(const std::string& nick);
    std::string getUser() const;
    bool isRegistered() const;
};