#pragma once

#include <iostream>

class ChannelSettings
{
public:
    std::string defaultChannelMode;
    bool allowChannelCreation;
    bool allowPrivateChannels;
    bool allowSecretChannels;
    bool allowInviteOnlyChannels;
    bool allowTopicRestriction;
    bool allowChannelKeys;
    bool allowUserLimitMode;
    bool ChannelHistoryLimit;
};