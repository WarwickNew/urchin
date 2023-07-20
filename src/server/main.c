// Sorry in advance for all the comments. This project is also a way for me to
// learn C.

#include <netinet/in.h> //sockaddr_in
#include <stdio.h>
#include <stdlib.h> // Keeping for conversion functions
#include <string.h>
#include <strings.h>
#include <sys/socket.h> // sockaddr
#include <sys/types.h>

void error_crash(const char *msg) {
  fprintf(stderr, "error crash: %s\n", msg);
  exit(EXIT_FAILURE);
}

void error_warn(const char *msg) { fprintf(stderr, "warning: %s\n", msg); }

// TODO: Save the logs somewhere
void error_log(const char *msg) { fprintf(stderr, "log: %s\n", msg); }

int main(int argc, char *argv[]) {
  // Set up containers for file descriptor id's
  int sockfd, clientsockfd, portno, errflag;
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

  // Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error_crash("Can't open socket.");
  }

  // Make sure there is no junk data in serve_addr
  bzero((char *)&serv_addr, sizeof serv_addr);

  // Tell the connection to use ipv4 and port number
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  // Bind Socket
  errflag = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  if (errflag < 0) {
    error_crash("Can't bind socket");
  }

  errflag = listen(sockfd, 5);
  if (errflag < 0) {
    error_crash("Can't listen for connections");
  }

  char portstr[5]; // Buffer to store string version of port
  snprintf(portstr, sizeof portstr, "%d", portno);
  printf("Server Listening on port: %s\n", portstr);

  clientsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (clientsockfd < 0) {
    error_crash("Can't accept connection");
  }

  while (1) {
    // Empty message buffer
    bzero(msgbuffer, sizeof msgbuffer);

    errflag = read(clientsockfd, msgbuffer, sizeof msgbuffer);
    if (errflag < 0) {
      error_crash("Didn't recieve message from connection");
    }
    printf("Client: %s\n", msgbuffer);

    // clear buffer for writing
    bzero(msgbuffer, sizeof msgbuffer);
    fgets(msgbuffer, sizeof msgbuffer, stdin);

    errflag = write(clientsockfd, msgbuffer, strlen(msgbuffer));
    if (errflag < 0) {
      error_crash("Couldn't write response message");
    }

    int cmp = strncmp("Bye", msgbuffer, 3);
    if (cmp == 0)
      break;
  }

  close(clientsockfd);
  close(sockfd);

  return EXIT_SUCCESS;
}
