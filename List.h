typedef struct List List;

List *List_create();
int List_insert(List* list, void *value);
int List_delete(List *list);

void *List_find(List* list, void *value, int (*compare)(void*,void*));
void *List_remove(List* list, void *value, int (*compare)(void*,void*));

void *List_getFirst(List *list);
void *List_getLast(List *list);
int List_getLength(List *list);

List *List_concat(List *list_1, List *list_2);
int List_print(List *list, void (*printValue)(void *));