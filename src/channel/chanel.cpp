#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

Chanel::Chanel()
{

}

Chanel::~Chanel()
{

}

Chanel& Chanel::operator=(const Chanel& other)
{
    if (this != &other)
        *this = other;
    return *this;
}

Chanel::Chanel(const std::string& name, int fd, const std::string& key)
{
    _chanelName = name;
    _chanelRootFd = fd;
    _chanelkey = key;
}

void Chanel::addClient(int fd, const std::string& nick)
{
    if (_clients.find(fd) != _clients.end())
        return;
    if (_clients.size() == MAX_CLIENT)
        Utils::errorChanelIsFull(_chanelName, fd);
    _clients[fd] = nick;
}

void Chanel::showAll(int fd, const Client& client)
{
    std::string tmpMessage = ":localhost 353 " + client.getNick() + " = " + _chanelName + " :";
    for (std::map<int, std::string>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it != _clients.begin())
            tmpMessage += " ";
        if (it->first == _chanelRootFd)
            tmpMessage += "@";

        tmpMessage += it->second;
    }
    tmpMessage += "\r\n";
    Utils::sendMessage(fd, tmpMessage);
}

void Chanel::broadCast(const std::string& message, int all)
{
    for (std::map<int, std::string>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->first == all)
            continue;
        Utils::sendMessage(it->first, message);
    }
}

bool Chanel::hasClient(int fd)
{
    if (_clients.find(fd) != _clients.end())
        return true;
    return false;
}

int Chanel::getCountClient() const
{
    return _clients.size();
}

std::string Chanel::getTopic() const
{
    return _chanelTopic;
}

void Chanel::setTopic(const std::string& topic)
{
    _chanelTopic = topic;
}