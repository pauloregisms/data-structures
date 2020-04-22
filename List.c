#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct Node Node;

struct Node {
	void *value;
	Node *next;
	Node *prev;
};

struct List {
	Node *first;
	int length;
	int (*compare)(void*, void*);
};

List *List_create(int (*comparator)(void*, void*)) {
	List *list = NULL;

	if (comparator == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}
	
	list = (List*) malloc(sizeof(List));

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}
	
	list->first= NULL;
	list->length = 0;
	list->compare = comparator;
	
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

static void List_swapValues(Node *node_1, Node *node_2) {
	void *value = NULL;
	
	if (node_1 == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}

	if (node_2 == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-2);
	}

	node_1->value;
	node_1->value = node_2->value;
	node_2->value = value;
}

int List_insert(List* list, void *value) {
	Node *node = NULL;
	
	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -2;
	}
	
	node = (Node*) malloc(sizeof(Node));
	
	if (node == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -3;
	}
	
	node->value = value;
	node->next = list->first;
	
	if (list->first)
		list->first->prev = node;
	
	list->first = node;
	list->length++;

	while (node->next) {
		if (list->compare(node->value, node->next->value) > 0)
			List_swapValues(node, node->next);
		else
			break;
		
		node = node->next;
	}
	
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

void *List_find(List *list, void *value) {
	Node *node = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	node = list->first;
	
	while (node) {
		if (list->compare(node->value, value) == 0)
			return node->value;

		node = node->next;
	}

	return NULL;
}

void *List_remove(List* list, void *value) {
	Node *node = NULL;
	Node *nodeAux = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (list->first == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	node = list->first;
	
	while (node) {
		if (list->compare(node->value, value) == 0) {
			// case 1: (L)->[x]->NULL
			// case 2: (L)->[x]->[ ]->NULL
			if (node == list->first) {
				list->first = node->next;
				if (node->next)
					node->next->prev = NULL;
				list->length--;
				return node->value;
			}
			// case 3: (L)->[ ]->[x]->NULL
			// case 4: (L)->[ ]->[x]->[ ]->NULL
			else {
				node->prev->next = node->next;
				list->length--;
				return node->value;
			}
		}
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

void List_print(List *list, void (*printValue)(void *)) {
	Node *node = NULL;

	if (list == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}
	
	if (printValue == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-2);
	}

	node = list->first;

	while (node) {
		printValue(node->value);
		node = node->next;
	}
	
	printf("\n");
}