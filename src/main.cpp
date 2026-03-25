#include "../inc/ft_irc.hpp"

int main(int argc, char** argv)
{
    if (argc != 3)
        return (std::cerr << "To meny argument" << std::endl, 0);
    try
    {
        Server server(argv[1], argv[2]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}