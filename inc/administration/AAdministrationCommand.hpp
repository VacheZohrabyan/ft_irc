#pragma once

#include "../../inc/include.hpp"

class Chanel;
class Client;

class AAdministrationCommand
{
public:
    virtual ~AAdministrationCommand()
    {

    }

public:
    virtual void executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients) = 0;
};