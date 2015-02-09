#ifndef DUNGEON_H
#define DUNGEON_H

struct room {
  int cost;
  room* next;
}

struct dungeon {
  int order;
  room[]* rooms;
}

#endif 
