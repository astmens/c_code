#include "minunit.h"
#include "lcthw/list.h"
#include <lcthw/list_algos_wiki.h>

#include <stdio.h>
#include <assert.h>
#include "lcthw/dbg.h"

char listArr0[] = {'a', 'b', 'c', 'd', 'e'}; 	// define as 'char' CHAR_LIST; TODO: make it flexible
int listArr1[] = {5, 1, 4, 2, 8}; 				// define as 'int' INT_LIST; TODO: make it flexible
double listArr2[] = {5.0, 1.0, 4.0, 2.0, 8.0}; 	// define as 'double' DOUBLE_LIST; TODO: make it flexible
char *listArr3[] = {"5_", "10<", "(>4<)", "2-)", "8"}; 	// define as 'string' STRING_LIST; TODO: make it flexible

// int list_size0 = sizeof listArr0 / sizeof *listArr0;  // works only with non-void pointers
// int list_size1 = sizeof listArr1 / sizeof *listArr1;
// int list_size2 = sizeof listArr2 / sizeof *listArr2;
// int list_size3 = sizeof listArr3 / sizeof *listArr3;
#define SIZE_OF_LIST(X) sizeof X / sizeof *X 

/* 

b tests/list_algos_wiki_tests.c:23
b src/lcthw/list_algos_wiki.c:43

*/

void *list_algos_test(){ // break list_algos_test
//	mu_assert(listArr, "There must be an array. ");
	
//	int pnt_size = (sizeof *listArr) >> 2; // 
//	int pnt_size2 = (sizeof *listArr2) >> 2; // 
//	int pnt_size3 = (sizeof *listArr3) >> 2; // 
//	int list_size = sizeof listArr / sizeof *listArr; // works only with non-void pointers
	assert(sizeof(void*) == sizeof(long)); // will store pointer addresses as long array, but long is platform specific...
	
	// setup list, its size and type:
	/// void *listArr = listArr3;						// SET the list pointer
	int list_size = SIZE_OF_LIST(listArr3); // works only with non-void pointers
	enum List_types list_type = STRING_LIST;			// SET the type of list used

	long *longListArr = (long *)malloc(list_size*sizeof(long));
	int i = 0;
	
	for(i = 0; i < list_size; i++){
		longListArr[i] = (long )&(listArr3[i]);
	}
	
	/// printf("listArr: %p, listArr1: %p, longListArr: %lx \n", &listArr, &listArr1, longListArr[0]);
	/// debug("%p @ ListArr, [0]: %x \n", &listArr, *(int*)listArr);
	
	/// List *list = List_create_from_arr(listArr, list_size, list_type); // TODO: make it flexible
	List *list2 = List_create_from_longArr(longListArr, list_size, list_type);
	
	mu_assert(list2, "List not created. ");
	
	free(longListArr);
	return NULL;
}

void *all_algos_tests(){
	mu_suite_start();
	
	mu_run_test(list_algos_test);
	
	printf("Tests over!");
	
	return NULL;
}

RUN_TESTS(all_algos_tests);
