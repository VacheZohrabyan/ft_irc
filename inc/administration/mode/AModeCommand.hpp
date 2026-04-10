#pragma once

#include "../AAdministrationCommand.hpp"
#include "../../include.hpp"

class Chanel;
class Client;

class AModeCommand
{
public:
    virtual ~AModeCommand()
    {

    }

public:
    virtual void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients) = 0;
};