#pragma once

#include <iostream>

class FeatureFlags
{
public:
    bool allowGuestNickNames;
    bool allowPrivateMessages;
    bool allowNoticeMessages;
    bool allowWhoCommand;
    bool allowWhoisCommand;
    bool allowOperCommand;
    bool allowWallops;
    bool allowKickCommand;
    bool allowInviteCommand;
    bool allowModeCommand;
    bool allowTopicCommand;
    bool allowAwayCommand;
    bool allowListCommand;
    bool allowNamesCommand;
};