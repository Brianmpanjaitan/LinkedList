#include "list.h"
#include <stdio.h>


void free_node(Node* pItem)
{
	pItem->data = NULL;
	pItem = pItem->next;
	//printf("test");
	return;
}


// Bool function to compare items
bool compare(void* pItem, void* comparisonArg)
{
	if (pItem != comparisonArg)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

int main()
{
	//printf("hello\n");
	
	// Create the two lists
	List* l1 = List_create();
	List* l2 = List_create();
	
	// Test Add
	void * one = (void *) 1;
	void * two = (void *) 2;
	void * three = (void *) 3;
	void * four = (void *) 4;
	void * five = (void *) 5;
	void * six = (void *) 6;
	
	List_add(l1, one);
	List_add(l1, two);
	List_add(l1, three);
	List_add(l2, four);
	List_add(l2, five);
	// pList1 = [1,2,3]
	// pList2 = [4,5]
	
	// Test Count
	//printf("%d\n", List_count(l1));
	
	// Test First
	//printf("%p\n", List_first(l1));
	
	// Test Last
	//printf("%p\n", List_last(l1));
	
	// Test Next
	//printf("%p\n", List_next(l1));
	
	// Test Prev
	//printf("%p\n", List_prev(l1));
	
	// Test Curr
	//printf("%p\n", List_curr(l1));
	
	// Test Add
	//List_add(l1, one);
	
	// Test Insert
	//List_insert(l1, one);
	
	// Test Append
	//List_append(l1, four);
	//int count = List_count(l1);
	//printf("%d", count);
	
	// Test Prepend
	//List_prepend(l1, four);
	//int count = List_count(l1);
	//printf("%d", count);
	
	// Test Remove
	//l1->curr = l1->tail;
	//l1->curr = l1->head->next;
	//List_remove(l1);
	//int count = List_count(l1);
	//printf("%d\n", count);
	
	//Test Concat
	//List_concat(l1, l2);
	//printf("%d\n", List_count(l1));
	//printf("%d\n", List_count(l2));
	
	// Test Trim
	//List_trim(l1);
	//printf("%d\n", List_count(l1));
	
	// Test List Free
	//List_free(l1, free_node);
	//printf("%d\n", List_count(l1));
	
	// Test Search
	//List_search(l1, compare, one); // True
	//List_search(l1, compare, six); // False
	
	// Print pList1
	l1->curr = List_first(l1);
	while(l1->curr != NULL)
	{
		printf( "%p\n", l1->curr->data);
		l1->curr = l1->curr->next;
	} 
	return 0;
	
	/*
	// Print pList2
	l2->curr = List_first(l2);
	while(l2->curr != NULL)
	{
		printf( "%p\n", l2->curr->data);
		l2->curr = l2->curr->next;
	} 
	return 0;
	*/
}


