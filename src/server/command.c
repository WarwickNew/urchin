#include "command.h"

Room *cmd__check_move(Room *current_room, Room *to_room) {
  if (current_room == NULL || to_room == NULL)
    return current_room;

  return to_room;
};

// Update room based on move direction
void cmd__move_direction(move_direction direction, Room *current_room) {
  if (current_room == NULL) {
    err__warn("Cannot move from current_room as room is NULL");
  }

  switch (direction) {
  case NORTH:
    current_room = cmd__check_move(current_room, current_room->north);
    break;
  case EAST:
    current_room = cmd__check_move(current_room, current_room->east);
    break;
  case SOUTH:
    current_room = cmd__check_move(current_room, current_room->south);
    break;
  case WEST:
    current_room = cmd__check_move(current_room, current_room->west);
  }
}

void cmd__process_cmd(Player *player, Command *command) {
  if (command->has_move_direction) {
    move_direction dir = {command->move_direction};
    cmd__move_direction(dir, player->current_location);
  }
  command__free_unpacked(command, NULL);
}
