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

#define ERR_NEEDMOREPARAMS " :Not enough parameters\r\n"
#define ERR_ALREADYREGISTRED " :You may not register\r\n"
#define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"
#define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\r\n"