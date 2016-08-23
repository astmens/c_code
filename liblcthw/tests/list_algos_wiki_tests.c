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
#define LIST_NAME listArr2
#define LIST_TYPE DOUBLE_LIST		// needed for dereferencing: printing and comparing
#define LIST_TYPE_CAST (LIST_TYPE *) // TODO: possible idea for improvement

#define SIZE_OF_LIST(X) sizeof X / sizeof *X // works only with non-void pointers

// some quick and dirty globals:
long *longListArr;
enum List_types list_type;
int list_size;

List *create_list_from_array(){
	check(sizeof(void*) <= sizeof(long), "Check if 'void*' can be stored as 'long'"); // will store pointer addreses as long array, but long is platform specific...
	
	// setup list's size and type:
	list_size = SIZE_OF_LIST(LIST_NAME); // works only with non-void pointers
	list_type = LIST_TYPE;			// SET the type of list used
	longListArr = (long *)calloc(1, list_size*sizeof(long)); // global!
	int i = 0;
	
	for(i = 0; i < list_size; i++){
		longListArr[i] = (long )&(LIST_NAME[i]);
	}
	List *list = List_create_from_longArr(longListArr, list_size);
	//List_print(list, list_type);
	check(list, "List not created. ");
	
	return list;
	
error:
	return NULL;
}

void free_list(List *list){
	List_destroy(list);	// only allocation done was for list, but not it's values; clear not needed!
	free(longListArr);
	return;
}

void *list_algos_test(){ // break list_algos_test

	List *list = create_list_from_array();
	mu_assert(list, "List not created. ");
	/*
	List_destroy(list);
	
	printf("Second time of list:\n");
	list = List_create_from_longArr(longListArr, list_size, list_type);	
	mu_assert(list, "List not created. ");
	*/
	
	debug("Swap test %d\n", 1);
	List_swap_w_prev_node(list, list->first->next);
	// List_print(list, list_type); // visual check...
	debug("Bubble sort test %d\n", 1);
	int times = List_sort_bubble(list, list_type);
	debug("Pass times: %d\n", times);
	// List_print(list, list_type);	// visual check
	//printf("p->p: %x, p: %x, n->p: %x, p->n:%x, n: %x, n->n:%x\n",
	//	list->first->prev, list->first, list->first->next->prev, list->first->next, list->first->next, list->first->next->next);
	
	/// make the test fail by swaping first with second, which are different:
	// List_swap_w_prev_node(list, list->first->next);
	
	/// test if sorted: (by trying to sort again)
	times = List_sort_bubble(list, list_type);
	mu_assert(times == 1, "List not sorted!");
	List_print(list, list_type);	// visual check

	
	/// Clean-up:
	free_list(list);
	//List_clear_destroy(list); // core dumped... because it trys to free the pointer from stack?
	//List_destroy(list);	// only allocation done was for list, but not it's values; clear not needed!
	//free(longListArr);
	return NULL;
//error:
//	return "Failed this test!";
}

void *all_algos_tests(){
	mu_suite_start();
	
	mu_run_test(list_algos_test);
	
	printf("Tests over!");
	
	return NULL;
}

RUN_TESTS(all_algos_tests);

