#include "error.h"

void error_crash(const char *msg) {
  fprintf(stderr, "error crash: %s\n", msg);
  exit(EXIT_FAILURE);
}

void error_warn(const char *msg) { fprintf(stderr, "warning: %s\n", msg); }

// TODO: Save the logs somewhere
void error_log(const char *msg) { fprintf(stderr, "log: %s\n", msg); }
