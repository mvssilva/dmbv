#include "vector.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Vector{
    Result * data;
    int size;
    int capacity;
};

Vector *vector_init(int size)
{
    Vector * v = (Vector *)malloc(sizeof(Vector));
    v->data = (Result*) malloc(size*sizeof(Result));
    v->size = 0;
    v->capacity = size;

    return v;

}

Result *vector_get_vertice(Vector* v, float n, float m)
{
    for(int i = 0; i < v->size; i++){
        float aux_n = result_get_n(v->data[i]);
        float aux_m = result_get_m(v->data[i]);

        if(aux_n == n && aux_m == m) return &(v->data[i]);
    }

}

Result vector_get_indice(Vector* v, int indice)
{
    return v->data[indice];
}


void vector_push_back(Vector* v, float n, float m, float bt, char * name){
    if (v->size >= v->capacity)
    {
        v->capacity *= 2;
        v->data = (Result *)realloc(v->data, v->capacity * sizeof(Result));
    }
    Result * r = &(v->data[v->size]);
    v->size++;
    result_set(r, n, m, bt, name);
}

int vector_exist_equal(Vector * v, float n, float m){
    for(int i = 0; i < v->size; i++){
        float aux_n = result_get_n(v->data[i]);
        float aux_m = result_get_m(v->data[i]);
        if(aux_n == n && aux_m == m){
            return 1;
        }
    }

    return 0;
}

int vector_size(Vector *v)
{
    return v->size;
}

void vector_sort(Vector *v)
{   
    qsort(v->data, v->size, sizeof(Result), result_compare);
}

void vector_add_otimo(Vector * v, float otimo, int indice)
{
    Result * r = &(v->data[indice]);
    result_set_otimo(r, otimo);
}

void vector_add_moreno(Vector * v, float moreno, int indice)
{
    Result * r = &(v->data[indice]);
    result_set_moreno(r, moreno);
}

void vector_add_pagerank1(Vector * v, float pagerank1, int indice)
{
    Result * r = &(v->data[indice]);
    result_set_pagerank1(r, pagerank1);
}

void vector_add_pagerank2(Vector * v, float pagerank1, int indice)
{
    Result * r = &(v->data[indice]);
    result_set_pagerank2(r, pagerank1);
}
