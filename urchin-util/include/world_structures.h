#pragma once
// Make world structures accessible to both server and client

// Define moveable directions
typedef enum { NORTH, EAST, SOUTH, WEST } move_direction;

// Define what a room is.
typedef struct room {
  char* name;
  char* description;
  struct room* north;
  struct room* east;
  struct room* south;
  struct room* west;
} Room;
