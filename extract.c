#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "extract.h"

int open_for_reading(char *path)
{
	int	fd;
	fd = open (path, O_RDONLY);
	return fd;
}

void get_ints (char *str, size_t s, int **datat)
{
	size_t                  size, i, j, k, l;
	char                    *tmp, *nb;
	int                         *datas;
	datas = *datat;
	size = strlen(str) - 1;
	for (i = 0; str[i] != ':'; i++);
	i += 2;
	tmp = malloc (size - i);
	j = i;
	for (; i < size; i++) 
		tmp [i - j] = str[i];
	i = 0;
	for (j = 0; j < s; j++)
	{
		datas [j] = -1;
		k = i;
		l = i;
		for (; i < size && tmp[i] != ' '; i++);
		nb = malloc (i);
		for (; k < i; k++) nb[k-l] = tmp[k];
		datas[j] = atoi (nb);
		free (nb);
		i++;
	}
	free (tmp);
}

int get_charact (char *ph, int *s1, float *c, int *s2)
{
	int	*datas;
	float	cost;
	datas = malloc (sizeof(int) * 3);
	if (ph[0] == 'R')
	{
		get_ints(ph, 1, &datas);
		*s1 = datas[0];
		*s2 = datas[2];
		*c = (cost = datas [1]);
		return 1;
	}
	else if (ph[0] == 'M')
	{
		get_ints(ph, 2, &datas);
		*s1 = datas[0];
		*s2 = datas[2];
		*c = (cost = datas [1]);
		return 2;
	}
	else if (ph[0] == 'B')
	{
		get_ints(ph, 2, &datas);
		*s1 = datas[0];
		*s2 = datas[2];
		*c = (cost = datas [1]);
		return 3;
	}
	else if (ph[0] == 'D')
	{
		get_ints(ph, 1, &datas);
		*s1 = datas[0];
		*s2 = datas[2];
		*c = (cost = datas [1]);
		return 4;
	}
	else if (ph[0] == 'A')
	{
		if (ph[3] == 'S')
			return 5;
		get_ints (ph, 3, &datas);
		*s1 = datas[0];
		*s2 = datas[2];
		*c = (cost = datas [1]);
		return 6;
	}
	else
		return -1;
}

t_dungeon dungeon_from_file(char *path)
{
	int		fd, ret;
	int		s1,s2;
	float		c;
	t_dungeon	dungeon = NULL;
	char line [20];
	fd = open_for_reading(path);
	do
	{
		char tmp = '\0';
		int i = 0;
		while (read (fd, &tmp, 1))
		{
			line[i] = tmp;
			i++;
			if (tmp == '\n')
				break;
		}
		line[i]='\0';
		ret = get_charact (line, &s1, &c, &s2);
		switch (ret)
		{
			case 1 : dungeon = create_dungeon(s1+1);
				 break;

			case 2 : create_cost(dungeon, s1, c);
				 break;

			case 3 : create_cost(dungeon, s1, c*(-1));
				 break;

			case 4 : create_cost(dungeon, s1, +INFINITY);
				 break;

			case 6 : create_room(dungeon, s1, s2, c);
				 break;

			case 5 : break;
		}
	}while (line[0] != '\0');
	close (fd);
	return dungeon;
}
