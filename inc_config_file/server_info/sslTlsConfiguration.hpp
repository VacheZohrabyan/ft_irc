#pragma once

#include <iostream>

class SslTlsConfiguration
{
public:
    bool enavleSsl;
    short sslPort;
    std::string sslCertFile;
    std::string sslKeyFile;
    std::string sslKeyPassword;
};