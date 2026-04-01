#pragma once

#include "../include.hpp"

class AChannelCommand
{
public:
    virtual ~AChannelCommand();

public:
    virtual void executeCommand() = 0;
};