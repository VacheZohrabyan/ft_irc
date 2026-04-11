#include "../inc/client.hpp"

Client::Client()
{
    _isRegistered = false;
}

Client::Client(int fd, const std::string& serverPass)
{
    _fd = fd;
    _serverPass = serverPass;
    _isRegistered = false;
}

void Client::setPass(const std::string& newPass)
{
    _pass = newPass;
}

void Client::setNick(const std::string& newNick)
{
    _nick = newNick;
}

void Client::setUser(const std::string& newUser)
{
    _user = newUser;
}

void Client::setHost(const std::string& newHost)
{
    _host = newHost;
}

void Client::setServer(const std::string& newServer)
{
    _server = newServer;
}

void Client::setReal(const std::string& newReal)
{
    _real = newReal;
}

bool Client::getIsRegistered() const
{
    return _isRegistered;
}

void Client::setIsRegistered(bool is)
{
    _isRegistered = is;
}

std::string Client::getPass() const
{
    return _pass;
}

std::string Client::getServerPass() const
{
    return _serverPass;
}

std::string Client::getNick() const
{
    return _nick;
}

std::string Client::getUser() const
{
    return _user;
}

std::string Client::getHost() const
{
    return _host;
}

std::string Client::getServer() const
{
    return _server;
}

std::string Client::getReal() const
{
    return _real;
}

int Client::getFd() const
{
    return _fd;
}