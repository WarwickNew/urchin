#pragma once
#include "error.h"
#include <bits/stdint-uintn.h>

void msg__read_from_socket(int *sockfd, uint8_t *msgbuf, unsigned bufsize);

size_t get_msg_size_in_buffer(unsigned max_length, uint8_t *out);
