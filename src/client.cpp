#include "../inc/ft_irc.hpp"

Client::Client()
{
    _isRegistered = false;
    _sendMessageOne = false;
}

Client::Client(int fd, const std::string& serverPass)
{
    _fd = fd;
    _isRegistered = false;
    _sendMessageOne = false;
    _serverPass = serverPass;
}

void Client::messageToClient(std::string& message)
{
    if (_isRegistered && !_sendMessageOne)
    {
        sendMessage(":localhost 001 " + _nick + " :Welcome to IRC\r\n");
        sendMessage(":localhost 002 " + _nick + " :Your host is localhost\r\n");
        sendMessage(":localhost 003 " + _nick + " :This server was created today\r\n");
        sendMessage(":localhost 004 " + _nick + " localhost 1.0 o o\r\n");
        _sendMessageOne = true;
    }
    if (message.substr(0, 4) == "PING")
    {
        std::string tmp = message.substr(5);
        if (!tmp.empty() && tmp[0] == ' ')
            tmp.erase(0, 1);
        sendMessage("PONG : " + tmp + "\r\n");
    }
}

void Client::hendleMessage(const std::set<std::string> &nickName, std::string& message)
{
    if (!_isRegistered)
    {
        findCapLs(message);
        if (message.find("PASS") != std::string::npos && _pass.empty())
        {
            findPass(message);
            if (_pass.empty())
            {
                sendMessage("PASS" + std::string(ERR_NEEDMOREPARAMS));
                throw std::runtime_error("");
            }
            if (_pass != _serverPass)
            {
                sendMessage(std::string(ERR_ALREADYREGISTRED));
                throw std::runtime_error("");
            }
            message.clear();
        }
        else if (message.find("NICK") != std::string::npos && _nick.empty())
        {
            findNick(message);
            if (_nick.empty())
            {
                sendMessage(std::string(ERR_NONICKNAMEGIVEN));
                throw std::runtime_error("");
            }
            std::set<std::string>::const_iterator it = nickName.begin();
            while (it != nickName.end())
            {
                if (*it == _nick)
                    break;
                ++it;
            }
            if (it != nickName.end())
            {
                sendMessage(_nick + std::string(ERR_NICKNAMEINUSE));
                throw std::runtime_error("");
            }
            if (!std::isalnum(_nick[0]))
            {
                sendMessage("_nick" + std::string(ERR_ERRONEUSNICKNAME));
                throw std::runtime_error("");
            }
            for (std::string::size_type i = 0; i < _nick.length(); ++i)
            {
                if (!std::isalnum(_nick[i]) ||
                    _nick[i] == '_' || _nick[i] == '-' ||
                    _nick[i] == '{' || _nick[i] == '}' ||
                    _nick[i] == '[' || _nick[i] == ']' ||
                    _nick[i] == '\\')
                {
                    sendMessage("_nick" + std::string(ERR_ERRONEUSNICKNAME));
                    throw std::runtime_error("");
                }
            }
            message.clear();
        }
        else if (message.find("USER") != std::string::npos &&
                 _realName.empty() && _serverName.empty() &&
                 _hostName.empty() && _userName.empty())
        {
            findUser(message);
            if (_realName.empty() || _serverName.empty() ||
                _hostName.empty() || _userName.empty())
            {
                sendMessage("USER" + std::string(ERR_NEEDMOREPARAMS));
                throw std::runtime_error("");
            }
            message.clear();
        }
        // if (message.find("USER") != std::string::npos)
        // {
        //     if (_isRegistered)
        //     {
        //         sendMessage(std::string(ERR_ALREADYREGISTRED));
        //         throw;
        //     }
        // }
        if (!_pass.empty() && !_nick.empty() && 
            !_realName.empty() && !_serverName.empty() &&
            !_hostName.empty() && !_userName.empty())
            _isRegistered = true;
    }
    if (_isRegistered)
        messageToClient(message);
}

void Client::findCapLs(std::string& message)
{
    if (message.empty())
        return ;
    std::string::size_type pos = 0;
    std::string tmp = message.substr(0, pos);
    if (tmp == "CAP LS")
        sendMessage(":localhost CAP * LS :\r\n");
}

void Client::findPass(std::string& message)
{
    if (message.empty() || !_pass.empty())
        return ;
    std::string::size_type passPos = 0;
    if ((passPos = message.find("PASS ", passPos)) != std::string::npos)
    {
        std::string tmp = message.substr(passPos + 5, message.length());
        if (!tmp.empty())
            _pass = tmp;
    }
}

void Client::findNick(std::string& message)
{
    if (message.empty() || !_nick.empty())
        return ;
    std::string::size_type nickPos = 0;
    if ((nickPos = message.find("NICK ", nickPos)) != std::string::npos)
    {
        std::string tmp = message.substr(nickPos + 5, message.length());
        if (!tmp.empty())
            _nick = tmp;
    }
}

void Client::findUser(std::string& message)
{
    if (message.empty() || (!_realName.empty() && !_serverName.empty() && !_hostName.empty() && !_userName.empty()))
        return ;
    std::string::size_type userPos = 0;
    if ((userPos = message.find("USER ", 0)) != std::string::npos)
    {
        std::string::size_type spacePos = 0;
        if ((spacePos = message.find(" :", userPos + 5)) != std::string::npos)
        {
            _realName = message.substr(spacePos + 2, message.length());
            message.erase(spacePos, message.length());
        }
        if ((spacePos = message.rfind(" ", message.length())) != std::string::npos)
        {
            _serverName = message.substr(spacePos + 1, message.length());
            message.erase(spacePos, message.length());
        }
        if ((spacePos = message.rfind(" ", message.length())) != std::string::npos)
        {
            _hostName = message.substr(spacePos + 1, message.length());
            message.erase(spacePos, message.length());
        }
        if ((spacePos = message.rfind(" ", message.length())) != std::string::npos)
        {
            _userName = message.substr(spacePos + 1, message.length());
            message.erase(spacePos, message.length());
        }
    }
    message.clear();
}

void Client::sendMessage(std::string message)
{
    send(_fd, message.c_str(), message.size(), 0);
}

std::string Client::getNick() const
{
    return _nick;
}

void Client::setNick(const std::string& nick)
{
    _nick = nick;
}

std::string Client::getUser() const
{
    return _userName;
}

bool Client::isRegistered() const
{
    return _isRegistered;
}