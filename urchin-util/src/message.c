#include "message.h"
#include "error.h"
#include "protobuf_gen/amessage.pb-c.h"
#include "protobuf_gen/player.pb-c.h"
#include "world_structures.h"
#include <stdio.h>

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
    err__crash("error unpacking incoming message");
  }

  // display the message's fields.
  printf("Received: a=%d", msg2->a); // required field
  if (msg2->has_b)                   // handle optional field
    printf("  b=%d", msg2->b);
  printf("\n");

  // Free the unpacked message
  amessage__free_unpacked(msg2, NULL);
}

// Gets size of protobuf message inside bigger buffer
size_t get_msg_size_in_buffer(unsigned max_length, uint8_t *out) {
  size_t cur_len = 0;
  while ((out[cur_len]) != 0) {
    cur_len++;
    if (cur_len >= max_length) {
      err__warn("max message length exceeded\n");
      return max_length;
    }
  }
  return cur_len;
}

void msg__recv_login(int *con_sockfd) {
  uint8_t msgbuf[MAX_MSG_SIZE];
  bzero(msgbuf, sizeof msgbuf);

  if (read(*con_sockfd, msgbuf, sizeof msgbuf) < 0) {
    err__warn("Connection did not send login data");
  }

  size_t msg_len = get_msg_size_in_buffer(MAX_MSG_SIZE, msgbuf);
  PlayerLogin *pl = player_login__unpack(NULL, msg_len, msgbuf);
  if (pl == NULL) {
    err__warn("Error unpacking login message");

    player_login__free_unpacked(pl, NULL);
    return;
  }

  // TODO: Do something with login data
  char msg[80];
  snprintf(msg, sizeof msg, "Recieved Login: %s %s \n", pl->username,
           pl->password);
  err__log(msg);

  player_login__free_unpacked(pl, NULL);
}

void msg__req_login(int *con_sockfd, char *usernm, char *passwd) {
  PlayerLogin pl = PLAYER_LOGIN__INIT;
  void *msgbuf;
  unsigned len;

  pl.username = usernm;
  pl.password = passwd;

  len = player_login__get_packed_size(&pl);
  msgbuf = malloc(len);
  player_login__pack(&pl, msgbuf);

  if (write(*con_sockfd, msgbuf, len) < 0) {
    err__crash("Couldn't write response message");
    free(msgbuf);
    return;
  }
  // See the length of message
  fprintf(stderr, "Writing %d serialized bytes\n", len);
  fwrite(msgbuf, len, 1, stderr);

  free(msgbuf);
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

void msg__recv_command(int *con_sockfd) {}
void msg__req_command(int *con_sockfd, char *usernm, char *passwd) {}
