#pragma once

#include "world.h"
#include <error.h>

typedef enum { NORTH, EAST, SOUTH, WEST } move_directions;

// Returns pointer to new room based on current room and direction If room
// doesn't exist returns NULL
Room *cmd__move(move_directions direction, Room *current_room);