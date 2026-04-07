#pragma once

#include "../../inc/include.hpp"
#include "../../inc/utils.hpp"

class AAdministrationCommand
{
public:
    virtual ~AAdministrationCommand()
    {

    }

public:
    virtual void executeCommand();
};