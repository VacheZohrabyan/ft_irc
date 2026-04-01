#include "../inc/chanel.hpp"

Chanel::Chanel()
{

}

Chanel::Chanel(const std::string& name, int fd, const std::string& key)
{
    _chanelName = name;
    _chanelRootFd = fd;
    _chanelkey = key;
}

void Chanel::addChanel(int fd)
{
    if (_clients.find(fd) != _clients.end())
        return;

    if (_clients.size() == MAX_CLIENT)
        Utils::errorChanelIsFull(_chanelName, fd);
}