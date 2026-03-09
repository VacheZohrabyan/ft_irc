#include "../inc/server_class.hpp"

Server::Server()
{

}

void Server::setPass(const std::string& pass)
{
    _pass = pass;
}

const std::string& Server::getPass() const
{
    return _pass;
}

void Server::set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0)
        throw std::runtime_error("set_nonblocking fcntl(F_GETFL) error");
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK))
        throw std::runtime_error("set_nonblocking fcntl(F_SETFL) error");
}

void Server::init(Parsing& obj)
{
    _pass = obj.getPass();
    _port = obj.getPort();
    startServer();
}

void Server::startServer()
{
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(std::stoi(_port));
    if ((_serverSockedFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw std::runtime_error("socket error");
    }
     
    if (fcntl(_serverSockedFd, F_SETFL, O_NONBLOCK) < 0)
    {
        close(_serverSockedFd);
        throw std::runtime_error("fcntl error");
    }

    if (bind(_serverSockedFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        close(_serverSockedFd);
        throw std::runtime_error("bind error");
    }
    set_nonblocking(_serverSockedFd);

    if (listen(_serverSockedFd, 10) < 0)
    {
        close(_serverSockedFd);
        throw std::runtime_error("listen error");
    }
    int epoll_fd = epoll_create1(0); //MAX_CONNECT
    if (epoll_fd < 0)
        throw std::runtime_error("epoll_create");

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = _serverSockedFd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, _serverSockedFd, &event) == -1)
    {
        throw std::runtime_error("epoll_ctl");
    }
    struct epoll_event events[10];
    while (true)
    {
        int newSocket = 0;
        int n_events = epoll_wait(epoll_fd, events, 10, -1);
        if (n_events == -1)
            throw std::runtime_error("epoll_wait");

        for (int i = 0; i < n_events; ++i)
        {
            if (events[i].data.fd == _serverSockedFd)
            {
                while (true)
                {
                    struct sockaddr_in client_addr;
                    socklen_t len = sizeof(client_addr);
                    newSocket = accept(_serverSockedFd, (struct sockaddr*)&client_addr, (socklen_t*)&len);
                    _client[newSocket];
                    if (newSocket == -1)
                    {
                        if (errno == EAGAIN || errno == EWOULDBLOCK)
                            break;
                        else
                            throw std::runtime_error("accept");
                    }
                    set_nonblocking(newSocket);
                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = newSocket;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, newSocket, &event) == -1)
                        throw std::runtime_error("epoll_ctl(newSocket)");
                }
            }
            else
            {
                char str[512];
                int byte_len = 0;
                memset(str, 0x0, 512);
                std::string message;
                while ((byte_len = read(event.data.fd, str, 511)) > 0)
                {
                    message += str;
                    std::memset(str, 0x0, 512);
                }
                if (byte_len == 0)
                {
                    close(event.data.fd);
                }
                else if (byte_len == -1)
                {
                    if (errno == EAGAIN)
                    {
                        if (!_client[event.data.fd].getReceived() && !message.empty())
                        {
                            Client client;
                            client.setClient(event.data.fd, message);
                            _client[event.data.fd] = client;
                            _client[event.data.fd].message();
                            message.clear();
                            if (_client[event.data.fd].getPass() != this->getPass())
                            {
                                close(event.data.fd);
                                break;
                            }
                        }
                        else if (message.find("PING") == 0)
                        break;
                    }
                    else
                    {
                        close(event.data.fd);
                        break;
                    }
                }
                else
                {
                    close(event.data.fd);
                    break;
                }
                // for (std::map<int, Client>::iterator it = _client.begin(); it != _client.end(); ++it)
                // {
                //     std::string message;
                //     _client[client_fd].setClient(client_fd, message);
                //     std::cout << it->first << it->second.getNick() << std::endl;
                //     message.clear();
                // }
                // if (newSocket < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
                //     break;
                // usleep(1000);
            }
        }
        // int newSocket = 0;
        // len = sizeof(client_addr);
        // while ((newSocket = accept(serverSockedFd, (struct sockaddr*)&client_addr, (socklen_t*)&len)) >= 0)
        //     _client[newSocket] = Client();
    }
}