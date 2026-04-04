#pragma once

#include "include.hpp"
#include "client.hpp"

#include "capCommand.hpp"
#include "passCommand.hpp"
#include "nickCommand.hpp"
#include "userCommand.hpp"
#include "pingCommand.hpp"

#include "joinCommand.hpp"

#include "message/privmsgCommand.hpp"

class Server
{
private:
    std::string _port;
    std::string _pass;

private:
    int _socketFd;
    int _eventCount;
    struct epoll_event _event;
    struct epoll_event _events[MAX_EVENTS];
    struct sockaddr_in _serverAddr;
    std::map<std::string, ARegisterCommand*> _registerCommand;
    std::map<std::string, AChannelCommand*> _channelCommand;
    std::map<std::string, AMessageCommand*> _messageCommand;
    std::map<std::string, Chanel> _chanels;
    std::map<int, Client> _clients;
    std::set<std::string> _nickName;

public:
    Server();
    Server(char** argv);
    Server(const Server& other);
    Server& operator=(const Server& other);
    ~Server();

private:
    void hendlePort(const std::string& port);
    void hendlePass(const std::string& pass);
    void executeCommand(int fd, const std::string& message);
private:
    int setNonblocking(int fd);

public:
    void runServer();
};