#include "world.h"

Room* wrld__create() {
  Room *rooms = malloc(WORLD_SIZE * sizeof(*rooms));

  for (unsigned int i = 0; i < WORLD_SIZE; ++i) {
    //char strbuf[(int)log10(WORLD_SIZE) + 1 + 12];
    char* strbuf = malloc(sizeof (char) * ((int)log10(WORLD_SIZE) + 1 + 12));
    snprintf(strbuf, sizeof (char) * ((int)log10(WORLD_SIZE) + 1 + 12), "Room name: %d",i+1);
    rooms[i].name = strbuf;
    rooms[i].description = strbuf;
    rooms[i].north = NULL;
    if (i>0) // Link to previous room if exists
      rooms[i].east = &rooms[i-1];
    rooms[i].south = NULL;
    if (i<WORLD_SIZE-1) // Link to next room if exists
      rooms[i].west = &rooms[i-1];
  }

  return rooms;
}

void wrld__destroy(Room* rooms){
  for (unsigned int i = 0; i < WORLD_SIZE; ++i) {
    free(rooms[i].name);
    free(rooms[i].description);
  }
  free(rooms);
}
