#pragma once

#include "../include.hpp"

class Client;
class Chanel;

class AChannelCommand
{
public:
    virtual ~AChannelCommand()
    {
        
    }

public:
    virtual void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients) = 0;
};