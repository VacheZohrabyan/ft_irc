#pragma once

#include "include.hpp"
#include "client.hpp"

#include "administration/modeCommand.hpp"

#include "register/capCommand.hpp"
#include "register/passCommand.hpp"
#include "register/nickCommand.hpp"
#include "register/userCommand.hpp"
#include "register/pingCommand.hpp"
#include "register/quitCommand.hpp"

#include "channel/partCommand.hpp"
#include "channel/joinCommand.hpp"
#include "channel/quitCommand.hpp"
#include "channel/namesCommand.hpp"
#include "channel/listCommand.hpp"

#include "message/privmsgCommand.hpp"
#include "message/noticeCommand.hpp"
#include "message/quitCommand.hpp"

extern bool server_runing;

class Server
{
private:
    std::string _port;
    std::string _pass;

private:
    int _socketFd;
    int _eventCount;
    int _epollFD;
    struct epoll_event _event;
    struct epoll_event _events[MAX_EVENTS];
    struct sockaddr_in _serverAddr;
    std::map<std::string, AAdministrationCommand*> _administrativeCommand;
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
    int setNonblocking(int fd);
    
    private:
    bool isRegistered(Client& client, int fd);
    
    
public:
    void runServer();
};