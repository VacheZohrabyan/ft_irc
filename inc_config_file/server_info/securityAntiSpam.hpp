#pragma once

#include <iostream>

class SecurityAntiSpam
{
public:
    short maxMessagePerSeconds;
    short maxJoinsPerMinute;
    short maxNickChangesPerMinute;
    short maxFailedLoginAttempts;
    short failedLoginBanMinutes;
    bool antiFloodEnabled;
    bool antiSpamEnabled;
    bool antiCloneConnections;
    bool ignoreDuplicateMessage;
};