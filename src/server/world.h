#pragma once

#define WORLD_SIZE 100

#include <math.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

#include <world_structures.h>


// Creator and destructor for the world
Room* wrld__create();
void wrld__destroy(Room* rooms);
