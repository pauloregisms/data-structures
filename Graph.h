typedef struct Graph Graph;

Graph *Graph_create(int (*compare)(void*, void*));
int Graph_delete(Graph *graph);

int Graph_insert(Graph *graph, void *value);
void *Graph_find(Graph *graph, void *value);
void *Graph_remove(Graph *graph, void *value);

int Graph_getLength(Graph *graph);
void Graph_print(Graph *graph, void printValue(void*));

int Graph_createEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);
int Graph_removeEdge(Graph *graph, void *nodeOrigin, void *nodeTarget);