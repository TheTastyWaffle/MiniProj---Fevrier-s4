#ifndef LIST
#define LIST
#include <stdlib.h>
#include <unistd.h>
#include "dungeon.h"

typedef struct list *t_list;
int is_empty(t_list);
t_list add(t_lroom, t_list);
int check_val(t_lroom, t_list);
t_lroom min(t_list*);

#endif 
