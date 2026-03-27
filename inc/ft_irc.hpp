#pragma once

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <map>
#include <set>
#include <sstream>

#define MAX_EVENTS 10

#define ERR_NEEDMOREPARAMS " :Not enough parameters\r\n"
#define ERR_ALREADYREGISTRED ":You may not reregister\r\n"
#define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"
#define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\r\n"

#include "server.hpp"
#include "client.hpp"
#include "chanel.hpp"
