#include "lcthw/list_algos_wiki.h"
#include "lcthw/dbg.h" // check(), ...

#include <stdio.h> // printf

/** Print the list to console/std */
void List_print(List *list, enum ListTypes type){// TODO: make it flexible?
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
int List_node_cmp(ListNode *first, ListNode *second, enum ListTypes type){// TODO: make it flexible?
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

/** Made to solve problem of passing string array as void pointer. Instead address of each element of list is stored as size_t array. Additionally size/length of size_t pointer array must be passed, as well as type of data stored in each pointer address*/
List *List_create_from_size_tArr(size_t size_tArr[], int size){
	List *list = List_create();
	int i = 0;
	void *val = NULL;
	check(size > 0 && size_tArr != NULL, "Size must be positive");
	
	//printf("%p @ ListArr, [0 of %d]: %lx \n", &size_tArr, size, *size_tArr);
	for(i = 0; i < size; i++) {
		val = (void*)(size_tArr[i]);
		//debug("val[%d]: %lx with %s \n", i, (size_t)val, *(char **)val); // causes mystic seg fault when wrong type used
		List_push(list, val);
	}
	return list;

error:
	return NULL;
}

/*
int List_sort_merge(List *list, enum ListTypes list_type){
	int i = 0;
	check(list, "Must have a list");
	return i;
error:
	return -1;
}
*/

/** Sorts the list using (unoptimized) bubble sort algorythm. Returns number of passes through the list. Returns 1 if already sorted. */
int List_sort_bubble(List *list, enum ListTypes list_type){
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
		//debug("Sorting: %d\n", i);
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
			//debug("%dof%d, p: %lx, c:%lx n:%lx ", k, n, (size_t)cur->prev, (size_t)cur, (size_t)cur->next); //src/lcthw/list_algos_wiki.c:123:4: warning: format '%lx' expects argument of type 'long unsigned int', but argument 8 has type 'unsigned int'[-Wformat]
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
	//debug("Swapping nodes %lx and %lx\n", (size_t)node->prev, (size_t)node);
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

/** Copy values (pointer addresses) from listA to listB */
void *List_copy_list(List *listA, List *listB){
	check(listA != NULL && listB != NULL, "List_copy_list: input list NULL");
	int countA = listA->count;
	int countB = listB->count;
	check(countA == countB, "List size differs!");
	ListNode *nodeA = listA->first;
	ListNode *nodeB = listB->first;
	for ( ; nodeA != NULL; nodeA = nodeA->next){
		nodeB->value = nodeA->value;
		
		// 
		nodeB = nodeB->next;
	} 
		
	return NULL;
error:
	return NULL;
}

void topDownMergeSortInt(int a[], int b[], int n){
	topDownSplitMergeInt(a, 0, n, b);
	return;
}

void topDownSplitMergeInt(int a[], int iBegin, int iEnd, int b[]){
	
	if(iEnd - iBegin < 2) { return; } // if run size == 1, consider it sorted;
	//recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain
	int iMiddle = (iEnd + iBegin) / 2;
	topDownSplitMergeInt(a, iBegin, iMiddle, b);
	topDownSplitMergeInt(a, iMiddle, iEnd, b);
	topDownMergeInt(a, iBegin, iMiddle, iEnd, b);
	copyArrayInt(b, iBegin, iEnd, a);
	
	return;
}

void topDownMergeInt(int a[], int iBegin, int iMiddle, int iEnd, int b[]){
	int i = iBegin;
	int j = iMiddle;
	int k = 0;
	// while there are elements in the left or right runs...
	for (k = iBegin; k < iEnd; k++){
		// if leftrun head exists and is <= existing right run head.
		if( i < iMiddle && (j >= iEnd || a[i] <= a[j])) {
			b[k] = a[i];
			i++;
		}
		else {
			b[k] = a[j];
			j++;
		}
	}

	return;
}

void copyArrayInt(int b[], int iBegin, int iEnd, int a[]){
	int i = 0;
	for(i = iBegin; i < iEnd; i++){
		a[i] = b[i];
	}

	return;
}

/** get ListNode at given index number from list. Indexing starts at 0. */
ListNode *getListNodeAtIndex(List *list, int index){
	check(list !=NULL && index < list->count, "Check inputs for ListNodeAtIndex");
	int i = 0;
	ListNode *curr = list->first;
	for(i = 0; i < index; i++){
		curr = curr->next;
	}
	//printf("0x%0.4x @ %d \n", *(int *)(curr->value), index);
	return curr;
	
error:
	return NULL;
}

void setListNodeAtIndexInt(List *list, int index, void *value){
	
	ListNode *node = getListNodeAtIndex(list, index);
	check(node != NULL, "Node not returned!");
	node->value = value;
	return;
error:
	return;
}


void topDownMergeSortList(List *listA, List *listB, int n){
	topDownSplitMergeList(listA, 0, n, listB);
	return;
}

/** listA - list to sort; listB - temp list; iBegin - starting index of list node (incl.); iEnd - ending index of list node (NON-incl) */
void topDownSplitMergeList(List *listA, int iBegin, int iEnd, List *listB){
	if(iEnd - iBegin < 2) { return; } // if run size == 1, consider it sorted;
	//recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain
	int iMiddle = ((iEnd + iBegin) / 2);
	if ((iEnd - iBegin) % 2 == 1) { iMiddle++; } // if list is odd!!!
	topDownSplitMergeList(listA, iBegin, iMiddle, listB);
	topDownSplitMergeList(listA, iMiddle, iEnd, listB);
	topDownMergeList(listA, iBegin, iMiddle, iEnd, listB);
	copyArrayList(listB, iBegin, iEnd, listA);
	
	return;
}

void topDownMergeList(List *listA, int iBegin, int iMiddle, int iEnd, List *listB){
	int i = iBegin;
	int j = iMiddle;
	int k = iBegin;
	ListNode *iNode = getListNodeAtIndex(listA, i);
	ListNode *jNode = getListNodeAtIndex(listA, j);
	ListNode *kNode = getListNodeAtIndex(listB, k);
	// while there are elements in the left or right runs...
	for (k = iBegin; k < iEnd; k++){
		// if leftrun head exists and is <= existing right run head.
		if( i < iMiddle && (j >= iEnd || List_node_cmp(jNode, iNode, INT_LIST))) { // iNode <= jNode
			//kNode = getListNodeAtIndex(listB, k);
			//setListNodeAtIndexInt(listTmp, k, iNode->value);
			kNode->value = iNode->value;
			//b[k] = a[i];
			i++;
			iNode = iNode->next;
		}
		else {
			kNode->value = jNode->value;
			//b[k] = a[j];
			j++;
			jNode = jNode->next;
		}
		kNode = kNode->next;
	}

	return;
}
/** Copy list values from listB to listA from index iBegin to iEnd-1 */
void copyArrayList(List *listB, int iBegin, int iEnd, List *listA){
	int i = iBegin;
	ListNode *listANode = getListNodeAtIndex(listA, i);
	ListNode *listBNode = getListNodeAtIndex(listB, i);
	
	for(i = iBegin; i < iEnd; i++){
		listANode->value = listBNode->value;
		//a[i] = b[i];
		listANode = listANode->next;
		listBNode = listBNode->next;
	}

	return;
}

