#pragma once 

#include "AMessageCommand.hpp"
#include "../include.hpp"
#include "../utils.hpp"

class Client;
class Chanel;

class PrivMsg : public AMessageCommand
{
public:
    PrivMsg();
    ~PrivMsg();

public:
    void executeCommand(Client& client, Chanel& chanel, int fd, std::vector<std::string>& message);
};