#include "../inc/ft_irc.hpp"

Client::Client()
{
    _isRegistered = false;
}

Client::Client(int fd, const std::string& serverPass)
{
    _fd = fd;
    _isRegistered = false;
    _serverPass = serverPass;
}

void Client::hendleMessage(const std::vector<std::string> &nickName, std::string& message)
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
                throw;
            }
            if (_pass != _serverPass)
            {
                sendMessage(std::string(ERR_ALREADYREGISTRED));
                throw;
            }
            message.clear();
        }
        else if (message.find("NICK") != std::string::npos && _nick.empty())
        {
            findNick(message);
            if (_nick.empty())
            {
                sendMessage(std::string(ERR_NONICKNAMEGIVEN));
                throw;
            }
            std::vector<std::string>::const_iterator it = nickName.begin();
            while (it != nickName.end())
            {
                if (*it == _nick)
                    break;
                ++it;
            }
            if (it == nickName.end())
            {
                sendMessage(_nick + std::string(ERR_NICKNAMEINUSE));
                throw;
            }
            if (std::isalnum(_nick[0]))
            {
                sendMessage("_nick" + std::string(ERR_ERRONEUSNICKNAME));
                throw;
            }

            for (std::string::size_type i = 0; i < _nick.length(); ++i)
            {
                if (std::isalnum(_nick[i]) ||
                    _nick[i] == '_' || _nick[i] == '-' ||
                    _nick[i] == '{' || _nick[i] == '}' ||
                    _nick[i] == '[' || _nick[i] == ']' ||
                    _nick[i] == '\\')
                {
                    sendMessage("_nick" + std::string(ERR_ERRONEUSNICKNAME));
                    throw;
                }
            }
            message.clear();
        }
        else if (message.find("USER") != std::string::npos)
        {
            findUser(message);
            std::cout << "USER " << _userName << " " << _hostName << " " << _serverName << " :" << _realName << std::endl; 
            if (_realName.empty() || _serverName.empty() ||
                _hostName.empty() || _userName.empty())
            {
                sendMessage("USER" + std::string(ERR_NEEDMOREPARAMS));
                throw;
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
        {
            std::cout << "PASS " << _pass << std::endl; 
            std::cout << "NICK " << _nick << std::endl; 
            _isRegistered = true;
            sendMessage(":localhost 001 " + _nick + " :Welcome to the IRC server, " + _nick + "!\r\n");
        }
    }
    
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