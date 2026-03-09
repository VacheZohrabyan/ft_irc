#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>

class Client
{
public:
    Client();

public:
    int getFd() const;
    std::string getIpAddress() const;
    std::string getNick() const;
    std::string getUser() const;
    bool getReceived() const;
    const std::string& getPass() const;

    void setFd(int fd);
    // void setIpAddress(const std::string& ipAddress);
    void setNick(const std::string& nick);
    void setUser(const std::string& user);
    void setClient(int newSocket, std::string& message);
    void setReceived(bool received);
    void message();

private:
    std::string& _init_client_class(std::string& message);
    void _parse_array(std::string& message);
    std::string _helper(std::string& message, std::string find_key);
    void _parseUser(std::string& , std::string );
    void _parseUserNameHelper(std::string& , std::string& , std::string );
    void _messageForClient();

private:
    int _fd;
    std::string _nickName;
    std::string _hostName;
    std::string _serverName;
    std::string _userName;
    std::string _realName;
    std::string _pass;
    bool _isReceived;
};