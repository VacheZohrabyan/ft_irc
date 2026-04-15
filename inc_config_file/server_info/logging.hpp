#pragma once

#include <iostream>

class Logging
{
public:
    bool enableLogging;
    std::string logFile;
    std::string logLevel;
    bool logConnections;
    bool logDisconnections;
    bool logFailedLogins;
    bool logCommands;
    bool logChannels;
    bool logPrivateMessages;
    bool saveChatHistory;
    std::string chatHistoryDirectory;
};