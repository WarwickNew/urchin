// Sorry in advance for all the comments. This project is also a way for me to
// learn C.

#include "command.h"
#include "world.h"
#include <error.h>
#include <message.h>
#include <netinet/in.h> //sockaddr_in
#include <stdio.h>
#include <stdlib.h> // Keeping for conversion functions
#include <string.h>
#include <strings.h>
#include <sys/socket.h> // sockaddr
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Set up containers for file descriptor id's
  int serv_sockfd, cli_sockfd, portno, errflag;
  char msgbuffer[255];
  // Set port number.
  if (argc > 1) {
    portno = atoi(argv[1]);
  } else {
    portno = 3940;
  }

  // Socket address info
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen = sizeof cli_addr; // We can do this here as cli_addr isn't
                                      // touched until it's used

  // Create world
  Room *world = wrld__create();
  Player player;
  player.current_location = &world[0];

  // Create socket
  serv_sockfd = msg__create_serv_connection(portno);

  // Accept connection
  cli_sockfd = msg__accept_cli_connection(serv_sockfd);

  // Require login as first request
  msg__recv_login(&cli_sockfd);

  // HACK: test recieve of movement command
  err__log(player.current_location->name);
  cmd__process_cmd(&player, msg__recv_command(&cli_sockfd));
  err__log(player.current_location->name);

  while (1) {
    // Empty message buffer
    bzero(msgbuffer, sizeof msgbuffer);

    errflag = read(cli_sockfd, msgbuffer, sizeof msgbuffer);
    if (errflag < 0) {
      err__crash("Didn't recieve message from connection");
    }
    printf("Client: %s\n", msgbuffer);

    // clear buffer for writing
    bzero(msgbuffer, sizeof msgbuffer);
    fgets(msgbuffer, sizeof msgbuffer, stdin);

    errflag = write(cli_sockfd, msgbuffer, strlen(msgbuffer));
    if (errflag < 0) {
      err__crash("Couldn't write response message");
    }

    int cmp = strncmp("Bye", msgbuffer, 3);
    if (cmp == 0)
      break;
  }

  msg__destroy_connection(cli_sockfd);
  msg__destroy_connection(serv_sockfd);
  wrld__destroy(world);

  return EXIT_SUCCESS;
}
