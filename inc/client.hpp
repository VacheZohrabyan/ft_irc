#pragma once

#include "include.hpp"
#include "ARegisterCommand.hpp"

class Client
{
private:
    bool _isRegistered;
    int _fd;
    std::string _pass;
    std::string _nick;
    std::string _user;
    std::string _host;
    std::string _server;
    std::string _real;
    std::string _serverPass;

    
public:
    std::string message;

public:
    Client();
    Client(int fd, const std::string& serverPass);

public:
    void setPass(const std::string& newPass);
    void setNick(const std::string& newNick);
    void setUser(const std::string& newUser);
    void setHost(const std::string& newHost);
    void setServer(const std::string& newServer);
    void setReal(const std::string& newReal);
    bool getIsRegistered() const;
    void setIsRegistered(bool is);
    std::string getPass() const;
    std::string getServerPass() const;
    std::string getNick() const;
    std::string getUser() const;
    std::string getHost() const;
    std::string getServer() const;
    std::string getReal() const;
};