#pragma once

#include "AChannelCommand.hpp"

class Client;
class Chanel;

class TopicCommand : public AChannelCommand
{
public:
    TopicCommand();
    ~TopicCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    std::string concatMessage(const std::vector<std::string>& message) const;
};