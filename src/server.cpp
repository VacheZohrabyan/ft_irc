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
    std::cout << "sendMessage = " << message;
    send(fd, message.c_str(), message.length(), 0);
}

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

void Server::handleMessageToChanel(std::string& mes, int fd)
{
    std::cout << "message = " << mes << std::endl;
    std::vector<std::string> message = mySplit(mes, ' ');
    std::cout << "message.size = " << message.size() << std::endl;

    if (message[0] == "PING")
    {
        std::string pong = "PONG :" + message[1] + "\r\n";
        send(fd, pong.c_str(), pong.length(), 0);
    }
    else if (message[0] == "NICK")
    {
        if (message.size() == 1)
            return sendMessage("431 NICK " + std::string(ERR_NONICKNAMEGIVEN), fd);
        if (_nickName.find(message[1]) != _nickName.end())
            return sendMessage("433 " + message[1] + ERR_NICKNAMEINUSE, fd);
        std::string oldNick = _clients[fd].getNick();
        _clients[fd].setNick(message[1]);
        // vor chanel mech ka message uxarkel
        std::string nickMsg = ":" + oldNick + "!" + _clients[fd].getUser() + "@localhost NICK :" + _clients[fd].getNick() + "\r\n";
        for (std::map<std::string, Chanel>::const_iterator chanel = _chanels.begin(); chanel != _chanels.end(); ++chanel)
        {
            std::set<int> client = chanel->second.getClient();
            if (client.find(fd) != client.end())
                _chanels[chanel->first].broadCast(nickMsg, -1);
        }
    }
    else if (message[0] == "JOIN")
    {
        if (message.size() < 2)
            return sendMessage(":localhost 461 " + _clients[fd].getNick() + " JOIN" + std::string(ERR_NEEDMOREPARAMS), fd);
        handleJoin(message[1], (message.size() == 2) ? "" : message[2], fd);
    }
    else if (message[0] == "PRIVMSG")
    {
        if (message.size() < 3)
            return ;
        if (_chanels.find(message[1]) != _chanels.end())
            _chanels[message[1]].broadCast(":" + _clients[fd].getNick() + "!" + _clients[fd].getUser() + "@localhost PRIVMSG #" + message[1] + " " + message[2] + "\r\n", fd);
        else
            return;
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
                            std::cout << "ClientMessage = " << _clients[_events[i].data.fd].message << std::endl;
                            std::string tmp = _clients[_events[i].data.fd].message.substr(0, pos);
                            if (!_clients[_events[i].data.fd].isRegistered())
                                _clients[_events[i].data.fd].hendleMessage(_nickName, tmp);                       
                            else if (_clients[_events[i].data.fd].isRegistered())
                                handleMessageToChanel(tmp, _events[i].data.fd);
                            _clients[_events[i].data.fd].message.erase(0, pos + 2);
                            tmp.clear(); 
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