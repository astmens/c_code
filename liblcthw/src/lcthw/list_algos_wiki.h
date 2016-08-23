#ifndef LIST_ALGOS_WIKI_H
#define LIST_ALGOS_WIKI_H

#include "lcthw/list.h"
#include <stddef.h> // size_t



void List_print(List *list, enum ListTypes type);
int List_node_cmp(ListNode *first, ListNode *second, enum ListTypes type);
List *List_create_from_size_tArr(size_t size_tArr[], int size);
List *List_create_from_arr(void *arr, int size, enum ListTypes list_type);
int List_sort_bubble(List *list, enum ListTypes list_type);
void List_swap_w_prev_node(List *list, ListNode *node);
void *List_copy_list(List *listA, List *listB);

/* testing Merge Sort with int array: */
void topDownMergeSortInt(int a[], int b[], int n);
void topDownSplitMergeInt(int a[], int iBegin, int iEnd, int b[]);
void topDownMergeInt(int a[], int iBegin, int iMiddle, int iEnd, int b[]);
void copyArrayInt(int b[], int iBegin, int iEnd, int a[]);

/* adapting Merge Sort with linked list: */
void topDownMergeSortList(List *listA, List *listB, int n);
void topDownSplitMergeList(List *listA, int iBegin, int iEnd, List *listB);
void topDownMergeList(List *listA, int iBegin, int iMiddle, int iEnd, List *listB);
void copyArrayList(List *listB, int iBegin, int iEnd, List *listA);

ListNode *getListNodeAtIndex(List *list, int index);
void setListNodeAtIndexInt(List *list, int index, void *value);

#endif
