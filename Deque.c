#include <stdlib.h>
#include <stdio.h>
#include "Deque.h"

typedef struct Deque_Node Deque_Node;

struct Deque {
	Deque_Node *first;
	Deque_Node *last;
	int length;
};

struct Deque_Node { 
	void *value;
	Deque_Node *next;
	Deque_Node *prev;
};

Deque *Deque_create() {
	Deque *deque = NULL;

	deque = (Deque*) malloc(sizeof(Deque));
	if (deque== NULL) return NULL;

	deque->first = NULL;
	deque->last = NULL;
	deque->length = 0;

	return deque;
}

int Deque_delete(Deque *deque) {
	Deque_Node *node = NULL, *tempNode = NULL;

	if (deque == NULL) return -1;

	node = deque->first;
	while (node) {
		tempNode = node->next;
		free(node);
		node = tempNode;
	}

	free(deque);
	return 0;
}

int Deque_pushFront(Deque *deque, void *value) {
	Deque_Node *newNode = NULL;

	if (deque == NULL) return -1;
	if (value == NULL) return -2;

	newNode = (Deque_Node*) malloc(sizeof(Deque_Node));
	if (newNode == NULL) return -3;

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	if (deque->first == NULL) {
		deque->first = newNode;
		deque->last = newNode;
	}
	else {
		deque->first->prev = newNode;
		newNode->next = deque->first;
		deque->first = newNode;
	}

	deque->length++;

	return 0;
}


int Deque_pushBack(Deque *deque, void *value) {
	Deque_Node *newNode = NULL;

	if (deque == NULL) return -1;
	if (value == NULL) return -2;

	newNode = (Deque_Node*) malloc(sizeof(Deque_Node));
	if (newNode == NULL) return -3;

	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = NULL;

	if (deque->last == NULL) {
		deque->first = newNode;
		deque->last = newNode;
	}
	else {
		deque->last->next = newNode;
		newNode->prev = deque->last;
		deque->last = newNode;
	}

	deque->length++;

	return 0;
}

void *Deque_popFront(Deque *deque) {
	Deque_Node *tempNode = NULL;
	void *value = NULL;

	if (deque == NULL) return NULL;

	tempNode = deque->first;
	deque->first = tempNode->next;
	deque->first->prev = NULL;

	value = tempNode->value;
	free(tempNode);

	deque->length--;

	return value;
}

void *Deque_popBack(Deque *deque) {
	Deque_Node *tempNode = NULL;
	void *value = NULL;

	if (deque == NULL) return NULL;

	tempNode = deque->last;
	deque->last = tempNode->prev;
	deque->last->next = NULL;

	value = tempNode->value;
	free(tempNode);

	deque->length--;

	return value;
}

void *Deque_getFront(Deque *deque) {
	if (deque == NULL) return NULL;
	if (deque->first == NULL) return NULL;

	return deque->first->value;
}

void *Deque_getBack(Deque *deque) {
	if (deque == NULL) return NULL;
	if (deque->last == NULL) return NULL;

	return deque->last->value;
}

int   Deque_getLength(Deque *deque) {
	if (deque == NULL) return -1;

	return deque->length;
}


void Deque_print(Deque *deque, void (*printValue)(void*)) {
	Deque_Node *node = deque->first;
	int i = 1;

	printf("Deque(%d):\n", deque->length);
	printf("  (front)\n");
	while (node) {
		printf("   %03d [", i);
		printValue(node->value);
		printf("]\n");
		node = node->next;
		i++;
	}
	printf("  (back)\n");
	printf("end\n");
}