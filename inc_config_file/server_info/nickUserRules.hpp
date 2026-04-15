#pragma once

#include <iostream>

class NickUserRules
{
public:
    std::size_t minNickNameLength;
    std::size_t maxNickNameLength;
    std::size_t minUserNameLength;
    std::size_t maxUserNameLength;
    std::size_t maxRealNameLength;
    bool allowSpecialCharsInNickName;
    std::size_t nickNameChangeCoolDownSeconds;
};