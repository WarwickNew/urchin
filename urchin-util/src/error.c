#include "error.h"
#include "protobuf_gen/amessage.pb-c.h"
#define MAX_MSG_SIZE 1024

void err__crash(const char *msg) {
  fprintf(stderr, "error crash: %s\n", msg);
  exit(EXIT_FAILURE);
}

void err__warn(const char *msg) { fprintf(stderr, "warning: %s\n", msg); }

// TODO: Save the logs somewhere
void err__log(const char *msg) { fprintf(stderr, "log: %s\n", msg); }
