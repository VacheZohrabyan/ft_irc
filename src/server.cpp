#include "../inc/server.hpp"

Server::Server(const std::string& port, const std::string& pass)
{
    checkPort(port);
    checkPass(pass);
    runServer();
}

void Server::checkPort(const std::string& port)
{
    for (std::string::size_type i = 0; i < port.size(); ++i)
    {
        if (!std::isdigit(port[i]))
            throw std::invalid_argument("Invalid port(non digit)");
    }
    int value = std::stoi(port);
    if (value < 0 || value > 65535)
        throw std::out_of_range("Invalid port(rang)");
    if (value >= 0 && value <= 1023)
        throw std::out_of_range("The port is busy.");
    _port = port;
}

void Server::checkPass(const std::string& pass)
{
    if (pass.empty())
        throw std::invalid_argument("pass is empty");
    if (pass.find("\n") != std::string::npos)
        throw std::invalid_argument("pass there is new line");
    if (pass.find("\r") != std::string::npos)
        throw std::invalid_argument("pass there is carriage return");
    if (pass.find(" ") != std::string::npos)
        throw std::invalid_argument("pass there is a space");
    _pass = pass;
}

// void Server::addClient(int clientFd)
// {
//     Client client(clientFd);
//     _clients[clientFd] = client;
// }

int Server::set_nonblocking(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "fcntl(F_GETFL)" << std::endl;
        return -1;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "fcntl(F_SETFL)" << std::endl;
        return -1;
    }
    return 0;
}

void Server::sendMessage(const std::string& message, int fd)
{
    send(fd, message.c_str(), message.length(), 0);
}

// void Server::hendleException(const std::exception& e, int fd)
// {
//     // if (!std::strcmp(e.what(), ERR_NEEDMOREPARAMS))
//     //     sendMessage(e.what(), fd);
//     // if (!std::strcmp(e.what(), ERR_ALREADYREGISTRED))
//     //     sendMessage()
// }

// void Server::findNickAndRemove(const std::string& nick)
// {
//     // std::vector<std::string>::const_iterator it = _nickName.begin();
//     // while (it != _nickName.end())
//     // {
//     //     if (*it == nick)
//     //     {
//     //         _nickName.erase(it);
//     //         std::cout << "stex = " << *it << std::endl;
//     //         return ;
//     //     }
//     //     ++it;
//     // }
//     // return ;
// }

