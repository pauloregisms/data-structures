#include "Iterator.h"

struct Iterator {
        void *value;
        Iterator *next;
};

Iterator *Iterator_create() {
        
}

void *Iterator_getNext(Iterator *iterator);

int Itarator_hasMore(Iterator *iterator);