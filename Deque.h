typedef struct Deque Deque;

Deque *Deque_create();
int Deque_delete(Deque *deque);

int Deque_pushBack(Deque *deque, void *value);
int Deque_pushFront(Deque *deque, void *value);

void *Deque_popBack(Deque *deque);
void *Deque_popFront(Deque *deque);

void *Deque_getFront(Deque *deque);
void *Deque_getBack(Deque *deque);
int   Deque_getLength(Deque *deque);

void Deque_print(Deque *deque, void (*print)(void*));