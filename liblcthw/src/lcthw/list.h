#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

#define FALSE	0
#define TRUE	1
enum ListTypes {
	CHAR_LIST,
	INT_LIST,
	DOUBLE_LIST,
	STRING_LIST
};

struct ListNode;

typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode;

typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
	enum ListTypes listType; // my add
} List;

/** Allocate memory for the list structure */
List *List_create();
/** Set type of the list for dereferencing */
void List_set_type(List *list, enum ListTypes list_type);
/** Get type of the list */
enum ListTypes List_get_type(List *list);
/** Free the allocated memory of list and every its member */
void List_destroy(List *list);
/** Free the values of the each node on the list, while keeping the list and nodes */
void List_clear(List *list);
/** Clears the values and frees the allocated memory for the list */
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

/** Adds an element to the end of the list */
void List_push(List *list, void *value);
/** Removes the last element from the list and returns it */
void *List_pop(List *list);

/** Adds an element to the front of the list */
void List_unshift(List *list, void *value);
/** Removes the first element from the list and returns it */
void *List_shift(List *list);

/** Removes the node from the list */
void *List_remove(List *list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; \
	ListNode *V = NULL; \
	for (V = _node = L->S; _node != NULL; V = _node = _node->M)
	// L - list, s - first, M - next, V - cur


#endif


