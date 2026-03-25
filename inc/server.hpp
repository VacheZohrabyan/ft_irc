#pragma once

#include "../inc/ft_irc.hpp"

class Server
{
private:
    std::string _port;
    std::string _pass;
    int _socketFd;
    struct sockaddr_in _serverAddr;
    struct epoll_event _event;
    struct epoll_event _events[MAX_EVENTS];
    std::map<int, Client> _clients;

public:
    Server(const std::string& port,const std::string& pass);

private:
    void checkPort(const std::string& port);
    void checkPass(const std::string& pass);
    int set_nonblocking(int sockfd);
    void addClient(int clientFd);
    void runServer();
};