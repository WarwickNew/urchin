#pragma once

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msg_amsg_test(int a);

// Creates a socket set's it up to listen to listen on the specified port and
// returns the file descriptor
int msg_create_serv_connection(int portno);

// Creates a socket for the client and returns the file descriptor
int msg_accept_cli_connection();
