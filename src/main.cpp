#include "../inc/include.hpp"
#include "../inc/server.hpp"
#include <sys/wait.h>

bool server_runing = true;

void signalHandler(int sig)
{
    server_runing = false;
    (void)sig;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    if (argc != 3)
        return -1;
    try
    {
        Server obj(argv);
        obj.runServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}