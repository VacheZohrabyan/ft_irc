#pragma once

#include "../inc/ft_irc.hpp"

class Client;
class Chanel;

class Server
{
private:
    std::string _port;
    std::string _pass;
    int _socketFd;
    int _eventCount;
    struct sockaddr_in _serverAddr;
    struct epoll_event _event;
    struct epoll_event _events[MAX_EVENTS];
    std::map<int, Client> _clients;

    std::set<std::string> _nickName;

    std::map<std::string, Chanel> _chanels;

public:
    Server(const std::string& port,const std::string& pass);

private:
    std::vector<std::string> mySplit(const std::string& message, char delimiter);

private:
    void checkPort(const std::string& port);
    void checkPass(const std::string& pass);
    int set_nonblocking(int sockfd);
    void sendMessage(const std::string& message, int fd);
    void handleMessageToChanel(std::string& message, int fd);
    void handleJoin(std::string &argument, const std::string& pass, int fd);
    
    void runServer();
};