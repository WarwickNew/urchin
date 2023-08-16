// Sorry in advance for all the comments. This project is also a way for me to
// learn C.

#include "error.h"
#include "message.h"
#include <unistd.h>
#include <netdb.h>      // Contains host structure
#include <netinet/in.h> //sockaddr_in
#include <stdio.h>
#include <stdlib.h> // Keeping for conversion functions
#include <string.h>
#include <strings.h>
#include <sys/socket.h> // sockaddr
#include <sys/types.h>

// void error_crash(const char *msg) {
//   fprintf(stderr, "error crash: %s\n", msg);
//   exit(EXIT_FAILURE);
// }
//
// void error_warn(const char *msg) { fprintf(stderr, "warning: %s\n", msg); }
//
// // TODO: Save the logs somewhere
// void error_log(const char *msg) { fprintf(stderr, "log: %s\n", msg); }

int main(int argc, char *argv[]) {
  // Set up containers for file descriptor id's
  int sockfd, portno, errflag;
  struct sockaddr_in serv_addr;
  bzero((char *)&serv_addr, sizeof(serv_addr));
  struct hostent *server;
  char msgbuffer[255];

  if (argc < 2) {
    err__crash("Not enough server info has been provided");
  }

  if (argc > 2) {
    portno = atoi(argv[2]);
  } else {
    portno = 3940;
  }

  // Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    err__crash("Can't open socket.");

  server = gethostbyname(argv[1]);
  if (server == NULL)
    err__crash("No such host exists :(");

  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  errflag = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (errflag < 0)
    err__crash("Failed to connect to host");

  msg__req_login(&sockfd, "username", "passwd");

  while (1) {
    bzero(msgbuffer, sizeof msgbuffer);
    fgets(msgbuffer, sizeof msgbuffer, stdin);
    errflag = write(sockfd, msgbuffer, strlen(msgbuffer));
    if (errflag < 0)
      err__crash("Failed to write message");

    bzero(msgbuffer, sizeof msgbuffer);
    errflag = read(sockfd, msgbuffer, sizeof msgbuffer);
    if (errflag < 0)
      err__crash("Failed to read message");

    printf("Server: %s", msgbuffer);

    int cmp = strncmp("Bye", msgbuffer, 3);
    if (cmp == 0)
      break;
  }

  close(sockfd);
  return EXIT_SUCCESS;
}
