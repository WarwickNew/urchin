#include "message.h"
#include "protobuf_gen/amessage.pb-c.h"

#define MAX_MSG_SIZE 1024

void msg__amsg_test(int a) {
  AMessage msg = AMESSAGE__INIT; // The massage format
  void *buf;                     // Buffer to store serialized data
  unsigned len;                  // length of serialized data

  msg.a = a;
  msg.b = 2;
  msg.has_b = 1;
  len = amessage__get_packed_size(&msg);
  buf = malloc(len);
  amessage__pack(&msg, buf); // we now have a serialised message buffer

  fprintf(stderr, "Writing %d serialized bytes\n",
          len); // See the length of message
  fwrite(buf, len, 1, stderr);

  // unpack the message
  AMessage *msg2;
  uint8_t buf2[MAX_MSG_SIZE];
  size_t msg_len = len;
  memcpy((void *)buf2, (void *)buf, msg_len);

  free(buf);

  msg2 = amessage__unpack(NULL, msg_len, buf2);
  if (msg2 == NULL) {
    err__crash("error unpacking incoming message\n");
  }

  // display the message's fields.
  printf("Received: a=%d", msg2->a); // required field
  if (msg2->has_b)                   // handle optional field
    printf("  b=%d", msg2->b);
  printf("\n");

  // Free the unpacked message
  amessage__free_unpacked(msg2, NULL);
}

int msg__create_serv_connection(int portno) {
  int sockfd, clientsockfd, errflag;
  struct sockaddr_in serv_addr;

  // Create socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    err__crash("Can't open socket.");
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
    err__crash("Can't bind socket");
  }

  errflag = listen(sockfd, 5);
  if (errflag < 0) {
    err__crash("Can't listen for connections");
  }
  char successmsg[80]; // Buffer for success message
  snprintf(successmsg, sizeof successmsg, "Server funning on port: %d", portno);
  err__log(successmsg);

  return sockfd;
}

void msg__destroy_connection(int sockfd) { close(sockfd); }

int msg__accept_cli_connection(int server_sockfd) {
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof cli_addr;

  int cli_sockfd = accept(server_sockfd, (struct sockaddr *)&cli_addr, &clilen);

  if (cli_sockfd < 0) {
    err__crash("Can't accept connection");
  }

  return cli_sockfd;
}
