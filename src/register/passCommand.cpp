#include "../../inc/register/passCommand.hpp"
#include "../../inc/client.hpp"

PassCommand::PassCommand()
{

}

PassCommand::~PassCommand()
{

}

void PassCommand::executeCommand(Client& client, int fd, std::vector<std::string>& message)
{
    if (client.getIsRegistered())
        Utils::errorAlreadyRegister(client.getNick(), fd);
    std::string tmp;
    for (std::vector<std::string>::const_iterator it = message.begin() + 1; it != message.end(); )
    {
        tmp.append(*it);
        ++it;
        if (it != message.end())
            tmp.append(" ");
    }
    client.setPass(tmp);
    if (client.getServerPass() != tmp)
        Utils::errorAlreadyRegister(client.getNick(), fd);
    std::cout << "stex2" << std::endl;
}