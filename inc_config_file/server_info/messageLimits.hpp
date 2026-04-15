#pragma once

#include <iostream>

class MessageLimits
{
public:
    short maxMessageLength;
    short maxTopicLength;
    short maxChannelsNameLength;
    short max_modes_per_command;
    short maxAwayMessageLength;    
};