#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

typedef struct Graph Graph;
typedef struct Node Node;

struct Node {
	void *value;
	List *edges;
};

struct Graph {
	int length;
	List *nodes;
};

Graph *Graph_create() {
	Graph *graph = NULL;

	graph = (Graph*) malloc(sizeof(Graph));
	
	assert(graph != NULL);
	
	graph->length = 0;
	graph->nodes = List_create();

	return graph;
}

void Graph_insertNode(Graph *graph, void *value) {
	Node *newNode = NULL;

	assert(graph != NULL);
	assert(value != NULL);

	newNode = (Node*) malloc(sizeof(Node));
	assert(newNode != NULL);

	newNode->value = value;
	newNode->edges = List_create();

	List_pushFront(graph->nodes, newNode);
}

void *Graph_removeNode(Graph *graph, void *value, int (*compare)(void *, void *)) {
	Node *node;
	void *foundValue;
	int count = 0;

	assert(graph != NULL);
	assert(value != NULL);
	assert(compare != NULL);

	node = (Node*) List_popFront(graph->nodes);

	while (count < List_getLength(graph->nodes)) {

		if (compare(node->value, value) == 0) {
			return node->value;
		}

		List_pushBack(graph->nodes, node);
		node = (Node*) List_popFront(graph->nodes);

		count++;
	}

	return NULL;
}

void Graph_insertEdge(Graph *graph, void *origin, void *target, int (*compare)(void *, void *)) {
	Node *node = NULL;
	int count = 0;

	assert(graph != NULL);
	assert(origin != NULL);
	assert(target != NULL);
	assert(compare != NULL);

	node = (Node*) List_popFront(graph->nodes);

	while (count < List_getLength(graph->nodes)) {

		if (compare(node->value, origin) == 0) {
			List_pushFront(node->edges, target);
			List_pushBack(graph->nodes, node);
			break;
		}

		List_pushBack(graph->nodes, node);
		node = (Node*) List_popFront(graph->nodes);

		count++;
	}
}

void Graph_removeEdge(Graph *graph, void *origin, void *target, int (*compare)(void *, void *)) {
	Node *node = NULL;

	assert(graph != NULL);
	assert(origin != NULL);
	assert(target != NULL);
	assert(compare != NULL);

	node = (Node*) List_find(graph->nodes, origin, compare);

	assert(node != NULL);

	List_remove(node->edges, target, compare);
}

int Graph_getLength(Graph *graph) {
	
	assert(graph != NULL);

	return List_getLength(graph->nodes);
}

void Graph_delete(Graph *graph) {
	Node *node;

	assert(graph != NULL);

	node = (Node*) List_popFront(graph->nodes);

	while (node) {
		List_delete(node->edges);
		free(node);
		node = (Node*) List_popFront(graph->nodes);
		printf("--\n");
	}

	free(graph);
}

void print(void *v){
	printf("%d", *((int*)v));
}

int compare(void *v_1, void *v_2) {
	return *((int*)v_1) - *((int*)v_2);
}

void Graph_print(Graph *graph, void (*printValue)(void *)) {
	Node *node;
	void *edge;
	int count = 0;

	assert(graph != NULL);
	assert(printValue != NULL);

	node = (Node*) List_popFront(graph->nodes);

	while (count < List_getLength(graph->nodes)) {
		printf("(");
		printValue(node->value);
		printf(")");

		edge = List_popFront(node->edges);

		while (edge) {
			printf("[");
			printValue(edge);
			printf("]");

			List_pushBack(node->edges, edge);
			edge = List_popFront(node->edges);
		}

		List_pushBack(graph->nodes, node);
		node = (Node*) List_popFront(graph->nodes);
		printf("\n");

		count++;
	}
}

int main() {
	Graph *g = Graph_create();
	int n[] = {1,2,3,4};

	Graph_insertNode(g, &n[0]);
	Graph_insertNode(g, &n[1]);
	Graph_insertNode(g, &n[2]);
	Graph_insertNode(g, &n[3]);

	Graph_insertEdge(g, &n[0], &n[1], compare);
	Graph_insertEdge(g, &n[0], &n[2], compare);
	Graph_insertEdge(g, &n[0], &n[3], compare);

	Graph_insertEdge(g, &n[1], &n[3], compare);

	Graph_insertEdge(g, &n[2], &n[0], compare);
	Graph_insertEdge(g, &n[2], &n[3], compare);

	Graph_insertEdge(g, &n[3], &n[1], compare);
	Graph_insertEdge(g, &n[3], &n[3], compare);

	Graph_print(g, print);

	return 0;
}







