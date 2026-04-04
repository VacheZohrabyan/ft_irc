#pragma once

#include "../include.hpp"

class AMessageCommand
{
public:
    virtual ~AMessageCommand()
    {
        
    }

public:
    virtual void executeCommand(Client& client, Chanel& chanel, int fd, std::vector<std::string>& message) = 0;
};