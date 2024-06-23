#if !defined(RESULT_H_H)
#define RESULT_H_H


typedef struct Result
{   
    char * name;
    float n;
    float qtd;
    float m;
    
    float rbepaleatorio;
    float rbepseedfixa1;
    float rbepseedfixa100;
    float rbepseedfixa1000;

    float pagerank1;  
    float pagerank2;

    float pagerank1seed;
    float pagerank2seed;
    
    float moreno;
    float otimo;
}Result;

void result_set(Result *r, float n, float m, float Bt, char * name);
float result_get_n(Result);
float result_get_m(Result);
float result_get_otimo(Result);
float result_get_moreno(Result);
void result_inserir(Result * r, float Bt);
int result_compare(const void *a, const void *b);
void result_destruct(Result * r);
void result_set_otimo(Result *r, float);
void result_set_moreno(Result *r, float);
void result_set_pagerank1(Result *r, float);
void result_set_pagerank2(Result *r, float);
void result_set_rbepseedfixa1(Result *r, float);
void result_set_rbepseedfixa100(Result *r, float);
void result_set_rbepseedfixa1000(Result *r, float);

#endif // RESULT_H_H
