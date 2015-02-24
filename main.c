#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "dungeon.h"
#include "extract.h"

void cost (t_dungeon dg, char *line)
{
	int             test=0, *lst, i;
	float           health=0;
	char            *chem = NULL;
	chem = malloc(100);
	lst = malloc (sizeof(int)*100);
	sscanf(line, "COST %f [%s]\n",&health, chem);

	for (i=0;1 < sscanf (chem, "%d;%s",&test, chem); i++)
		lst[i] = test;

	sscanf (chem, "%d;%s",&test, chem);
	lst[i] = test;
	lst[i+1] = 0;
	printf("%d\n", lst[i-1]);  
	i = create_path(dg, lst, &health);
	if (0 < i)
		printf ("%g - %d\n", health, i);
	else if ( 0 == i)
		printf ("NP\n");
	else
		printf ("DEAD\n");
	free (lst);
	free (chem); 
}

void display_path(int *pere, int src, int dest, int *cpt)
{
	if (src != dest)
	{
		(*cpt)++;
		display_path(pere, src, pere[dest], cpt);
		(*cpt)--;
	}
	if (*cpt > 0)
		printf("%d;", dest);
	else
		printf("%d", dest);
}

void path(t_dungeon dg, char *phrase)
{
	int             deb=0, fin=0;
	int             *pere, cpt = 0;
	float           vies=0;
	float           *dist;
	sscanf(phrase, "PATH %f %d %d",&vies, &deb, &fin);
	pere = malloc (sizeof(int)*dg->order);
	dist = malloc (sizeof(float)*dg->order);
	dijkstra(dg, deb, pere, dist);
	printf("[");
	display_path(pere, deb, fin, &cpt);
	printf("]\n");
	free (pere);
	free (dist);
}

int main(int argc, char **argv)
{
	t_dungeon	dg = NULL;
	char		*curr;

	if (argc < 1)
		return -1;
	
	dg = dungeon_from_file(argv[1]);
	curr = malloc (100);
	while (fgets(curr,100, stdin))
	{
		if (curr[0] == 'C')
			cost(dg, curr);
		else if (curr[0] == 'P')
			path(dg, curr);
		else
			break;
	}
	free (path);
	free (dg);
	return 0;
}
