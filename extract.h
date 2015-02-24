#ifndef EXTRACT_H
#define EXTRACT_H

#include "dungeon.h"

int open_for_reading(char*);
t_dungeon dungeon_from_file(char*);
void create_room(t_dungeon, int, int, float);
void create_cost(t_dungeon, int, float);
int next_room(t_dungeon, t_lroom, int);
int create_path(t_dungeon, int*, float*);
void dijkstra(t_dungeon, int, int*, float*);

#endif
