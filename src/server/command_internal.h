#pragma once

#include <world_structures.h>

// Check that room is valid before moving
Room *cmd__check_move(Room *current_room, Room *to_room);
