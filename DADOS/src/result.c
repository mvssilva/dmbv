#include "result.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void result_set(Result * r, float n, float m, float Bt, char * name)
{   
    r->name  = strdup(name);
    // printf("%s\n", r->name);
    r->n = n;
    r->m = m;
    r->qtd++;

    r->rbep = Bt;
    r->moreno = 0;
    r->otimo = 0;
}

float result_get_n(Result r)
{
    return r.n;
}

void result_inserir(Result * r, float Bt)
{
    int i = r->qtd;
    r->rbep = Bt;
    r->qtd++;    
}

float result_get_m(Result r){
    return r.m;
}

float result_get_otimo(Result r){
    return r.otimo;
}

float result_get_moreno(Result r){
    return r.moreno;
}


int result_compare(const void *a, const void *b)
{
    Result *result1 = (Result *)a;
    Result *result2 = (Result *)b;

    float n1 = result1->n;
    float n2 = result2->n;

    float m1 = result1->m;
    float m2 = result2->m;

    if(n1 == n2){
        if(m1 == m2)
            return 0;
        if(m1 < m2)
            return -1;
        else
            return 1;
    }
    else if(n1 < n2)
        return -1;
    else
        return 1;

}

void result_set_otimo(Result *r, float otimo)
{
    r->otimo = otimo;
}

void result_set_moreno(Result *r, float moreno)
{
    r->moreno = moreno;
}

void result_set_pagerank1(Result *r, float pagerank1)
{
    r->pagerank1 = pagerank1;
}

void result_set_pagerank2(Result *r, float pagerank2)
{
    r->pagerank2 = pagerank2;
}

