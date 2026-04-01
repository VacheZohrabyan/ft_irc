#include "../inc/include.hpp"
#include "../inc/server.hpp"

int main(int argc, char** argv)
{
    if (argc != 3)
        return -1;
    try
    {
        Server obj(argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}