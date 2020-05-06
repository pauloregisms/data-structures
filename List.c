#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Container.h"
#include "List.h"

typedef struct Node Node;

struct List {
	Node *first;
	Node *last;
	Node *iterator;
	int length;
};

struct Node { 
	void *value;
	Node *next;
	Node *prev;
};

void *List_getNext(List *list) {
	Node *node;

	assert(list);

	if (list->iterator)
		list->iterator = list->iterator->next;
	else
		list->iterator = list->first;
	
	if (list->iterator)
		return list->iterator->value;
	else
		return NULL;
}

int List_hasNext(List *list) {
	assert(list);
	if (list->iterator)
		return list->iterator->next != NULL;
	else
		return 0;
}

void List_resetIterator(List *list) {
	assert(list);
	list->iterator = NULL;
}

static Node *Node_create(void *value) {
	Node *newNode = NULL;

	assert(value);

	newNode = (Node*) malloc(sizeof(Node));
	assert(newNode);

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

List *List_create() {
	List *list = NULL;

	list = (List*) malloc(sizeof(List));
	assert(list);

	list->first = NULL;
	list->last = NULL;
	list->length = 0;
	list->iterator = NULL;

	return list;
}

void List_delete(List *list) {
	Node *node = NULL;
	Node *tempNode = NULL;

	assert(list);
	node = list->first;
	
	while (node) {
		tempNode = node->next;
		free(node);
		node = tempNode;
	}

	free(list);
}

void List_pushFront(List *list, void *value) {
	Node *newNode = NULL;

	assert(list);
	assert(value);

	newNode = Node_create(value);

	if (list->first == NULL) {
		list->first = newNode;
		list->last = newNode;
	}
	else {
		list->first->prev = newNode;
		newNode->next = list->first;
		list->first = newNode;
	}

	list->length++;
}


void List_pushBack(List *list, void *value) {
	Node *newNode = NULL;

	assert(list);
	assert(value);

	newNode = Node_create(value);

	if (list->last == NULL) {
		list->first = newNode;
		list->last = newNode;
	}
	else {
		list->last->next = newNode;
		newNode->prev = list->last;
		list->last = newNode;
	}

	list->length++;
}

void *List_popFront(List *list) {
	Node *tempNode = NULL;
	void *value = NULL;

	assert(list);

	if (list->first) {
		tempNode = list->first;
		list->first = tempNode->next;
		list->first->prev = NULL;

		value = tempNode->value;
		free(tempNode);

		list->length--;
	}

	return value;
}

void *List_popBack(List *list) {
	Node *tempNode = NULL;
	void *value = NULL;

	assert(list);

	tempNode = list->last;
	list->last = tempNode->prev;
	list->last->next = NULL;

	value = tempNode->value;
	free(tempNode);

	list->length--;

	return value;
}

void *List_getFront(List *list) {
	
	assert(list);

	if (list->first != NULL)
		return list->first->value;
	else
		return NULL;
}

void *List_getBack(List *list) {
	
	assert(list);
	
	if (list->last != NULL) 
		return list->last->value;
	else
		return NULL;
}

int List_getLength(List *list) {
	
	assert(list);

	return list->length;
}

void *List_find(List *list, void *value, int (*compare)(void *, void *)) {
	Node *node = NULL;
	
	assert(list);
	assert(value);
	assert(compare);

	node = list->first;
	
	while (node) {
		if (compare(node->value, value) == 0) {
			return node->value;	
		}
		node = node->next;
	}

	return NULL;
}

void *List_remove(List *list, void *value, int (*compare)(void *, void *)) {
	Node *node = NULL;
	void *removedValue = NULL;

	assert(list);
	assert(value);
	assert(compare);

	node = list->first;
	
	while (node) {
		if (compare(node->value, value) == 0) {
			removedValue = node->value;

			/*   (L)
			    /   \ 
			    \   /
			   <-[X]->  */
			if (node == list->first && node == list->last) {
				list->first = NULL;
				list->last = NULL;
				free(node);
				return removedValue;
			}

			/*     ____(L)____
			      /           \ 
			      \           /
		           <-[X]-> ... <-[ ]->  */
			if (node == list->first && node != list->last) {
				list->first = node->next;
				node->next->prev = NULL;
				free(node);
				return removedValue;
			}

			/*     ____(L)____
			      /           \ 
			      \           /
		           <-[ ]-> ... <-[X]->  */
			if (node != list->first && node == list->last) {
				list->last = node->prev;
				node->prev->next = NULL;
				free(node);
				return removedValue;
			}

			/*     __________(L)__________
			      /                       \ 
			      \                       /
		           <-[ ]-> ... <-[X]-> ... <-[ ]-> */
			if (node != list->first && node != list->last) {
				node->prev->next = node->next;
				free(node);
				return removedValue;
			}
		}
		node = node->next;
	}

	return NULL;
}

void List_print(List *list, void (*printValue)(void*)) {
	Node *node = NULL;

	assert(list);
	assert(printValue);

	node = list->first;

	while (node) {
		printValue(node->value);
		node = node->next;
	}
	
	printf("\n");
}

List *List_map(List *list, void *value, void* (*callback)(void*, void*)) {
	Node *node = NULL;
	List *listMap = NULL;

	assert(list);
	assert(callback);

	listMap = List_create();
	node = list->first;

	while (node) {
		List_pushBack(listMap, callback(node->value, value));
		node = node->next;
	}

	return listMap;
}

