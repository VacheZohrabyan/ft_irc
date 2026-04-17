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
    _chanelRootFd.insert(fd);
    _chanelkey = key;
    _createTime = std::time(NULL);
    _inviteOnly = false;
    if (key.empty())
        _chanelPasswd = false;
    else
        _chanelPasswd = true;
    _limit = false;
    _inviteOnly = false;
    _maxCountUser = 10;
}

void Chanel::addInvite(int fd, const std::string& nick)
{
    _invites[fd] = nick;
}

void Chanel::addClient(int fd, const std::string& nick)
{
    if (_clients.find(fd) != _clients.end())
        return;
    if (_clients.size() == _maxCountUser)
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
        if (_chanelRootFd.find(it->first) != _chanelRootFd.end())
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

bool Chanel::hasClient(const std::string& nick) const
{
    for (std::map<int, std::string>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second == nick)
            return true;
    }
    return false;
}

std::size_t Chanel::getCountClient() const
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

void Chanel::removeChanel(int fd)
{
    _clients.erase(fd);
    if (_chanelRootFd.find(fd) != _chanelRootFd.end())
    {
        _chanelRootFd.erase(fd);
        if (_chanelRootFd.size() == 0)
            _chanelRootFd.insert(_clients.begin()->first);
    }
}

void Chanel::removeClient(int fd)
{
    if (_chanelRootFd.find(fd) != _chanelRootFd.end())
        _chanelRootFd.erase(fd);
    
    if (_clients.find(fd) != _clients.end())
        _clients.erase(fd);
}

void Chanel::setMaxCount(std::size_t count)
{
    _maxCountUser = count;
}

std::size_t Chanel::getMaxCount() const
{
    return _maxCountUser;
}

const std::set<int>& Chanel::getRootFd() const
{
    return _chanelRootFd;
}

const std::time_t& Chanel::getTime() const
{
    return _createTime;
}

const std::string& Chanel::getChanelName() const
{
    return _chanelName;
}

const std::string& Chanel::getChannelPass() const
{
    return _chanelkey;
}

void Chanel::setChanelKey(const std::string& key)
{
    _chanelkey = key;
}

void Chanel::removeRootFd(int fd)
{
    if (_chanelRootFd.size() == 0)
        return;
    _chanelRootFd.erase(fd);
}

void Chanel::removeInviteList(int fd)
{
    if (_invites.find(fd) != _invites.end())
        _invites.erase(fd);
}

const std::map<int, std::string>& Chanel::getInviteList() const
{
    return _invites;
}

const std::map<int, std::string>& Chanel::getChanelClients() const
{
    return _clients;
}

bool Chanel::getLimit() const
{
    return _limit;
}

void Chanel::setLimit(bool limit)
{
    _limit = limit;
}

bool Chanel::getInviteOnly() const
{
    return _inviteOnly;
}

void Chanel::setInviteOnly(bool inviteOnly)
{
    _inviteOnly = inviteOnly;
}

bool Chanel::getTopicProtection() const
{
    return _topicProtection;
}

void Chanel::setTopicProtection(bool topicprotection)
{
    _topicProtection = topicprotection;
}

bool Chanel::getChanelPasswd() const
{
    return _chanelPasswd;
}

void Chanel::setChanelPasswd(bool chanelPasswd)
{
    _chanelPasswd = chanelPasswd;
}

bool Chanel::getOperatorPrivilege(int fd) const
{
    if (_chanelRootFd.find(fd) != _chanelRootFd.end())
        return true;
    return false;
}

void Chanel::setOperatorPrivilege(int fd)
{
    _chanelRootFd.insert(fd);
}
