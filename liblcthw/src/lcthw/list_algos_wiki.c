#include "lcthw/list_algos_wiki.h"
#include <lcthw/dbg.h> // check(), ...

#include <stdio.h> // printf

void List_print(List *list, enum List_types type){// TODO: make it flexible?
	debug("List_print:%c", ' ');
	LIST_FOREACH(list, first, next, cur){
		switch(type){
			case CHAR_LIST:
				printf("0x%x ", *(char *)(cur->value)); 
				printf("Char type chosen. \n");
				break;
			case INT_LIST:
				printf("0x%x ", *(int *)(cur->value));
				break;
			case DOUBLE_LIST:
				printf("%f ", *(double *)(cur->value)); // value of double pointer
				break;
			case STRING_LIST:
				printf("%s ", *(char **)(cur->value)); // value of pointer of array of char's
				break;
			default:
				printf("Unknown type.\n");
				return;
		}
		
	}
	printf("\n");
	return;
}

/** Made to solve problem of passing string array as void pointer. Instead address of each element of list is stored as long array. Additionally size of long pointer must be passed, as well as type of data stored in each pointer address*/
List *List_create_from_longArr(long longArr[], int size, enum List_types list_type){
	List *list = List_create();
	int i = 0;
	void *val = NULL;
	check(size > 0 && longArr != NULL, "Size must be positive");
	
	//printf("%p @ ListArr, [0 of %d]: %lx \n", &longArr, size, *longArr);
	for(i = 0; i < size; i++) {
		val = (void*)(longArr[i]);
		debug("val[%d]: %lx with %s \n", i, (long)val, *(char **)val);
		List_push(list, val);
	}
	
	List_print(list, list_type);
	return list;

error:
	return NULL;
}

/** Creating list from pointer and type passed as a pointer operation exercise. */
List *List_create_from_arr(void *arr, int size, enum List_types list_type){
	check(size > 0 && arr != NULL, "Size must be positive");
	List *list = List_create();
	int i = 0;
	void *val = NULL;
	
	printf("%p @ ListArr, [0]: %x \n", &arr, *(int*)arr);
	for(i = 0; i < size; i++) {
		// pointer operations according to type chosen:
		switch(list_type){	// TODO: make it flexible
			case CHAR_LIST:
				val = (char *)(arr) + i*1;		
				char valc = *(char*)val;
				printf("val: %p, val2: %c \n", &val, valc);
				printf("Char type chosen. \n");
				break;
			case INT_LIST:
				val = (int *)(arr) + i*1;
				int vali = *(int*)val;
				printf("val: %p, val2: %x \n", &val, vali);
				break;
			case DOUBLE_LIST:
				val = (double *)(arr) + i*1;
				double vald = *(double*)val;
				printf("val: %p, val2: %f \n", &val, vald);
				printf("Double type chosen. \n");
				break;
			/*
			case STRING_LIST: // unsolved problem of determining string size from void* pointer...
				val = (char *)(arr) + i*1;
				char vals = *(char*)val;
				printf("val: %p, val2: %s \n", &val, vals);
				printf("String type chosen. \n");
				break;
			*/
			default:
				printf("Unknown type.\n");
				return NULL;
		}
		
		List_push(list, val);
	}
	
	List_print(list, list_type);
	return list;

error:
	return NULL;
}


void *List_sort_bubble(List *list){
	int n = list->count; // TODO: improve security, and add checks...
	debug("%d ", n);
	n++;
	
	return NULL;
}

void List_swap_w_prev_node(List *list, ListNode *node){
	ListNode *prev = node->prev;
	check(prev && node, "Need elements to swap with. ");
	
	// prev node is first
	if(prev == List_first(list)) {
		list->first = node; // update to new first
	}
	// this node is last
	if (node == List_last(list)) {
		list->last = prev;
	}
	// swap:
	node->prev = prev->prev;
	prev->next = node->next;
	node->next = prev;
	prev->prev = node;
	
	return;
	
error:
	return;
}

