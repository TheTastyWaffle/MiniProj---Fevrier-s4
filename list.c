#include <stdlib.h>
#include <unistd.h>
#include "list.h"

struct list{
	t_lroom	data;
	t_list      next;
};

int is_empty(t_list list){
	if(list)
		return 0;
	else
		return 1;
}

t_list add (t_lroom lroom, t_list list){
	t_list	new = NULL, tmp = NULL, keep;
	keep = list;
	new = malloc (sizeof(struct list));
	new->data = lroom;
	new->next = NULL;
	for (;list && lroom->cost > list->data->cost; list = list->next);
	if (list)
	{
		tmp = list->next;
		list->next = new;
		new->next = tmp;
	}
	else
		keep = new;
	return keep;
}

int check_val(t_lroom lroom, t_list list){
	t_list tmp = list;

	while(tmp)
	{
		if (tmp->data == lroom)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

t_lroom min (t_list *list)
{
	t_lroom	lroom;
	t_list	tmp;
	lroom = (*list)->data;
	tmp = *list;
	*list = (*list)->next;
	free (tmp);
	return lroom;
}
