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
    t_list	lst = NULL;
    t_list	tmp = NULL;
    t_list	ret = list;
    lst = malloc (sizeof(struct list));
    lst->data = lroom;
    lst->next = NULL;

    while (list && lroom->cost > list->data->cost)
	list = list->next;

    if (lst)
    {
       	lst = list->next;
       	list->next = lst;
       	lst->next = tmp;
    }
    else
    	ret = lst;

    return ret;
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
