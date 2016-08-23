#include "minunit.h"
#include "lcthw/list.h"
#include "lcthw/list_algos_wiki.h"

#include <stdio.h>
#include <assert.h>
#include "lcthw/dbg.h"
/* 
valgrind --leak-check=full -v ./tests/list_algos_wiki_tests

gdb ./tests/list_algos_wiki_tests

b tests/list_algos_wiki_tests.c:23
b src/lcthw/list_algos_wiki.c:43

*/

char listArr0[] = {'a', 'b', 'c', 'd', 'e'}; 	// define as 'char' CHAR_LIST; TODO: make it flexible
int listArr1[] = {10, 50, 1, 4, 2, 8}; 				// define as 'int' INT_LIST; TODO: make it flexible
double listArr2[] = {5.0, 1.0, 4.0, 2.0, 8.0}; 	// define as 'double' DOUBLE_LIST; TODO: make it flexible
char *listArr3[] = {"5_", "10<", "(>4<)", "2-)", "8"}; 	// define as 'string' STRING_LIST; TODO: make it flexible


// define name of the list and its type
#define LIST_NAME listArr1
#define LIST_TYPE INT_LIST		// needed for dereferencing: printing and comparing
#define LIST_TYPE_CAST (LIST_TYPE *) // TODO: possible idea for improvement

#define SIZE_OF_LIST(X) sizeof X / sizeof *X // works only with non-void pointers

// some quick and dirty globals:
size_t *size_tListArr;
//enum List_types list_type;
int list_size;

/** Make linked list from array of int's. Array pointer and its length must be provided.*/
List *intArrayToLinkedList(int *a, size_t list_size){
	check(a != NULL, "Size must be positive");
	check(list_size > 0, "Size must be positive");
	
	unsigned int i = 0;
	void *val = NULL;
	
	List *list = List_create();
	check(list, "List not created. ");
	List_set_type(list, INT_LIST);
	for(i = 0; i < list_size; i++) {
		val = (&a[i]); // store addresses instead of values; dereferencing!!! (type specific!)
		List_push(list, val);
	}
	return list;

error:
	return NULL;
}


List *create_list_from_array(){
	check(sizeof(void*) <= sizeof(size_t), "Check if 'void*' can be stored as 'size_t'"); // will store pointer addresses as size_t array, but size_t is platform specific...
	
	// setup list's size and type:
	list_size = SIZE_OF_LIST(LIST_NAME); // works only with non-void pointers
	//list_type = LIST_TYPE;			// SET the type of list used
	size_tListArr = (size_t *)calloc(1, list_size*sizeof(size_t)); // global!
	int i = 0;
	
	for(i = 0; i < list_size; i++){
		size_tListArr[i] = (size_t )&(LIST_NAME[i]);
	}
	List *list = List_create_from_size_tArr(size_tListArr, list_size);
	//List_print(list, list->list_type);
	check(list, "List not created. ");
	list->listType = LIST_TYPE;
	return list;
	
error:
	return NULL;
}

void free_list(List *list){
	List_destroy(list);	// only allocation done was for list, but not it's values; clear not needed!
	free(size_tListArr);
	return;
}

void *list_algos_test(){ // break list_algos_test

	List *list = create_list_from_array();
	mu_assert(list, "List not created. ");
	/*
	List_destroy(list);
	
	printf("Second time of list:\n");
	list = List_create_from_size_tArr(size_tListArr, list_size, list_type);	
	mu_assert(list, "List not created. ");
	*/
	
	debug("Swap test %d\n", 1);
	List_swap_w_prev_node(list, list->first->next);
	// List_print(list, list_type); // visual check...
	debug("Bubble sort test %d\n", 1);
	int times = List_sort_bubble(list, list->listType);
	debug("Pass times: %d\n", times);
	// List_print(list, list_type);	// visual check
	//printf("p->p: %x, p: %x, n->p: %x, p->n:%x, n: %x, n->n:%x\n",
	//	list->first->prev, list->first, list->first->next->prev, list->first->next, list->first->next, list->first->next->next);
	
	/// make the test fail by swaping first with second, which are different:
	// List_swap_w_prev_node(list, list->first->next);
	
	/// test if sorted: (by trying to sort again)
	times = List_sort_bubble(list, list->listType);
	mu_assert(times == 1, "List not sorted!");
	List_print(list, list->listType);	// visual check

	
	/// Clean-up:
	free_list(list);
	//List_clear_destroy(list); // core dumped... because it trys to free the pointer from stack?
	//List_destroy(list);	// only allocation done was for list, but not it's values; clear not needed!
	//free(size_tListArr);
	return NULL;
//error:
//	return "Failed this test!";
}

void *arrayMeregeIntTest(){
	int a[] = {38, 27, 43, 3, 9, 82, 10};
	int b[] = {38, 27, 43, 3, 9, 82, 10};	// temp 
	int n = SIZE_OF_LIST(a);
	int k = 0;
	topDownMergeSortInt(a, b, n);
	for (k = 0; k < n; k++){
		printf("a[%d]=%d ", k, a[k]);
	}
	printf("\n");

	return NULL;

}

void *listMergeIntTest(){

	int a[] = {38, 27, 43, 3, 9, 82, 10, 85, 74, 41, 21};
	int b[] = { 0,  0,  0, 0, 0,  0,  0,  0,  0,  0,  0};	// temp 
	int n = SIZE_OF_LIST(a);
	List *list = intArrayToLinkedList(a, n);
	List *listTmp = intArrayToLinkedList(b, n);
	
	
	List_print(listTmp, INT_LIST);
	//topDownMergeSortInt(a, b, n);	
	topDownMergeSortList(list, listTmp, n);
	printf("sorted list: \n");
	List_print(list, INT_LIST);
	List_print(listTmp, INT_LIST);
	
	List_destroy(list);	// only allocation done was for list, but not it's values; clear not needed!
	List_destroy(listTmp);	// only allocation done was for list, but not it's values; clear not needed!
	return NULL;
}

void *all_algos_tests(){
	mu_suite_start();
	
	mu_run_test(list_algos_test);
	
	mu_run_test(arrayMeregeIntTest);
	
	mu_run_test(listMergeIntTest);
	
	printf("Tests over!\n");
	
	return NULL;
}

RUN_TESTS(all_algos_tests);

