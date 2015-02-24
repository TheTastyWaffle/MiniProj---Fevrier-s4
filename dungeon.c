#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include "dungeon.h"
#include "list.h"

t_dungeon create_dungeon(int order){
  t_dungeon dg = malloc(sizeof(int)+sizeof(t_lroom)*order);
  dg->order = order;
  for(int i=0; i<order; i++)
        {
                dg->lroom[i] = malloc(sizeof(t_lroom));
                dg->lroom[i]->som = i;
                dg->lroom[i]->succ = NULL;
                dg->lroom[i]->pred = NULL;
        }
  return dg;
}

void create_room(t_dungeon dg, int s, int d, float cost){
  t_room r = malloc(sizeof(t_room));
  r->cost = cost;
  r->vsom = d;
  r->next = dg->lroom[s]->succ;
  dg->lroom[s]->succ = r;
  r = malloc(sizeof(t_room));
  r->cost = cost;
  r->vsom = s;
  r->next = dg->lroom[d]->pred;
  dg->lroom[d]->pred = r;
}


void create_cost(t_dungeon dg, int som, float cost)
{
    t_lroom ps = NULL;
    if ((ps = dg->lroom[som]))
        ps->cost = cost;
}



int next_room(t_dungeon dg, t_lroom ps, int s)
{
    t_room           pa = NULL;
    pa = dg->lroom[ps->som]->succ;
    while (pa)
    {
        if (pa->vsom == s)
            return pa->cost + ps->cost;
        pa = pa->next;
    }    
    return 0;
}

int create_path(t_dungeon dg, int *costs, float *health)
{
    t_lroom	ps = NULL;
    int		n = 0;
    float	cost;
    ps = dg->lroom[*costs];
    do
    {
        if (!(cost = next_room(dg, ps, costs[n+1])))
            return 0;
        *health -= cost;
        if (*health < 1)
            return -1;
        n++;
        ps = dg->lroom[costs[n]];
    } while (costs[n+1]);
    n++;
    return n;
}

void dijkstra (t_dungeon dg, int src, int *f, float *dist)
{
    t_lroom	ps = NULL;
    t_room	pa = NULL;
    t_list	op = NULL;
    f[0] = -1;
    int sa;
    for (sa = 1; sa < dg->order; sa++)
    {
        f[sa] = 0;
        dist[sa] = INFINITY;
    }

    f[src] = src;
    dist[src] = 0;
    op = add(dg->lroom[src], NULL);
    do
    {
        ps = min(&op);
        src = ps->som;
        pa = dg->lroom[src]->succ;
        while (pa)
        {
            sa = pa->vsom;
            if (dist[sa] > dist[src] + pa->cost + ps->cost)
            {
                dist[sa] = dist[src] + pa->cost + ps->cost;
                f[sa] = src;
                if (!check_val(dg->lroom[pa->vsom], op))
                    op = add(dg->lroom[pa->vsom], op);
            }
            pa = pa->next;
        }
    }while (!is_empty(op));
}
