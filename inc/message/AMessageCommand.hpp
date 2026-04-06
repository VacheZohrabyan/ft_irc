#pragma once

#include "../include.hpp"

class Client;
class Chanel;

class AMessageCommand
{
public:
    virtual ~AMessageCommand()
    {
        
    }

public:
    virtual void executeCommand(Client& client, std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message) = 0;
};