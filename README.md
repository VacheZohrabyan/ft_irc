*This project has been created as part of the 42 curriculum by [Your Name].*

## Description
**ft_irc** is a custom Internet Relay Chat (IRC) server developed in C++98. The goal of this project is to understand the layers of network communication, specifically the TCP/IP protocol, and to implement a functional server capable of handling multiple clients simultaneously using non-blocking I/O and event-driven architecture.

The server allows users to authenticate, join channels, and exchange real-time messages. It implements various IRC commands and handles different user privileges, distinguishing between regular users and channel operators.

## Instructions

### Compilation
The project includes a `Makefile` for easy compilation. To build the executable, run:

make
This will generate an executable named ircserv.

Execution
To launch the server, use the following command:

./ircserv <port> <password>

port: The port number the server will listen on (e.g., 6667).

password: The connection password required for any client to connect.

Connecting with a Client
You can use any standard IRC client (like Irssi, AdiIRC) or Netcat to connect:

Bash

nc -C 127.0.0.1 <port>
Once connected, authenticate using the following sequence:
PASS <password>, NICK <your_nick>, and USER <username> 0 * :<realname>.

Features
Multiplexing: Uses epoll to handle multiple connections efficiently in a single process.

Non-blocking I/O: All socket operations are non-blocking to ensure the server never hangs.

Channel Management: Support for creating channels, joining, and exchanging messages.

Operator Commands: Implementation of KICK, INVITE, TOPIC, and MODE (i, t, k, o, l).

Buffer Management: Robust handling of fragmented TCP packets and Ctrl+D (EOF) scenarios.

Resources
RFC 1459 & 2812: The official specifications for the IRC protocol.

Beej's Guide to Network Programming: Essential resource for understanding socket programming.

Modern C++ Documentation: Reference for STL containers and C++98 standards.