#include <stdio.h>
#include "list.h"

int check = 0; // Flag for one-time initialization
List* List_create()
{
	if(check == 0)
	{
		// Keep track of available nodes and heads
		freeNode = &nodes[0];
		freeHead = &heads[0];
		// Inspired from : https://www.reddit.com/r/learningprogramming/comments/gnkmr/doing_linked_lists_in_c_without_malloc/
		
		// Initializing freeHead and freeNode
		for(int i = 0; i < LIST_MAX_NUM_HEADS; i++)
		{
			freeHead->next = &heads[i];
			freeHead->next->prev = freeHead;
			freeHead = freeHead->next;
		}
		freeHead->next = NULL;
		for(int j = 0; j < LIST_MAX_NUM_NODES; j++)
		{
			freeNode->next = &nodes[j];
			freeNode->next->prev = freeNode;
			freeNode = freeNode->next;
		}
		freeNode->next = NULL;
		freeHead = &heads[0];
		freeNode = &nodes[0];
		check = 1;
	}
	List* list = freeHead;
	list->head = NULL;
	list->tail = NULL;
	list->curr = NULL;
	freeHead = freeHead->next;
	return list;
}

int List_count(List* pList)
{
	return pList->count;
}

void* List_first(List* pList)
{
	pList->curr = pList->head;
	if (pList->curr == NULL)
	{	
		return NULL;
	}
	return pList->curr;
}

void* List_last(List* pList)
{
	pList->curr = pList->tail;
	if (pList->curr == NULL)
	{
		return NULL;
	}	
	return pList->curr;
}

void* List_next(List* pList)
{
	pList->curr = pList->curr->next;
	if (pList->curr == pList->tail->next)
	{
		return NULL;
	}
	return pList->curr;
}

void* List_prev(List* pList)
{
	pList->curr = pList->curr->prev;
	if (pList->curr == pList->head->prev)
	{
		return NULL;
	}
	return pList->curr;
}

