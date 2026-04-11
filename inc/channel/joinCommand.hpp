#pragma once

#include "../include.hpp"
#include "AChannelCommand.hpp"
#include "../utils.hpp"
#include "chanel.hpp"

class client;
class Chanel;

class JoinCommand : public AChannelCommand
{
public:
    JoinCommand();
    ~JoinCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    std::string concatPass(const std::vector<std::string>& message) const;
};