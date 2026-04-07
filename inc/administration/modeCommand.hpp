#pragma once

#include "../../inc/administration/AAdministrationCommand.hpp"
#include "../../inc/include.hpp"
#include "../../inc/utils.hpp"

class Chanel;

class ModeCommand : public AAdministrationCommand
{
public:
    ModeCommand();
    ~ModeCommand();

public:
    void executeCommand(std::map<std::string, Chanel>& chanels, std::vector<std::string>& message);
};