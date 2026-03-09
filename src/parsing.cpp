#include "../inc/parsing.hpp"

Parsing::Parsing(char** argv)
{
    _standart_port = false;
    _pars(argv);
}

const std::string& Parsing::getPass() const
{
    return _pass;
}

const std::string& Parsing::getPort() const
{
    return _port;
}

void Parsing::_pars(char** argv)
{
    std::string::size_type start_pos = 1;
    while (argv[start_pos])
        _input.push_back(argv[start_pos++]);
    _parse_port(_input[0]);
    _parse_pass(_input[1]);
}

void Parsing::_parse_port(std::string& port)
{
    if (port.empty())
        throw std::invalid_argument("The port field is empty.");
    for (std::string::size_type i = 0; i < port.size(); ++i)
    {
        if (!std::isdigit(port[i]))
            throw std::invalid_argument("dont correct port");
    }
    int tmp = std::stoi(port);
    if (tmp < 0 || tmp > 65536)
        throw std::invalid_argument("is outside the port limits");
    else if (!_standart_port)
    {
        if (tmp >= 0 && tmp <= 1023)
            throw std::invalid_argument("is within the standard port limits");
    }
    _port = port;
}

void Parsing::_parse_pass(std::string& pass)
{
    _pass = pass;
}