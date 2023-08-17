#include "command_cli.h"
#include <stdlib.h>
#include <string.h>

Command *cmd__create() {
  Command initialCommand = COMMAND__INIT;
  Command *command = malloc(sizeof(initialCommand));
  memcpy(&initialCommand, command, sizeof(initialCommand));
  return command;
}

void cmd__add_move(Command *command, move_direction direction) {
//  command->has_move_direction = 1;
  command->move_direction = direction;
}

void cmd__destroy(Command *command) { free(command); }
