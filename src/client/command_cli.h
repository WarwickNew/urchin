#pragma once

#include "world_structures.h"
#include <../src/protobuf_gen/commands.pb-c.h>

//FIX: Create malloced command struct to be edited before being sent
Command *cmd__create();

// Add movement direction to command struct
void cmd__add_move(Command* command, move_direction direction);

// Free command struct when we're done with it
void cmd__destroy(Command* command);
