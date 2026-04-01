#pragma once

#include "../include.hpp"
#include "AChannelCommand.hpp"
#include "../utils.hpp"

class client;

class JoinCommand : public AChannelCommand
{
public:
    JoinCommand();
    ~JoinCommand();

public:
    void executeCommand();
};