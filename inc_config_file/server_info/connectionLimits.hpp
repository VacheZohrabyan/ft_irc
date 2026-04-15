#pragma once

#include <iostream>

class ConnectionLimits
{
public:
    std::size_t maxClinets;
    std::size_t maxConnectionsPerIp;
    std::size_t maxChannels;
    std::size_t maxChannelsPerUser;
    std::size_t maxUsersPerChannels;
    std::size_t ClientTimeoutSeconds;
    std::size_t pingIntervalSeconds;
    std::size_t pongIntervalSeconds;
    std::size_t connectionBacklog;
};