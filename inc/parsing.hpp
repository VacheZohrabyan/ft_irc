#pragma once

#include <iostream>
#include <vector>

class Parsing
{
public:
    Parsing(char** argv);

public:
    const std::string& getPort() const;
    const std::string& getPass() const;

private:
    void _pars(char** argv);
    void _parse_port(std::string& port);
    void _parse_pass(std::string& pass);
public:
    std::vector<std::string> _input;
    std::string _port;
    std::string _pass;
    bool _standart_port;
};