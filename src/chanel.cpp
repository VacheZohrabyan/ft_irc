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

}