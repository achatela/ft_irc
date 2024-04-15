# IRC Server Project (ft_irc)

## Overview
This project involves developing an IRC (Internet Relay Chat) server named `ircserv`, entirely in C++ 98, adhering to strict project guidelines. The server is designed to handle multiple client connections simultaneously without using multi-threading (forking is forbidden). All I/O operations are performed in a non-blocking manner using a single `poll()` system call or its equivalent. This server works over TCP/IP and is compatible with existing IRC clients for communication.

## Features
- **Connection Management**: Supports multiple clients connecting concurrently without server hang-ups.
- **Non-Blocking I/O**: Utilizes non-blocking sockets combined with `poll()`, `select()`, `kqueue()`, or `epoll()` to manage all read/write operations efficiently.
- **Authentication**: Allows IRC clients to authenticate using a predefined password.
- **User Interaction**: Users can set nicknames, usernames, join channels, and send/receive private messages.
- **Channel Management**: Supports basic channel operations like joining, messaging, and managing channel modes.
- **Operator Commands**: Implements operator-specific commands such as KICK, INVITE, TOPIC, and MODE adjustments.

## Restrictions 
- **No External Libraries**: Only standard C++ 98 libraries and system calls are allowed.
- **Reference Client**: A specific IRC client must be designated as a reference for testing the server functionality during evaluation. (IRSSI)

## Usage
To run the server, use the following command:
```bash
./ircserv <port> <password>
```

## Compilation
To compile the server, run the following commands:
```bash
make        # Compile the server
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Re-compile the server
```

