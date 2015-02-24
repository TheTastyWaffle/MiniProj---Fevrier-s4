#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dungeon.h"
#include "extract.h"

void cost (t_dungeon dg, char *line)
{
	int	i, curr=0;
	int 	*lst;
	float	health=0;
	char	*path = NULL;
	path = malloc(100);
	lst = malloc (sizeof(int)*100);
	sscanf(line, "COST %f [%s]\n",&health, path);
	for (i=0;1 < sscanf (path, "%d;%s",&curr, path); i++)
		lst[i] = curr;
	sscanf (path, "%d;%s",&curr, path);
	lst[i] = curr;
	lst[i+1] = 0;  
	i = create_path(dg, lst, &health);
	if (0 < i)
		printf ("(%g,%d)\n", health, i);
	else if ( 0 == i)
		printf ("NP\n");
	else
		printf ("DEAD\n");
	free (lst);
	free (path); 
}

void display_path(int *f, int src, int dst, int *n)
{
	if (src != dst)
	{
		(*n)++;
		display_path(f+1, src, f[dst], n);
		(*n)--;
	}
	if (*n > 0)
		printf("%d;", dst);
	else
		printf("%d", dst);
}

void path(t_dungeon dg, char *line)
{
	int             src=0, dst=0;
	int             *f, n=0;
	float           health=0;
	float           *curr;
	sscanf(line, "PATH %f %d %d",&health, &src, &dst);
	f = malloc (sizeof(int)*dg->order);
	curr = malloc (sizeof(float)*dg->order);
	dijkstra(dg, src, f, curr);
	printf("[");
	display_path(f, src, dst, &n);
	printf("]\n");
	free (f);
	free (curr);
}

int main (int argc, char **argv)
{
	t_dungeon	dg = NULL;
	char		*curr;
	if (argc < 1)
		return -1;
	dg = dungeon_from_file(argv[1]);
	curr = malloc (100);
	while (fgets(curr,100, stdin))
	{
		if (curr[0] == 'C' && curr[1] == 'O' && curr[2] == 'S' && curr[3] == 'T')
			cost(dg, curr);
		else if (curr[0] == 'P' && curr[1] == 'A' && curr[2] == 'T' && curr[3] == 'H')
			path(dg, curr);
		else
		{
			printf("error in arguments\nTry PATH int [int;...;int] or COST int int\n");
			return 1;
		}
	}
	free(curr);
	free (dg);
	return 0;
}
