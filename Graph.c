#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct Node Node;
typedef struct Edge Edge;

struct Edge {
	Node *origin;
	Node *target;
};

struct Node {
	void *value;
	List *edgeList;
};

struct Graph {
	List *nodes;
	int length;
};

Graph *Graph_create(int (*compare)(void*, void*)) {
	Graph *graph = NULL;
	
	if (compare == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	graph = (Graph*) malloc(sizeof(Graph));
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}
	
	graph->length = 0;
	graph->nodes = List_create(compare);
	
	if (graph->nodes == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	return graph;
}

int Graph_delete(Graph *graph) {
	Node *node = NULL;

	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}

	if (graph->nodes == NULL) {
		free(graph);
		return 0;
	}

	if (List_getLength(graph->nodes) == 0) {
		List_delete(graph->nodes);
		free(graph);
		return 0;
	}

	node = (Node*) List_remove(graph->nodes, List_getFirst(graph->nodes));

	while (node) {
		if (node->edgeList != NULL)
			List_delete(node->edgeList);
		
		free(node);
		
		if (List_getLength(graph->nodes) == 0)
			break;
		else
			node = (Node*) List_remove(graph->nodes, List_getFirst(graph->nodes));
	}

	free(graph);
	graph = NULL;

	return 0;
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
	newNode->edgeList

	if (List_insert(graph->nodes, value) != 0) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -3;
	}
	else
		graph->length++;

	return 0;
}

void *Graph_find(Graph *graph, void *value) {
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	return List_find(graph->nodes, value);
}

void *Graph_remove(Graph *graph, void *value) {
	Node *node = NULL;
	void *valueFound = NULL;

	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__); 
		return NULL;
	}

	if (value == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return NULL;
	}

	valueFound = List_remove(graph->nodes, value);
	
	if (valueFound != NULL)
		graph->length--;
	
	return valueFound;
}

int  Graph_getLength(Graph *graph) {
	
	if (graph == NULL) {
		printf("Error: %s, %d\n", __FILE__, __LINE__);
		return -1;
	}
	
	return graph->length;
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

	List_print(graph->nodes, printValue);
}

int Graph_createEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);
int Graph_removeEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);