#pragma once

#include "../src/protobuf_gen/amessage.pb-c.h"
#include "../src/protobuf_gen/commands.pb-c.h"
#include "../src/protobuf_gen/player.pb-c.h"
#include "error.h"
#include "message_internal.h"
#include <netinet/in.h> //sockaddr_in
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // sockaddr
#include <sys/types.h>

void msg__amsg_test(int a);

// Creates a socket set's it up to listen to listen on the specified port and
// returns the file descriptor
int msg__create_serv_connection(int portno);

// Closes socket connection
void msg__destroy_connection(int sockfd);

// Creates a socket for the client and returns the file descriptor
int msg__accept_cli_connection(int server_sockfd);

// Handle logins
void msg__recv_login(int *con_sockfd);
void msg__req_login(int *con_sockfd, char *usernm, char *passwd);

// send and recive commands
Command *msg__recv_command(int *con_sockfd);
void msg__req_command(int *con_sockfd, char *usernm, char *passwd);
