#pragma once

#include "include.hpp"
#include "utils.hpp"

#define MAX_CLIENT 15

class Client;

class Chanel
{
public:
    Chanel();
    Chanel(const std::string& name, int fd, const std::string& chanelKey);
    ~Chanel();

private:
    std::string _chanelName;
    std::string _chanelkey;
    int _chanelRootFd;
    std::set<int> _clients;

public:
    void addChanel(int fd);
    void removeChanel(int fd);
    bool hasClient(int fd);

    void broadCast(const std::string& message, int all);
};