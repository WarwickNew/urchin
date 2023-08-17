#pragma once

#include "command_internal.h"
#include "world.h"
#include <error.h>
#include <message.h>
#include <world_structures.h>

// Will process a command given a player to execute it as
void cmd__recv_proc_cmd(Player *player, Command *command);

// Update room pointer based on move direction
void cmd__move_direction(move_direction direction, Room *current_room);
