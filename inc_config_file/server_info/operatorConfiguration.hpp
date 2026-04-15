#pragma once

#include <iostream>

class OperatorConfiguration
{
public:
    std::string operatorName;
    std::string operatorPassword;
    std::string operatorHostMask;
    bool operatorCanKill;
    bool operatorCanGline;
    bool operatorCanRehash;
    bool operatorCanRestart;
    bool operatorCanDie;
};