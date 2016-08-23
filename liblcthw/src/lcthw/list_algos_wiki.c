#include "lcthw/list_algos_wiki.h"
#include "lcthw/dbg.h" // check(), ...

#include <stdio.h> // printf

void List_print(List *list, enum List_types type){// TODO: make it flexible?
	check(list, "Check list before printing.");
	debug("List_print:%c", ' ');
	LIST_FOREACH(list, first, next, cur){
		check(cur->value, "Value must point somewhere");
		switch(type){
			case CHAR_LIST:
				printf("0x%.4x ", *(char *)(cur->value)); 
				break;
			case INT_LIST:
				printf("0x%.4x ", *(int *)(cur->value));
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
	
error:
	return;
}

/** Compares values of the two nodes. Returns 1 if second is "smaller" */
int List_node_cmp(ListNode *first, ListNode *second, enum List_types type){// TODO: make it flexible?
	check(first && second && first->value && second->value, "Check pointers before dereferencing!");
		int result = 0;
		switch(type){
			case CHAR_LIST:
				if ( (*(char *)(first->value)) > (*(char *)(second->value)) ){ result = 1; }
				break;
			case INT_LIST:
				if ( (*(int *)(first->value)) > (*(int *)(second->value)) ){ result = 1; }
				break;
			case DOUBLE_LIST:
				if ( (*(double *)(first->value)) > (*(double *)(second->value)) ){ result = 1; }
				break;
			case STRING_LIST:
				debug("comparing: %s vs %s", *(char **)(first->value), *(char **)(second->value)); // value of pointer of array of char's
				if ( strcmp( *(char **)(first->value), *(char **)(second->value) ) > 0 ){ result = 1; } 
				// the first character that does not match has a greater value in ptr1 than in ptr2
				break;
			default:
				debug("Unknown type.\n");
				return -1;
		}
		
	return result;

error:
	return -1;
}

/** Made to solve problem of passing string array as void pointer. Instead address of each element of list is stored as long array. Additionally size of long pointer must be passed, as well as type of data stored in each pointer address*/
List *List_create_from_longArr(long longArr[], int size){
	List *list = List_create();
	int i = 0;
	void *val = NULL;
	check(size > 0 && longArr != NULL, "Size must be positive");
	
	//printf("%p @ ListArr, [0 of %d]: %lx \n", &longArr, size, *longArr);
	for(i = 0; i < size; i++) {
		val = (void*)(longArr[i]);
		//debug("val[%d]: %lx with %s \n", i, (long)val, *(char **)val); // causes mystic seg fault when wrong type used
		List_push(list, val);
	}
	return list;

error:
	return NULL;
}


/** Sorts the list using (unoptimized) bubble sort algorythm. Returns number of passes through the list. Returns 1 if already sorted. */
int List_sort_bubble(List *list, enum List_types list_type){
	check(list && list->first, "Must have at leat one element");
	int n = list->count; // TODO: improve security, and add checks...
	int i = 0;
	int k = 0;
	char sorted = FALSE;
	//ListNode *pre = list->first;
	ListNode *cur = list->first;
	ListNode *nex = cur->next;
	if(cur->next == NULL) { return 1;} // one element list - its sorted!
	
	

	while(!sorted && i <= n){
		debug("Sorting: %d\n", i);
		sorted = TRUE;
		k = 0;
		cur = list->first;
		nex = cur->next;
	if(cur->next == NULL) { return 1;} // one element list - its sorted!
		//LIST_FOREACH(list, first, next, cur){
		for(k = 1; (k < n); k++){
			cur = nex;
			nex = cur->next;
			if (cur == NULL) { printf("something not as expected"); return -1;}
			debug("%dof%d, p: %lx, c:%lx n:%lx ", k, n, (long)cur->prev, (long)cur, (long)cur->next);
			// if there is something to compare and swap with previous is needed:
			if( cur && cur->prev && List_node_cmp(cur->prev, cur, list_type)){
				List_swap_w_prev_node(list, cur);
				//_node = cur->prev;
				sorted = FALSE;
			}
			if(k > n*2 + 1) {
				debug("Something got wrong...\n");
				return -1;
			}
		}
		i++;
	}
	if(i > n) { i = -1;} // something failed, because it should take no more than n (outer) loops to sort the list
	
	return i;

error:
	return -1;
}

void List_swap_w_prev_node(List *list, ListNode *node){
	ListNode *prev = node->prev;	// node - current; prev - previous
	check(prev && node, "Need elements to swap. ");
	debug("Swapping nodes %lx and %lx\n", (long)node->prev, (long)node);
	//printf("p->p: %x, p: %x, n->p: %x, p->n:%x, n: %x, n->n:%x\n",
	//	prev->prev, prev, node->prev, prev->next, node, node->next);
	
	// prev node is first
	if(prev == list->first) { // List_first(list)
		list->first = node; // update to new first
	}
	else {
		prev->prev->next = node;	// update node before swapped nodes pointing to them
	}
	// this node is last
	if (node == list->last) {
		list->last = prev;
	}
	else {
		node->next->prev = prev; // update node after swapped nodes pointing back to them
	}
	
	node->prev = prev->prev;
	prev->next = node->next;
	node->next = prev;
	prev->prev = node;
	
	//printf("p->p: %x, p: %x, n->p: %x, p->n:%x, n: %x, n->n:%x\n",
	//	prev->prev, prev, node->prev, prev->next, node, node->next);
	return;
	
error:
	return;
}

List *List_copy_list(List *list){
	
	return list;
}

