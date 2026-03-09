#include "../inc/client_class.hpp"

Client::Client()
{
    _isReceived = false;
}

int Client::getFd() const
{
    return _fd;
}

std::string Client::getNick() const
{
    return _nickName;
}

std::string Client::getUser() const
{
    return _userName;
}

bool Client::getReceived() const
{
    return _isReceived;
}

void Client::setFd(int fd)
{
    this->_fd = fd;
}

void Client::setNick(const std::string& nick)
{
    this->_nickName = nick;
}

void Client::setUser(const std::string& user)
{
    this->_userName = user;
}

void Client::setReceived(bool isReceived)
{
    _isReceived = isReceived;
}

void Client::setClient(int newSocket, std::string& message)
{
    _parse_array(_init_client_class(message));
    _fd = newSocket;
}

const std::string& Client::getPass() const
{
    return _pass;
}

void Client::message()
{
    _messageForClient();
}

std::string& Client::_init_client_class(std::string& message)
{
    std::string::size_type pos = 0;
    std::string::size_type start_pos = 0;
    while ((pos = message.find("\r\n", start_pos)) != std::string::npos)
    {
        std::cout << "stex1" << std::endl;
        message.erase(pos, 2);
        start_pos = pos;
    }
    return message;
}

void Client::_parse_array(std::string& message)
{
    std::string user = _helper(message, "USER");
    std::string nick = _helper(message, "NICK");
    std::string pass = _helper(message, "PASS");
    _parseUser(user, "USER");
    _parseUser(nick, "NICK");
    _parseUser(pass, "PASS");
    if (!pass.empty() && !nick.empty() && !user.empty())
        _messageForClient();
}

void Client::_messageForClient()
{
    if (!_isReceived && !_userName.empty() && !_serverName.empty() && !_hostName.empty() && !_nickName.empty() && !_realName.empty())
    {
        std::string message = ":server 001 " + _nickName +
                        " :Welcome to the IRC server\r\n";
        write(_fd, message.c_str(), message.size());
        _isReceived = true;
    }
}

void Client::_parseUserNameHelper(std::string& user, std::string& word, std::string type)
{
    std::string::size_type pos = 0;
    std::string::size_type start_pos = 0;
    if (type.size() != 0)
    {
        while ((pos = user.find(type, start_pos)) != std::string::npos)
        {
            start_pos = pos;
            start_pos++;
        }
    }
    word = user.substr(start_pos, user.size() - start_pos);
    if (type == ":")
        user.erase(start_pos - 2, user.size() - start_pos + 2);
    else if (type.size() == 0)
        user.erase(start_pos, user.size());
    else 
        user.erase(start_pos - 1, user.size() - start_pos + 1);
    
}

void Client::_parseUser(std::string& user, std::string type)
{
    if (!user.empty() && !_isReceived)
    {
        if (type == "USER")
        {
            _parseUserNameHelper(user, _realName, ":");
            _parseUserNameHelper(user, _serverName, " ");
            _parseUserNameHelper(user, _hostName, " ");
            _parseUserNameHelper(user, _userName, "");
        }
        else if (type == "NICK")
            _parseUserNameHelper(user, _nickName, "");
        else if (type == "PASS")
            _parseUserNameHelper(user, _pass, "");
    }
}

std::string Client::_helper(std::string& message, std::string find_key)
{
    std::string::size_type pos = 0;
    std::string::size_type start_pos = 0;
    std::string word;
    if ((pos = message.find(find_key, start_pos)) != std::string::npos)
    {
        word = message.substr(pos + find_key.size() + 1, message.size() - pos);
        message.erase(pos, message.size() - pos);
    }
    return word;
}
