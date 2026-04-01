#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"
class Client;

class UserCommand : public ARegisterCommand
{
public:
    UserCommand();
    ~UserCommand();

public:
    void executeCommand(Client& client, int fd, std::vector<std::string>& message);
};