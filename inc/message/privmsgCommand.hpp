#pragma once 

#include "AMessageCommand.hpp"
#include "../include.hpp"
#include "../utils.hpp"

class Client;
class Chanel;

class PrivMsgCommand : public AMessageCommand
{
public:
    PrivMsgCommand();
    ~PrivMsgCommand();

public:
    void executeCommand(Client& client, Chanel& chanel, int fd, std::vector<std::string>& message);
};