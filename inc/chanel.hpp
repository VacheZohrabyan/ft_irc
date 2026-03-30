#pragma once

#include "ft_irc.hpp"

class Chanel
{
private:
    std::string _name;
    std::string _key;
    int _rootFd;
    std::set<int> _clients;

public:
    void addClient(int fd);
    void removeClient(int fd);

    bool hasClient(int fd) const;

    void broadCast(const std::string& message, int openClose);

public:
    Chanel();
    Chanel(const std::string& name, int fd, const std::string& key);

public:
    std::set<int> getClient() const;
};