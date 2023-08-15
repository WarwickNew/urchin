#pragma once

#define WORLD_SIZE 100

#include <math.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

// Define what a room is.
typedef struct room {
  char* name;
  char* description;
  struct room* north;
  struct room* east;
  struct room* south;
  struct room* west;
} Room;

// Creator and destructor for the world
Room* wrld__create();
void wrld__destroy(Room* rooms);
