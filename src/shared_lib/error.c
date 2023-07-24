#include "error.h"
#include "../protobuf_gen/amessage.pb-c.h"
#define MAX_MSG_SIZE 1024

void error_crash(const char *msg) {
  fprintf(stderr, "error crash: %s\n", msg);
  exit(EXIT_FAILURE);
}

void error_warn(const char *msg) { fprintf(stderr, "warning: %s\n", msg); }

// TODO: Save the logs somewhere
void error_log(const char *msg) { fprintf(stderr, "log: %s\n", msg); }

void msg_amsg_test(int a) {
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
    error_crash("error unpacking incoming message\n");
  }

  // display the message's fields.
  printf("Received: a=%d", msg2->a); // required field
  if (msg2->has_b)                   // handle optional field
    printf("  b=%d", msg2->b);
  printf("\n");

  // Free the unpacked message
  amessage__free_unpacked(msg2, NULL);
}
