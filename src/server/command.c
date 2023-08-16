#include "command.h"

Room *cmd__move(move_direction direction, Room *current_room) {
  switch (direction) {
  case NORTH:
    return current_room->north;
  case EAST:
    return current_room->east;
  case SOUTH:
    return current_room->south;
  case WEST:
    return current_room->west;
  }
  return NULL;
}