void* List_curr(List* pList)
{
	return pList->curr;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_add(List* pList, void* pItem)
{
	// List is empty
	if (pList->head == NULL && pList->tail == NULL && pList->curr == NULL)
	{
		// Free the head
		pList->head = freeNode;
		freeNode = freeNode->next;
		pList->head->data = pItem;

		// Make head and tail the curr 
		pList->curr = pList->head;
		pList->tail = pList->head;
		pList->tail->next = NULL;

		pList->count++;
		return 0;
	}
	
	// curr is before the start of pList. Add to the start
	// Don't include curr == head because if true, we add after head
	if (pList->curr->next == pList->head)
	{
		// Free curr since its the start
		pList->curr = freeNode;
		freeNode = freeNode->next;
		
		// Make curr the head
		pList->head->prev = pList->curr;
		pList->head = pList->curr;
		pList->curr->data = pItem;
		pList->head->prev = NULL;
		pList->count++;
		return 0;
	}
	// curr is beyond the end of pList or is the tail.
	if (pList->curr->prev == pList->tail || pList->curr == pList->tail)
	{
		// Free tail->next
		pList->tail->next = freeNode;
		freeNode = freeNode->next;
		
		// Make tail the free node
		pList->tail = pList->tail->next;
		pList->tail->prev = pList->curr;
		pList->tail->data = pItem;
		// Make curr the tail and point to NULL
		pList->curr = pList->tail;
		pList->tail->next = NULL;
		pList->count++;
		return 0;
	}
	// Satically allocated array is full or fails
	if (freeNode == NULL || freeNode->next == NULL)
	{
		return -1;
	}
	
	else // Add pItem after curr
	{
		// Left side of doubly linked node
		freeNode->prev = pList->curr->next;
		pList->curr->next = freeNode;
		// New curr
		pList->curr = freeNode;
		
		pList->curr->next = pList->curr->prev;
		pList->curr->prev = pList->curr->next->prev;
		pList->curr->next->prev = pList->curr;
		pList->curr->data = pItem;
		
		freeNode = freeNode->next;
		pList->count++;
		return 0;
	}
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert(List* pList, void* pItem)
{
	// List is empty
	if (pList->head == NULL && pList->tail == NULL && pList->curr == NULL)
	{
		// Free the head
		pList->head = freeNode;
		pList->head->data = pItem;
		
		// Make head and tail the curr 
		pList->curr = pList->head;
		pList->tail = pList->head;
		pList->tail->next = NULL;
		
		freeNode = freeNode->next;
		pList->count++;
		return 0;
	}
	// curr is before the start of pList or is the head. 
	if (pList->curr->next == pList->head || pList->curr == pList->head)
	{
		// Free curr since its the start
		pList->curr = freeNode;
		freeNode = freeNode->next;
		
		// Make head curr since it is already at the start
		pList->head->prev = pList->curr;
		pList->curr->next = pList->head;
		pList->head = pList->curr;
		
		pList->curr->data = pItem;
		pList->count++;
		return 0;
	}
	// curr is beyond the end of pList. Add to the end
	// Don't include curr == tail because if true, we add before tail
	if (pList->curr->prev == pList->tail)
	{
		pList->curr = freeNode;
		freeNode = freeNode->next;
		
		pList->tail->next = pList->curr;
		pList->curr->prev = pList->tail;

		pList->tail = pList->curr;
		pList->tail->next = NULL;
		
		pList->tail->data = pItem;
		pList->count++;
		return 0;
	}
	// Satically allocated array is full or fails
	if (freeNode == NULL || freeNode->next == NULL)
	{
		return -1;
	}
	else
	{
		// Link to the left
		freeNode->prev = pList->curr->prev;
		pList->curr->prev = freeNode;
		// Link to the right
		pList->curr->prev->next = pList->curr; // freeNode->next = curr
		pList->curr = freeNode;
		freeNode = freeNode->next;
		pList->curr->prev->next = pList->curr;
		
		pList->curr->data = pItem;
		pList->count++;
		//printf( "%p\n", pList->tail->data);
		//printf("hello\n");
		return 0;
	}
}

int List_append(List* pList, void* pItem)
{
	// Satically allocated array is full
	if (freeNode == NULL || freeNode->next == NULL)
	{
		return -1;
	}
	// Make a new node after tail
	pList->tail->next = freeNode;
	freeNode = freeNode->next;
	
	// Make the new node the tail
	pList->tail = pList->tail->next;
	pList->tail->data = pItem;
	pList->curr = pList->tail;
	
	pList->tail->next = NULL;
	pList->count++;
	return 0;
}

// Add pItem to front of list and makes it curr
int List_prepend(List* pList, void* pItem)
{
	// Satically allocated array is full
	if (freeNode == NULL || freeNode->next == NULL)
	{
		return -1;
	}
	pList->curr = freeNode;
	freeNode = freeNode->next;
	
	pList->head->prev = pList->curr;
	pList->curr->next = pList->head;
	pList->head = pList->curr;

	pList->head->data = pItem;
	pList->head->prev = NULL;
	pList->count++;
	return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList)
{
	// If curr pointer is before or beyond the list
	if (pList->head->prev == pList->curr || pList->tail->next == pList->curr)
	{
		return NULL;
	}
	// Empty List
	if (pList->head == NULL && pList->tail == NULL && pList->curr == NULL)
	{
		return NULL;
	}
	// Removed item is head
	if (pList->curr == pList->head)
	{
		freeNode = pList->curr;
		pList->head = pList->head->next;
		pList->head->prev = NULL;
		pList->count--;
		return freeNode->data;
	}
	// Removed item is tail
	if (pList->curr == pList->tail)
	{
		freeNode = pList->curr;
		pList->tail = pList->tail->prev;

		pList->tail->next = NULL;
		pList->curr = pList->tail;
		pList->count--;
		return freeNode->data;
	}
	// Make the nodes before and after the one to be removed point at each other
	freeNode = pList->curr;
	
	pList->curr->prev->next = pList->curr->next;
	pList->curr->next->prev = pList->curr->prev;
	
	pList->count--;
	return freeNode->data;
}

void List_concat(List* pList1, List* pList2)
{
	pList1->tail->next = pList2->head;
	pList2->head->prev = pList1->tail;
	// Set new tail
	pList1->tail = pList2->tail;
	pList1->tail->next = NULL;

	// Free pList2
	pList2->head = NULL;
	pList2->tail = NULL;
	pList2->curr = NULL;
	pList2->count = 0;
	
	// Make pList2 available for future use
	freeHead->prev = pList2;
	pList2->next = freeHead;
	freeHead = freeHead->prev;
	
	pList1->count += pList2->count;
	return;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
void List_free(List* pList, FREE_FN pItemFreeFn)
{
	pList->curr = List_first(pList);
	while(pList->curr != pList->tail->next)
	{
		(*pItemFreeFn)(pList->curr); // Free the node
		pList->curr = pList->curr->next;
	}
	// Make pList available for future
	freeHead->prev = pList;
	freeHead->prev->next = freeHead;
	freeHead = freeHead->prev;
	
	pList->head = NULL;
	pList->tail = NULL;
	pList->curr = NULL;
	pList->count = 0;
	pList = NULL; 
	
	return;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList)
{
	// Check if pList is empty
	if (pList->head == NULL && pList->tail == NULL)
	{
		printf("empty\n");
		return NULL;
	}
	freeNode = pList->tail; // Save trimmed node
	pList->tail = pList->tail->prev;
	pList->tail->next = NULL;
	
	pList->curr = pList->tail;
	pList->count--;
	//printf("%p\n", freeNode->data);
	return freeNode->data;
}

/* 
Search pList, starting at the current item, until the end is reached or a match is found. In this context, a match is determined by the comparator parameter. This parameter is a pointer to a routine that takes as its first argument an item pointer, and as its second argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 

If a match is found, the current pointer is left at the matched item and the pointer to that item is returned. If no match is found, the current pointer is left beyond the end of the list and a NULL pointer is returned.

If the current pointer is before the start of the pList, then start searching from the first node in the list (if any).
*/
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
	pList->curr = pList->head;
	while(pList->curr != pList->tail->next) // Loop through the list
	{
		bool comp = (*pComparator)(pList->curr->data, pComparisonArg);
		if (comp)
		{
			//printf("true\n");
			return pList->curr;
		}
		pList->curr = pList->curr->next;
	}
	//printf("false\n");
	return NULL;
}
