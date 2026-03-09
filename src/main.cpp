#include "../inc/ft_irc.hpp"

int main(int argc, char** argv)
{
    try
    {
        if (argc != 3)
            throw std::invalid_argument("meny argument");
        Parsing parsing(argv);
        Server obj;
        obj.init(parsing);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}