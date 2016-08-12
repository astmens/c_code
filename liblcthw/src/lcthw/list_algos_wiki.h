#ifndef LIST_ALGOS_WIKI_H
#define LIST_ALGOS_WIKI_H

#include "lcthw/list.h"

enum List_types {
	CHAR_LIST,
	INT_LIST,
	DOUBLE_LIST,
	STRING_LIST
};

void List_print(List *list, enum List_types type);
List *List_create_from_longArr(long longArr[], int size, enum List_types list_type);
List *List_create_from_arr(void *arr, int size, enum List_types list_type);
void *List_sort_bubble(List *list);
void List_swap_w_prev_node(List *list, ListNode *node);

#endif
