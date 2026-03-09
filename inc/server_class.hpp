#pragma once

#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <arpa/inet.h>
#include "client_class.hpp"
#include "parsing.hpp"
#include <string>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <sys/epoll.h>

class Server
{
public:
    Server();
    // Server(const Server& other);
    // Server& operator=(const Server& other);
    // ~Server();

public:
    void init(Parsing& obj);
    void set_nonblocking(int fd);
    void setPass(const std::string& pass);
    const std::string& getPass() const;
    
private:
    void startServer();

private:
    int _serverSockedFd;
    std::string _pass;
    std::string _port;
    std::map<int, Client> _client;
};

void	*ft_memset(void *s, int c, size_t n);