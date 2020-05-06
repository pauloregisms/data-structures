typedef struct Graph Graph;

Graph *Graph_create();
void Graph_delete(Graph *graph);
void Graph_insert(Graph *graph, void *value);
void Graph_print(Graph *graph, void (*printValue)(void *));
void Graph_createEdge(Graph *graph, void *origin, void *target, int (*compare)(void*, void*));
void Graph_removeEdge(Graph *graph, void *origin, void *target, int (*compare)(void*, void*));