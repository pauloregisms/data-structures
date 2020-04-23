#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct Node Node;

struct Node {
	void *value;
	Node *next;
};

struct List {
	Node *first;
	int length;
};

List *List_create() {
	List *list = NULL;

	list = (List*) malloc(sizeof(List));

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}
	
	list->first= NULL;
	list->length = 0;
	
	return list;	
}

int List_delete(List *list) {
	Node *node = NULL; 
	Node *nodeAux = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}
		
	node = list->first;
	
	while (node) {
		nodeAux = node->next;
		free(node);
		node = nodeAux;
	}
	
	free(list);
	list = NULL;

	return 0;
}

int List_insert(List* list, void *value) {
	Node *newNode = NULL;
	
	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -2;
	}
	
	newNode = (Node*) malloc(sizeof(Node));
	
	if (newNode == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -3;
	}
	
	newNode->value = value;
	newNode->next = list->first;
	list->first = newNode;
	list->length++;
	
	return 0;
}

void *List_getFirst(List *list) {

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (list->first == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	return list->first->value;
}

void *List_getLast(List *list) {
	Node *node = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	node = list->first;
	
	while (node->next)
		node = node->next;

	return node->value;
}

void *List_find(List *list, void *value, int (*compare)(void*, void*)) {
	Node *node = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (compare == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	node = list->first;
	
	while (node) {
		if (compare(node->value, value) == 0)
			return node->value;

		node = node->next;
	}

	return NULL;
}

void *List_remove(List* list, void *value, int (*compare)(void*, void*)) {
	Node *node = NULL;
	Node *nodePrevious = NULL;
	void *valueFound = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (compare == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	node = list->first;
	
	while (node) {
		if (compare(node->value, value) == 0) {
			valueFound = node->value;

			if (node == list->first) {
				list->first = node->next;
			}
			else {
				nodePrevious->next = node->next;
			}

			free(node);
			return valueFound;
		}

		nodePrevious = node;
		node = node->next;
	}

	return NULL;
}

int List_getLength(List *list) {

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}

	return list->length;
}

int List_print(List *list, void (*printValue)(void *)) {
	Node *node = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}
	
	if (printValue == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -2;
	}

	node = list->first;

	while (node) {
		printValue(node->value);
		node = node->next;
	}
	
	printf("\n");
}