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
        int eventCount = epoll_wait(epollFd, _events, MAX_EVENTS, -1);
        if (eventCount == -1)
            throw std::runtime_error("epoll_wait failed");
        for (int i = 0; i < eventCount; ++i)
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
                std::string message;
                while ((count = recv(_events[i].data.fd, buffer, 512, 0)) > 0)
                {
                    message.append(buffer, count);
                    std::memset(buffer, 0x0, 512);
                    try
                    {
                        while (message.find("\r\n") != std::string::npos)
                        {
                            std::string tmp = message.substr(0, message.find("\r\n"));
                            std::cout << tmp << std::endl;
                            _clients[_events[i].data.fd].hendleMessage(_nickName, tmp);
                            message.erase(0, tmp.length() + 2);
                        }
                    }
                    catch(const std::exception&)
                    {
                        std::cout << "exception" << std::endl;
                        // hendleException(e, _events[i].data.fd);
                        count = 0;
                        break;
                    }
                    _nickName.push_back(_clients[_events[i].data.fd].getNick());
                }
                if (count > 0)
                {
                    
                }
                if (count == 0)
                { //stex avelacnel discconect linoxi vector i mechi hanely;
                    std::cerr << "Client " << _events[i].data.fd << " dicconect" << std::endl;
                    epoll_ctl(epollFd, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                    close(_events[i].data.fd);
                    break;
                }
                if (count == -1)
                {
                    if (errno != EAGAIN)
                    {
                        std::cerr << "read failed" << std::endl;
                        epoll_ctl(epollFd, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                        close(_events[i].data.fd);
                    }
                }
            }
        }
    }
}