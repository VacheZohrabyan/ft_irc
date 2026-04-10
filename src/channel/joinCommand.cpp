#include "../../inc/channel/joinCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/namesCommand.hpp"

JoinCommand::JoinCommand()
{

}

JoinCommand::~JoinCommand()
{

}

void JoinCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message)
{
	if (message.size() < 2)
		Utils::errorMoreParams(client.getNick(), fd);
	if (message[1].empty() || (message[1][0] != '#' && message[1][0] != '&'))
		Utils::errorBadChanMask(client.getNick(), fd);
	std::map<std::string, Chanel>::iterator it = chanel.find(message[1]);
	if (it == chanel.end())
	{
		if (chanel.size() == MAX_CHANELL)
			return Utils::errorNoSuchChannel(client.getNick(), fd);
		Chanel newChanel(message[1], fd, concatPass(message));
		newChanel.addClient(fd, client.getNick());
		chanel.insert(std::make_pair(message[1], newChanel));
	}
	else
	{
		if (it->second.getLimit())
			if (it->second.getCountClient() == it->second.getMaxCount())
				return Utils::errorChannelIsFull(message[1], fd);
		if (chanel[message[1]].getChanelPasswd())
		{
			if (message.size() < 3 || chanel[message[1]].getChannelPass() != concatPass(message))
				return Utils::errorBadChannelKey(client.getNick() + " " + message[1], fd);
			std::cout << "stex2\n";
		}
		it->second.addClient(fd, client.getNick());
	}
	std::cout << "stex1\n";
	std::string joinMessage = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " " + message[0] + " :" + message[1] + "\r\n";
	chanel[message[1]].broadCast(joinMessage, -1);
	joinMessage = ":localhost 332 " + client.getNick() + " " + message[1] + " :" + (chanel[message[1]].getTopic().empty() ? "No topic is set" : chanel[message[1]].getTopic()) + "\r\n";
	Utils::sendMessage(fd, joinMessage);
	NamesCommand().executeCommand(client, chanel, fd, message);
}

std::string JoinCommand::concatPass(const std::vector<std::string>& message) const
{
	std::string tmp = "";
	if (message.size() > 2)
	{
		for (std::vector<std::string>::const_iterator it = message.begin() + 2; it != message.end(); ++it)
		{
			if (it != message.begin() + 2)
				tmp += " ";
			tmp += *it;
		}
	}
	return tmp;
}