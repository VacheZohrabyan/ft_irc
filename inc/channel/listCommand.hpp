#pragma once

#include "../../inc/include.hpp"
#include "../../inc/channel/AChannelCommand.hpp"
#include "../../inc/utils.hpp"

class ListCommand : public AChannelCommand
{
public:
    ListCommand();
    ~ListCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message);

private:
    void helperFunction(int count, int fd, const std::string& nick_1, const std::string& chanelName, const std::string& topic) const;
};
