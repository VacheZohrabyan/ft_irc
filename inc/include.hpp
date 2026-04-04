#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/epoll.h>
#include <map>
#include <unistd.h>
#include <set>
#include <sstream>

#define MAX_EVENTS 10
#define MAX_CHANELL 10

#define ERR_NEEDMOREPARAMS " :Not enough parameters\r\n"
#define ERR_ALREADYREGISTRED " :You may not register\r\n"
#define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"
#define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\r\n"
#define ERR_BADCHANMASK " :Cannot join channel (+k)\r\n"
#define ERR_NOSUCHCHANNEL " :No such channel\r\n"
#define ERR_TOOMANYCHANNELS " :You have joined too many channels\r\n"
#define ERR_CHANNELISFULL " :Cannot join channel (+l)\r\n"
