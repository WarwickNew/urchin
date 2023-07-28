#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err__crash(const char *msg);

void err__warn(const char *msg);

void err__log(const char *msg);
