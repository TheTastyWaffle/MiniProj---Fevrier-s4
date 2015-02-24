#ifndef DUNGEON
#define DUNGEON

typedef struct dungeon	*t_dungeon;
typedef struct lroom	*t_lroom;
typedef struct room	*t_room;
 
struct lroom //som
{
  int		som;
  float 	cost;
  t_room	succ, pred;
};
 
struct room //adj
{
  float		cost;
  int		vsom;
  t_room	next;
};
 
struct dungeon
{
  int		order;
  t_lroom	lroom[1];
};

t_dungeon create_dungeon (int);
void create_room(t_dungeon, int, int, float);
void create_cost(t_dungeon, int, float);
int  create_path(t_dungeon, int *, float *);
void dijkstra(t_dungeon, int, int *, float *);

#endif
