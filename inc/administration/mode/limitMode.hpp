#pragma once

#include "AModeCommand.hpp"

class LimitMode : public AModeCommand
{
public:
    LimitMode();
    ~LimitMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag);

private:
    void addLimit(Client& client, Chanel& chanel, const std::string& message, bool flag) const;
    void subLimit(Client& client, Chanel& chanel, bool flag) const;
};