#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void printValue(void *v) {
	printf("%d ",*((int*)v));
}

int compareValues(void *v_1, void *v_2) {
	int *n_1 = (int*)v_1;
	int *n_2 = (int*)v_2;
	return *n_1 - *n_2;
}

int main() {
	int n[] = {0,1,2,3,4};
	Graph *g = Graph_create();
	
	Graph_insert(g, &n[1]);
	Graph_insert(g, &n[2]);
	Graph_insert(g, &n[3]);
	Graph_insert(g, &n[4]);

	Graph_createEdge(g, &n[1], &n[2], compareValues);
	Graph_createEdge(g, &n[1], &n[3], compareValues);
	Graph_createEdge(g, &n[1], &n[4], compareValues);
	Graph_createEdge(g, &n[2], &n[4], compareValues);
	Graph_createEdge(g, &n[3], &n[1], compareValues);
	Graph_createEdge(g, &n[3], &n[4], compareValues);
	Graph_createEdge(g, &n[4], &n[2], compareValues);
	Graph_createEdge(g, &n[4], &n[3], compareValues);
	Graph_print(g, printValue);

	Graph_removeEdge(g, &n[1], &n[4], compareValues);
	Graph_removeEdge(g, &n[3], &n[1], compareValues);
	Graph_print(g, printValue);
	
	Graph_delete(g);

	return 0;
}