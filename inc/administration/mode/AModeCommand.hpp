#pragma once

#include "../AAdministrationCommand.hpp"

class Chanel;
class Client;

class AModeCommand
{
public:
    virtual ~AModeCommand()
    {

    }

public:
    virtual void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message) = 0;
};