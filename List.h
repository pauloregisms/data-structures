typedef struct List List;

List *List_create();
void List_delete(List *List);

void List_pushBack(List *List, void *value);
void List_pushFront(List *List, void *value);

void *List_popBack(List *List);
void *List_popFront(List *List);

void *List_getFront(List *List);
void *List_getBack(List *List);

int List_getLength(List *List);
void *List_find(List *List, void *value, int (*compare)(void *, void *));
void *List_remove(List *List, void *value, int (*compare)(void *, void *));
void List_print(List *List, void (*print)(void*));
List *List_map(List *list, void *value, void* (*callback)(void*, void*));