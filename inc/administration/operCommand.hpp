#pragma once

#include "../../inc/administration/AAdministrationCommand.hpp"
#include "../../inc/include.hpp"
#include "../../inc/administration/operMode/AOperMode.hpp"

#include "../../inc/administration/operMode/killMode.hpp"
#include "../../inc/administration/operMode/rehashMode.hpp"
#include "../../inc/administration/operMode/restartMode.hpp"
#include "../../inc/administration/operMode/sQuitMode.hpp"
#include "../../inc/administration/operMode/wallopsMode.hpp"

class OperCommand : public AAdministrationCommand
{
public:
    OperCommand();
    ~OperCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    std::map<std::string, AOperMode*> _mode;
};