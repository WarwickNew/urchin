#include "world.h"

Room* wrld__create() {
  Room *rooms = malloc(WORLD_SIZE * sizeof(*rooms));

  for (unsigned int i = 0; i < WORLD_SIZE; i++) {
    char strbuf[(int)log10(WORLD_SIZE) + 1 + 80];
    snprintf(strbuf, sizeof(strbuf), "Room name: %d",i);

    rooms[i].name = strbuf;
    rooms[i].description = strbuf;
    rooms[i].north = NULL;
    rooms[i].east = NULL;
    rooms[i].south = NULL;
    rooms[i].west = NULL;
  }

  return rooms;
}

void wrld__destroy(Room* rooms){
  free(rooms);
}
