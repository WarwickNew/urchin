#pragma once
#include "error.h"
#include <bits/stdint-uintn.h>

// One method to fill the buffer from a connection
void read_from_sock(uint8_t *recvbuf, unsigned bufsize, int *sockfd);

// One method to see how much data is in a buffer to unpack
size_t get_msg_size_in_buffer(unsigned max_length, uint8_t *out);

// Send msg buffer to the server, crash on fail.
void msg__send_msgbuf(int *con_sockfd, uint8_t *msgbuf, size_t msgbuf_size);
