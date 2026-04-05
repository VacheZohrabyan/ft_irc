#pragma once 

#include "AMessageCommand.hpp"
#include "../include.hpp"
#include "../utils.hpp"

class Client;
class Chanel;

class NoticeCommand : public AMessageCommand
{
public:
    NoticeCommand();
    ~NoticeCommand();

public:
    void executeCommand(Client& client, const std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message);
};