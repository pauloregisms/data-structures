#include <stdlib.h>
#include <stdio.h>
#include "List.h"

typedef struct Node Node;

struct List {
	Node *first;
	Node *last;
	int length;
};

struct Node { 
	void *value;
	Node *next;
	Node *prev;
};

static Node *Node_create(void *value) {
	Node *newNode = NULL;

	if (value == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	newNode = (Node*) malloc(sizeof(Node));
	
	if (newNode == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

List *List_create() {
	List *list = NULL;

	list = (List*) malloc(sizeof(List));
	
	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	list->first = NULL;
	list->last = NULL;
	list->length = 0;

	return list;
}

void List_delete(List *list) {
	Node *node = NULL;
	Node *tempNode = NULL;

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}
	
	if (value == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	if (value == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	tempNode = list->last;
	list->last = tempNode->prev;
	list->last->next = NULL;

	value = tempNode->value;
	free(tempNode);

	list->length--;

	return value;
}

void *List_getFront(List *list) {
	
	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	if (list->first != NULL)
		return list->first->value;
	else
		return NULL;
}

void *List_getBack(List *list) {
	
	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}
	
	if (list->last != NULL) 
		return list->last->value;
	else
		return NULL;
}

int List_getLength(List *list) {
	
	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	return list->length;
}


void *List_find(List *list, void *value, int (*compare)(void *, void *)) {
	Node *node = NULL;
	
	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	node = list->first;
	
	while (node) {
		if (compare(node->value, value) == 0) {
			removedValue = node->value;
			free(node);
			list->length--;
			break;		
		}
		node = node->next;
	}

	return removedValue;
}

void List_print(List *list, void (*printValue)(void*)) {
	Node *node = NULL;

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	if (printValue == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

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

	if (list == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	if (callback == NULL) { 
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	listMap = List_create();
	node = list->first;

	while (node) {
		List_pushBack(listMap, callback(node->value, value));
		node = node->next;
	}

	return listMap;
}