#include "../inc/server.hpp"
#include "../inc/utils.hpp"

Server::Server()
{
}

Server::Server(char** argv) : _socketFd(-1), _epollFD(-1)
{
    hendlePort(argv[1]);
    hendlePass(argv[2]);
    //register
    _registerCommand["CAP"] = new CapCommand();
    _registerCommand["PASS"] = new PassCommand();
    _registerCommand["NICK"] = new NickCommand();
    _registerCommand["USER"] = new UserCommand();
    _registerCommand["PING"] = new PingCommand();
    _registerCommand["QUIT"] = new QuitRegisterCommand();
    // channel
    _channelCommand["JOIN"] = new JoinCommand();
    _channelCommand["QUIT"] = new QuitChannelCommand();
    _channelCommand["PART"] = new PartCommand();
    // _channelCommand["TOPIC"] = new TopicCommand();
    _channelCommand["NAMES"] = new NamesCommand();
    _channelCommand["LIST"] = new ListCommand();
    // _channelCommand["INVITE"] = new InviteCommand();
    // _channelCommand["KICK"] = new KickCommand();
    // Messageing;
    _messageCommand["PRIVMSG"] = new PrivMsgCommand();
    _messageCommand["NOTICE"] = new NoticeCommand();
    _messageCommand["QUIT"] = new QuitMessageCommand();
    // Administration
    _administrativeCommand["MODE"] = new ModeCommand();
    // _administrativeCommand["WHO"] = new WhoCommand();
    // _administrativeCommand["WHOIS"] = new WhoisCommand();
    // _administrativeCommand["OPER"] = new OperCommand();
    // _administrativeCommand["KILL"] = new KillCommand();
}

Server::Server(const Server& other)
{
    *this = other;
}

Server& Server::operator=(const Server& other)
{
    if (this != &other)
        *this = other;
    return *this;
}

Server::~Server()
{
    for (std::map<std::string, ARegisterCommand*>::iterator it = _registerCommand.begin(); it != _registerCommand.end(); ++it)
        delete it->second;
    _registerCommand.clear();
    for (std::map<std::string, AChannelCommand*>::iterator it = _channelCommand.begin(); it != _channelCommand.end(); ++it)
        delete it->second;
    _channelCommand.clear();
    for (std::map<std::string, AMessageCommand*>::iterator it = _messageCommand.begin(); it != _messageCommand.end(); ++it)
        delete it->second;
    _messageCommand.clear();
    for (std::map<std::string, AAdministrationCommand*>::iterator it = _administrativeCommand.begin(); it != _administrativeCommand.end(); ++it)
        delete it->second;
    _administrativeCommand.clear();
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        close(it->first);
    for (int i = 0; i < _eventCount; ++i)
        epoll_ctl(_epollFD, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
    close(_event.data.fd);
    close(_socketFd);
}

void Server::hendlePort(const std::string& port)
{
    if (port.empty())
        throw std::runtime_error("Port is empty");
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

void Server::hendlePass(const std::string& pass)
{
    if (pass.empty())
        throw std::invalid_argument("pass is empty");
    if (pass.find("\n") != std::string::npos)
        throw std::invalid_argument("pass there is new line");
    if (pass.find("\r") != std::string::npos)
        throw std::invalid_argument("pass there is carriage return");
    _pass = pass;
}

int Server::setNonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "fcntl(F_GETFL)" << std::endl;
        return -1;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "fcntl(F_SETFL)" << std::endl;
        return -1;
    }
    return 0;
}

bool Server::isRegistered(Client& client, int fd)
{
    if (client.getNick().empty() || client.getUser().empty() || client.getPass().empty())
        return false;
    else if (!client.getNick().empty() && !client.getUser().empty() && !client.getPass().empty() && !client.getIsRegistered())
    {
        Utils::sendMessage(fd, ":localhost 001 " + client.getNick() + " :Welcome to IRC\r\n");
        Utils::sendMessage(fd, ":localhost 002 " + client.getNick() + " :Your host is localhost\r\n");
        Utils::sendMessage(fd, ":localhost 003 " + client.getNick() + " :This server was created today\r\n");
        Utils::sendMessage(fd, ":localhost 004 " + client.getNick() + " localhost 1.0 o o\r\n");
    }
    return true;
}

void Server::executeCommand(int fd, const std::string& message)
{
    std::vector<std::string> tmp = Utils::mySplit(message, ' ');
    if (tmp.empty())
        return ;
    for (std::string::size_type i = 0; i < tmp[0].length(); ++i)
        tmp[0][i] = std::toupper(tmp[0][i]);
    if (_messageCommand.find(tmp[0]) != _messageCommand.end())
        _messageCommand[tmp[0]]->executeCommand(_clients[fd], _clients, _chanels[tmp[1]], fd, tmp);
    if (_channelCommand.find(tmp[0]) != _channelCommand.end())
        _channelCommand[tmp[0]]->executeCommand(_clients[fd], _chanels, fd, tmp);        
    if (_registerCommand.find(tmp[0]) != _registerCommand.end())
        _registerCommand[tmp[0]]->executeCommand(_clients[fd], _nickName, fd, tmp);
}

void Server::runServer()
{
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(1);
    }
    setNonblocking(_socketFd);
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
        
    _epollFD = epoll_create1(0);
    if (_epollFD == -1)
        throw std::runtime_error("epoll_create1 failed");
    
    _event.events = EPOLLIN;
    _event.data.fd = _socketFd;

    if (epoll_ctl(_epollFD, EPOLL_CTL_ADD, _socketFd, &_event) == -1)
        throw std::runtime_error("epoll_ctl failed");

    while (server_runing)
    {
        _eventCount = epoll_wait(_epollFD, _events, MAX_EVENTS, -1);
        if (_eventCount == -1)
            return ;
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
                setNonblocking(clientFd);
                struct epoll_event ev;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = clientFd;
                
                _clients[clientFd] = Client(clientFd, _pass);
                if (epoll_ctl(_epollFD, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
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
                            std::cout << "command = " << tmp << std::endl;
                            executeCommand(_events[i].data.fd, tmp);
                            _clients[_events[i].data.fd].message.erase(0, pos + 2);
                        }
                        if (isRegistered(_clients[_events[i].data.fd], _events[i].data.fd) && !_clients[_events[i].data.fd].getIsRegistered())
                            _clients[_events[i].data.fd].setIsRegistered(true);
                    }
                    catch(const std::exception& e)
                    {
                        _clients[_events[i].data.fd].message.clear();
                        epoll_ctl(_epollFD, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                        close(_events[i].data.fd);
                    }
                }
                if (count == 0)
                {
                    std::cerr << "Client " << _events[i].data.fd << " disconnect" << std::endl;
                    if (_nickName.find(_clients[_events[i].data.fd].getNick()) != _nickName.end())
                        _nickName.erase(_clients[_events[i].data.fd].getNick());
                    if (_clients.find(_events[i].data.fd) != _clients.end())
                        _clients.erase(_events[i].data.fd);
                    epoll_ctl(_epollFD, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                    close(_events[i].data.fd);
                    break;
                }
                if (count == -1)
                {
                    if (errno != EAGAIN)
                    {
                        if (_nickName.find(_clients[_events[i].data.fd].getNick()) != _nickName.end())
                            _nickName.erase(_clients[_events[i].data.fd].getNick());
                        if (_clients.find(_events[i].data.fd) != _clients.end())
                            _clients.erase(_events[i].data.fd);
                        epoll_ctl(_epollFD, EPOLL_CTL_DEL, _events[i].data.fd, NULL);
                        close(_events[i].data.fd);
                    }
                }
            }
        }
    }
}
