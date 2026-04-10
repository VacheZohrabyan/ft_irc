#pragma once

#include "../../inc/administration/AAdministrationCommand.hpp"
#include "../../inc/administration/mode/AModeCommand.hpp"
#include "../../inc/include.hpp"
#include "../../inc/utils.hpp"

#include "mode/inviteMode.hpp"
#include "mode/keyMode.hpp"
#include "mode/limitMode.hpp"
#include "mode/operatorMode.hpp"
#include "mode/topicMode.hpp"

class Chanel;
class Client;

class ModeCommand : public AAdministrationCommand
{
public:
    ModeCommand();
    ~ModeCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message);

private:
    std::map<char, AModeCommand*> _modeCommand;
    bool _adding;
};