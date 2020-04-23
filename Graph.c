#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct Node Node;
typedef struct Edge Edge;

struct Edge {
	void *value;
	Edge *next;
	Node *target;
};

struct Node {
	void *value;
	Node *next;
	Edge *firstEdge;
};

struct Graph {
	Node *firstNode;
	int length;
};

Graph *Graph_create() {
	Graph *graph = NULL;

	graph = (Graph*) malloc(sizeof(Graph));
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}
	
	graph->length = 0;
	graph->firstNode = NULL;

	return graph;
}

int  Graph_getLength(Graph *graph) {
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}
	
	return graph->length;
}

int Graph_insert(Graph *graph, void *value) {
	Node *newNode = NULL;

	if (graph == NULL) {
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
	newNode->next = graph->firstNode;
	
	graph->firstNode = newNode;
	graph->length++;

	return 0;
}

int Graph_delete(Graph *graph) {
	Node *node = NULL;

	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}

	free(graph);
	graph = NULL;

	return 0;
}


void  Graph_print(Graph *graph, void printValue(void*)) {
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-1);
	}
	
	if (printValue == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		exit(-2);
	}

}

int Graph_createEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);
int Graph_removeEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);