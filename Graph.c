#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

typedef struct Node Node;

struct Node {
	void *value;
	List *edges;
};

struct Graph {
	List *nodes;
};

Graph *Graph_create() {
	Graph *graph = (Graph*) malloc(sizeof(Graph));
	assert(graph);
	graph->nodes = List_create();
	return graph;
}

void Graph_delete(Graph *graph) {
	assert(graph);
	List_delete(graph->nodes);
	free(graph);
}

static Node *Node_create(void *value) {
	Node *node;

	assert(value);
	
	node = (Node*) malloc(sizeof(Node));
	assert(node);
	
	node->value = value;
	node->edges = List_create();
	
	return node;
}

void Graph_insert(Graph *graph, void *value) {
	assert(graph);
	List_pushBack(graph->nodes, Node_create(value));
}

void Graph_print(Graph *graph, void (*printValue)(void *)) {
	Node *node;
	void *value;

	assert(graph);
	assert(printValue);

	while (node = List_getNext(graph->nodes)) {
		printValue(node->value);
		printf(":");
		
		while (value = List_getNext(node->edges))
			printValue(value);
		printf("\n");
	}

	printf("\n");
}

static Node *Graph_findNode(Graph *graph, void *value, int (*compare)(void*, void*)) {
	Node *node;

	assert(graph);
	assert(value);
	assert(compare);

	while (node = List_getNext(graph->nodes))
		if (compare(node->value, value) == 0) {
			List_resetIterator(graph->nodes);
			return node;
		}
	
	return NULL;
}

void Graph_createEdge(Graph *graph, void *origin, void *target, int (*compare)(void*, void*)) {
	Node *node;

	assert(graph);
	assert(origin);
	assert(target);
	assert(compare);
	
	node = Graph_findNode(graph, origin, compare);
	assert(node);
	
	List_pushBack(node->edges, target);
}

void Graph_removeEdge(Graph *graph, void *origin, void *target, int (*compare)(void*, void*)) {
	Node *node;

	assert(graph);
	assert(origin);
	assert(target);
	assert(compare);
	
	node = Graph_findNode(graph, origin, compare);
	assert(node);
	
	List_remove(node->edges, target, compare);
}