std::vector<std::string> Server::mySplit(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Server::handleJoin(std::string& chanelName, const std::string& pass, int fd)
{
    if (chanelName[0] == '#')
    {
        chanelName = chanelName.erase(0, 1);
        if (pass.empty())
        {

            std::cout << "handleJoin" << fd << std::endl;
            if (_chanels.find(chanelName) == _chanels.end())
                _chanels[chanelName] = Chanel(chanelName, fd, pass);
            if (_chanels.find(chanelName) != _chanels.end() && !_chanels[chanelName].hasClient(fd))
                _chanels[chanelName].addClient(fd);
            else
            {
                //sendMessage(vor client ka);
                // throw;
            }
            std::string joinMessage = ":" + _clients[fd].getNick() + " JOIN :" + chanelName + "\r\n";
            _chanels[chanelName].broadCast(joinMessage, -1);
        }
    }
    else if (chanelName[0] == '&')
    {
        // esel verevi nman
    }
}

void Server::handleMessageToChanel(std::string& message, int fd)
{
    std::cout << "message = " << message << std::endl;
    if (message.substr(0, 4) == "PING")
    {
        std::string response = (message.length() > 5) ? message.substr(5) : "localhost";
        if (!response.empty() && response[0] == ':')
            response.erase(0, 1);
        
        std::string pong = "PONG :" + response + "\r\n";
        send(fd, pong.c_str(), pong.length(), 0);
    }
    if (message.substr(0, 4) == "JOIN")
    {
        std::string tmp = message.substr(5);
        std::string::size_type first = tmp.find_first_not_of(' ');
        if (first != std::string::npos)
            tmp = tmp.substr(first);
        first = tmp.find(' ');
        if (first == std::string::npos)
        {
            std::cout << "stex = " << tmp << std::endl;
            handleJoin(tmp, "", fd);
        }
        else
        {
            std::string chanelName = tmp.substr(0, first);
            std::string pass = tmp.substr(first + 1);
            handleJoin(chanelName, pass, fd);
        }
    }
    else if (message.substr(0, 7) == "PRIVMSG")
    {
        std::string tmp = message.substr(8);
        if (tmp.find(" ") == std::string::npos)
            return;
        std::string chanelName = tmp.substr(0, tmp.find(" "));
        tmp = tmp.substr(tmp.find(" "));
        std::string privateMessage = tmp.substr(tmp.find(" :") + 1);
        std::string fullIRCMessage = ":" + _clients[fd].getNick() + "!" + _clients[fd].getUser() + "@localhost PRIVMSG #" + chanelName + " " + privateMessage + "\r\n";
        if (_chanels.find(chanelName) != _chanels.end())
            _chanels[chanelName].broadCast(fullIRCMessage, fd); 
        
    }
}    

void Server::runServer()
{
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);

    set_nonblocking(_socketFd);
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(std::stoi(_port));
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    std::memset(_serverAddr.sin_zero, 0x0, sizeof(_serverAddr.sin_zero));

    int bindStatus = bind(_socketFd, (const sockaddr*)&_serverAddr, (socklen_t)sizeof(_serverAddr));
    if (bindStatus == -1)
        throw std::runtime_error("bind failed");
    int listenStatus = listen(_socketFd, SOMAXCONN);
    if (listenStatus == -1)
        throw std::runtime_error("listen failed"); 
        
    int epollFd = epoll_create1(0);
    if (epollFd == -1)
        throw std::runtime_error("epoll_create1 failed");
    
    _event.events = EPOLLIN;
    _event.data.fd = _socketFd;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, _socketFd, &_event) == -1)
        throw std::runtime_error("epoll_ctl failed");

    while (true)
    {
        _eventCount = epoll_wait(epollFd, _events, MAX_EVENTS, -1);
        if (_eventCount == -1)
            throw std::runtime_error("epoll_wait failed");
        for (int i = 0; i < _eventCount; ++i)
        {
            if (_events[i].data.fd == _socketFd)
            {
                struct sockaddr_in clinetAddr;
                socklen_t len = sizeof(clinetAddr);
                int clientFd = accept(_socketFd, (struct sockaddr*)&clinetAddr, &len);
                if (clientFd == -1)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        break;
                    else
                    {
                        std::cerr << "accept failed" << std::endl;
                        break;
                    }
                }
                set_nonblocking(clientFd);
                struct epoll_event ev;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = clientFd;
                
                _clients[clientFd] = Client(clientFd, _pass);
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
                {
                    std::cerr << "epoll_ctl failed, (clinet_fd)" << std::endl;
                    close(ev.data.fd);
                }
            }
            else
            {
                char buffer[512];
                std::memset(buffer, 0x0, 512);
                ssize_t count;
                while ((count = recv(_events[i].data.fd, buffer, 512, 0)) > 0)
                {
                    _clients[_events[i].data.fd].message.append(buffer, count);
                    std::memset(buffer, 0x0, 512);
                    try
                    {
                        std::string::size_type pos;
                        while ((pos = _clients[_events[i].data.fd].message.find("\r\n")) != std::string::npos)
                        {
                            std::string tmp = _clients[_events[i].data.fd].message.substr(0, pos);
                            if (!_clients[_events[i].data.fd].isRegistered())
                            {
                                _clients[_events[i].data.fd].hendleMessage(_nickName, tmp);
                                _clients[_events[i].data.fd].message.erase(0, pos + 2);
                                tmp.clear();                        
                            }
                            else if (_clients[_events[i].data.fd].isRegistered())
                            {
                                handleMessageToChanel(tmp, _events[i].data.fd);
                                _clients[_events[i].data.fd].message.erase(0, pos + 2);
                                tmp.clear();                        
                            }
                        }
                        if (_clients[_events[i].data.fd].isRegistered())
                            _nickName.insert(_clients[_events[i].data.fd].getNick());
                    }
                    catch(const std::exception&)
                    {
                        epoll_ctl(epollFd, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                        close(_events[i].data.fd);
                    }
                }
                if (count == 0)
                {
                    std::cerr << "Client " << _events[i].data.fd << " disconnect" << std::endl;
                    _nickName.erase(_clients[_events[i].data.fd].getNick());
                    _clients.erase(_events[i].data.fd);
                    epoll_ctl(epollFd, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                    close(_events[i].data.fd);
                    break;
                }
                if (count == -1)
                {
                    if (errno != EAGAIN)
                    {
                        epoll_ctl(epollFd, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                        close(_events[i].data.fd);
                    }
                }
            }
        }
    }
}