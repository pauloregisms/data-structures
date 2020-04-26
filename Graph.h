typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

Graph  *Graph_create();

Vertex *Graph_findVertex(Graph *graph, void *value);
Edge *Graph_findEdge(Graph *graph, void *value);

int Graph_insertVertex(Graph *graph, void *value);
int *Graph_removeVertex(Graph *graph, void *value, int (*compare)(void*,void*));

int Graph_insertEdge(Vertex *origin, Vertex *target, void *value);
void *Graph_removeEdge(Graph *graph, void *value, int (*compare)(void*,void*));

int Graph_getLength(Graph *graph);
int Graph_getVertexDegre(Vertex *vertex);
int Graph_getVertexIncidence(Vertex *vertex);

int Graph_print(Graph *graph, void printValue(void*));
int Graph_delete(Graph *graph);