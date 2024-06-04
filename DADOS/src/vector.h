#if !defined(VECTOR_H_)
#define VECTOR_H_

#include "result.h"

typedef struct Vector Vector;

Vector * vector_init(int size);
void vector_push_back(Vector*, float, float, float, char *);
Result * vector_get_vertice(Vector*, float, float);
Result vector_get_indice(Vector*, int);
int vector_exist_equal(Vector *, float, float);
int vector_size(Vector *);
void vector_sort(Vector *);
void vector_add_otimo(Vector *, float, int);
void vector_add_moreno(Vector *, float, int);
void vector_add_pagerank1(Vector *, float, int);
void vector_add_pagerank2(Vector *, float, int);

void vector_destroy(Vector *);


#endif // VECTOR_H_
