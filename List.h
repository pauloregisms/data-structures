typedef struct List List;

/**
 * Recebe uma função de comparação para os valores
 * na lista, aloca memória para uma lista vazia
 * e retorna um ponteiro para a lista
 */
List *List_create(int (*comparator)(void*,void*));

/**
 * Desaloca a lista da memória e retorna 1 
 * em caso de sucesso e 0 em caso de falha
 */
int List_delete(List *list);

/**
 * Cria uma nova célula o valor 'value', insere a 
 * nova célula na primeira posição da lista e retorna 1 
 * em caso de sucesso
 */
int List_insert(List* list, void *value);

/**
 * Retorna uma referência para nó da lista que contém o valor
 * 'value' ou retorna NULL se não encontrar.
 */
void *List_find(List* list, void *value);

/**
 * Retorna uma referência para o primeiro nó da lista.
 */
void *List_getFirst(List *list);

/**
 * Retorna uma referência para o último nó da lista.
 */
void *List_getLast(List *list);

/**
 * Remove o nó da lista que contém o valor
 * 'value' e retorna o valor do nó
 */
void *List_remove(List* list, void *value);

/**
 * Retorna o comprimento da lista
 */
int List_getLength(List *list);

/**
 * Recebe uma função de impressão para os valores da lista
 * e imprime a lista
 */
void List_print(List *list, void (*printValue)(void *));

/**
 * A função recebe uma lista como parâmetro e devolve 
 * uma nova lista na ordem inversa
 */
List *List_invert(List *list);

/**
 * A função recebe duas listas como parâmetros e devolve 
 * uma nova lista com os elementos das duas
 */
List *List_concat(List *l1, List *l2);

/** 
 * A função recebe uma lista e um valor e verica se o valor 
 * pertence a algum nó da lista retornando 1 em caso afirmativo 
 * e 0 caso o valor não se encontre na lista 
 */
int List_in(List *list, void *value);

