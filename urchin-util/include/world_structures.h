#pragma once
// Make world structures accessible to both server and client

// Define moveable directions
// TODO: eventually move over to a hash table so players can move through
// exits defined in the room description like hatch, crack, door, etc.
typedef enum { NORTH, EAST, SOUTH, WEST } move_direction;

// Define what a room is.
typedef struct Room Room;
struct Room {
  char *name;
  char *description;
  Room *north;
  Room *east;
  Room *south;
  Room *west;
};

typedef struct player {
  Room *current_location;
} Player;
