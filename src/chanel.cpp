#include "../inc/chanel.hpp"

Chanel::Chanel()
{

}

Chanel::Chanel(const std::string& name, int fd, const std::string& key)
{
    _name = name;
    _key = key;
    _rootFd = fd;
}

void Chanel::addClient(int fd)
{
    _clients.insert(fd);
}

void Chanel::removeClient(int fd)
{
    _clients.erase(fd);
}

bool Chanel::hasClient(int fd) const
{
    if (_clients.find(fd) != _clients.end())
        return true;
    return false;
}

void Chanel::broadCast(const std::string& message, int openClose)
{
    for (std::set<int>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        std::cout << "broadCast = " << message;
        if (*it != openClose)
            send(*it, message.c_str(), message.length(), 0);
    }
}

std::set<int> Chanel::getClient() const
{
    return _clients;
}