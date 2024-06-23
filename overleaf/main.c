#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void process_line_marcos(char * line, Vector * v){
    char *name = strtok(line, ";");
    char * n = strtok(NULL, ";");
    char * m = strtok(NULL, ";");
    char * BtMIN = strtok(NULL, ";");
    char * BtMAX = strtok(NULL, ";");
    char * BtMEDIO = strtok(NULL, ";");

    float vertices = atof(n);
    float arestas = atof(m);

    vector_push_back(v, vertices, arestas, atof(BtMIN), name);
    // vector_push_back(v, vertices, arestas, atof(BtMEDIO), name);
}

void process_line_anderson(char * line, Vector * v){
    char *name = strtok(line, "\t");
    char * n = strtok(NULL, " ");
    char * m = strtok(NULL, " ");
    char * LIXO = strtok(NULL, " ");
    char * BtMIN = strtok(NULL, "\t");
    char * BtMAX = strtok(NULL, "\t");
    char * BtMEDIO = strtok(NULL, "\t");
    float vertices = atof(n);
    float arestas = atof(m);
    vector_push_back(v, vertices, arestas, atof(BtMEDIO), name);
}

void  setup_otimo(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;
    int qtd = 0;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        if(qtd == 0){
            qtd++;
            continue;
        }

        char * n = strtok(line, ";");
        char * m = strtok(NULL, ";");
        char * otimo = strtok(NULL, "\n");

        float auxN = atof(n);
        float auxM = atof(m);
        float auxOtimo = atof(otimo);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
                if(r.n == auxN && auxN < 600){
                    vector_add_otimo(v, auxOtimo, i);
                }
                else if(r.n == auxN && r.m == auxM && auxN >=600){
                    vector_add_otimo(v, auxOtimo, i);
                }
        }
        
    }
}

void setup_moreno(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;
    int qtd = 0;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        if(qtd == 0){
            qtd++;
            continue;
        }

        char * n = strtok(line, ";");
        char * m = strtok(NULL, ";");
        char * moreno = strtok(NULL, "\n");

        float auxN = atof(n);
        float auxM = atof(m);
        float auxmoreno = atof(moreno);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
                if(r.n == auxN && auxN < 600){
                    vector_add_moreno(v, auxmoreno, i);
                }
                else if(r.n == auxN && r.m == auxM && auxN >=600){
                    vector_add_moreno(v, auxmoreno, i);
                }
        }
        
    }
}

Vector * setup_rbep(char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    Vector * v = vector_init(30); 
    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        process_line_marcos(line, v);
        // process_line_anderson(line, v);
    }
    return v;
}

void setup_seed_fixa1(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        char *name = strtok(line, ";");
        char * n = strtok(NULL, ";");
        char * m = strtok(NULL, ";");
        char * BtMIN = strtok(NULL, ";");
        char * BtMAX = strtok(NULL, ";");
        char * BtMEDIO = strtok(NULL, ";");

        float vertices = atof(n);
        float arestas = atof(m);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
            if(strcmp(r.name , name) == 0){
                vector_add_rbepseedfixa1(v, atof(BtMIN), i);
            }
        }
    }
}

void setup_seed_fixa100(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        char *name = strtok(line, ";");
        char * n = strtok(NULL, ";");
        char * m = strtok(NULL, ";");
        char * BtMIN = strtok(NULL, ";");
        char * BtMAX = strtok(NULL, ";");
        char * BtMEDIO = strtok(NULL, ";");

        float vertices = atof(n);
        float arestas = atof(m);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
            if(strcmp(r.name , name) == 0){
                vector_add_rbepseedfixa100(v, atof(BtMIN), i);
            }
        }
    }
}

void setup_seed_fixa1000(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        char *name = strtok(line, ";");
        char * n = strtok(NULL, ";");
        char * m = strtok(NULL, ";");
        char * BtMIN = strtok(NULL, ";");
        char * BtMAX = strtok(NULL, ";");
        char * BtMEDIO = strtok(NULL, ";");

        float vertices = atof(n);
        float arestas = atof(m);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
            if(strcmp(r.name , name) == 0){
                vector_add_rbepseedfixa1000(v, atof(BtMIN), i);
            }
        }
    }
}

void setup_rbep_pagerank1(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        char *name = strtok(line, ";");
        char * n = strtok(NULL, ";");
        char * m = strtok(NULL, ";");
        char * BtMIN = strtok(NULL, ";");
        char * BtMAX = strtok(NULL, ";");
        char * BtMEDIO = strtok(NULL, ";");

        float vertices = atof(n);
        float arestas = atof(m);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
            if(strcmp(r.name , name) == 0){
                vector_add_pagerank1(v, atof(BtMIN), i);
                // vector_add_pagerank1(v, atof(BtMEDIO), i);

            }
        }
    }
}

void setup_rbep_pagerank2(Vector * v, char * directory){
    FILE *file = fopen(directory, "r");
    if (file == NULL){
        exit(1);
    }

    char *line = NULL;
    size_t size = 0;
    int len;

    while ((len = getline(&line, &size, file)) != -1)
    {
        line[len - 1] = '\0';
        char *name = strtok(line, ";");
        char * n = strtok(NULL, ";");
        char * m = strtok(NULL, ";");
        char * BtMIN = strtok(NULL, ";");
        char * BtMAX = strtok(NULL, ";");
        char * BtMEDIO = strtok(NULL, ";");

        float vertices = atof(n);
        float arestas = atof(m);

        for(int i = 0; i < vector_size(v); i++){
            Result r  = vector_get_indice(v, i);
            if(strcmp(r.name , name) == 0){
                vector_add_pagerank2(v, atof(BtMIN), i);
                // vector_add_pagerank2(v, atof(BtMEDIO), i);
            }
        }
        
    }
}

void write_output_geral(Vector *v){
    FILE * file1 = fopen("Resultados.csv", "w");
    fprintf(file1, "n';m';Ótimo;Moreno et Al;R-BEP;PageRank1;PageRank2\n");

    float rNanterior = -1;
    float rManterior = -1;

    for(int i = 0; i < vector_size(v); i++)
    {   
        Result r = vector_get_indice(v, i);
        float rN = result_get_n(r);
        float rM = result_get_m(r);
        float rOtimo = result_get_otimo(r);
        float rMoreno = result_get_moreno(r);

        if(rN < 600 && rN != rNanterior){

            float soma = 0;
            float qtd = 0;
            Result r;
            
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.m;
                    qtd++;
                }
            }
            float rMmedio = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.rbepaleatorio;
                    qtd++;
                }
            }
            float rBtMedio = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.pagerank1;
                    qtd++;
                }
            }
            float rBtpagerank1= soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.pagerank2;
                    qtd++;
                }
            }
            float rBtpagerank2 = soma / qtd;

            fprintf(file1, "%.0f;", rN);
            fprintf(file1, "%.1f;", rMmedio);
            fprintf(file1, "%.1f;", rOtimo);
            fprintf(file1, "%.2f;", rMoreno);
            fprintf(file1, "%.2f;", rBtMedio);
            fprintf(file1, "%.2f;", rBtpagerank1);
            fprintf(file1, "%.2f", rBtpagerank2);
            fprintf(file1, "\n");
        }
        rNanterior = rN;
        rManterior = rM;
    }
    fclose(file1);

    FILE * file2 = fopen("Result_Large.csv", "w");
    fprintf(file2, "n';m';Ótimo;Moreno et Al;R-BEP;PageRank1;PageRank2\n");

    rNanterior = -1;
    rManterior = -1;

    for(int i = 0; i < vector_size(v); i++)
    {   

        Result r = vector_get_indice(v, i);
        float rN = result_get_n(r);
        float rM = result_get_m(r);
        float rOtimo = result_get_otimo(r);
        float rMoreno = result_get_moreno(r);

        if(rN >= 600 && rM != rManterior){
            rM = result_get_m(r);
            float soma = 0;
            float qtd = 0;
            Result r;
            
            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.rbepaleatorio;
                    qtd++;
                }
            }
            float rBtMedio = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.pagerank1;
                    qtd++;
                }
            }
            float rBtpagerank1= soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.pagerank2;
                    qtd++;
                }
            }
            float rBtpagerank2 = soma / qtd;

            fprintf(file2, "%.0f;", rN);
            fprintf(file2, "%.0f;", rM);
            fprintf(file2, "%.1f;", rOtimo);
            fprintf(file2, "%.1f;", rMoreno);
            fprintf(file2, "%.1f;", rBtMedio );
            fprintf(file2, "%.1f;", rBtpagerank1);
            fprintf(file2, "%.1f", rBtpagerank2);
            fprintf(file2, "\n");

        }
        rNanterior = rN;
        rManterior = rM;
    }
    fclose(file2);

}

void write_output_seed_fixa(Vector *v){
    FILE * file1 = fopen("result-mediun-seed-100.csv", "w");
    fprintf(file1, "n';m';Ótimo;Moreno et Al;R-BEP (a);R-BEP (100);PG1 (100); PG2 (100)\n");

    float rNanterior = -1;
    float rManterior = -1;

    for(int i = 0; i < vector_size(v); i++)
    {   
        Result r = vector_get_indice(v, i);
        float rN = result_get_n(r);
        float rM = result_get_m(r);
        float rOtimo = result_get_otimo(r);
        float rMoreno = result_get_moreno(r);

        if(rN < 600 && rN != rNanterior){

            float soma = 0;
            float qtd = 0;
            Result r;
            
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.m;
                    qtd++;
                }
            }
            float rMmedio = soma / qtd;

            qtd = 0;
            soma = 0;
            
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.rbepaleatorio;
                    qtd++;
                }
            }
            float rBtMedio = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.rbepseedfixa100;
                    qtd++;
                }
            }
            float rBtseedfixa100 = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.pagerank1;
                    qtd++;
                }
            }
            float pagerank1 = soma / qtd;


            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN){
                    soma += r.pagerank2;
                    qtd++;
                }
            }
            float pagerank2 = soma / qtd;

            fprintf(file1, "%.0f;", rN);
            fprintf(file1, "%.1f;", rMmedio);
            fprintf(file1, "%.1f;", rOtimo);
            fprintf(file1, "%.2f;", rMoreno);
            fprintf(file1, "%.2f;", rBtMedio);
            fprintf(file1, "%.2f;", rBtseedfixa100);
            fprintf(file1, "%.2f;", pagerank1);
            fprintf(file1, "%.2f", pagerank2);
            fprintf(file1, "\n");
        }
        rNanterior = rN;
        rManterior = rM;
    }
    fclose(file1);


    FILE * file2 = fopen("result-large-seed-100.csv", "w");
    fprintf(file2, "n';m';Ótimo;Moreno et Al;R-BEP (a);R-BEP (100);PG1 (100); PG2 (100)\n");

    rNanterior = -1;
    rManterior = -1;

    for(int i = 0; i < vector_size(v); i++)
    {   

        Result r = vector_get_indice(v, i);
        float rN = result_get_n(r);
        float rM = result_get_m(r);
        float rOtimo = result_get_otimo(r);
        float rMoreno = result_get_moreno(r);

        if(rN >= 600 && rM != rManterior){
            rM = result_get_m(r);
            float soma = 0;
            float qtd = 0;
            Result r;
            
            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.rbepaleatorio;
                    qtd++;
                }
            }
            float rBtMedio = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.rbepseedfixa100;
                    qtd++;
                }
            }
            float rBtseedfixa100 = soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.pagerank1;
                    qtd++;
                }
            }
            float pagerank1= soma / qtd;

            qtd = 0;
            soma = 0;
            for(int i = 0; i < vector_size(v); i++){
                r = vector_get_indice(v, i);
                if(r.n == rN && r.m == rM){
                    soma += r.pagerank2;
                    qtd++;
                }
            }
            float pagerank2 = soma / qtd;

            fprintf(file2, "%.0f;", rN);
            fprintf(file2, "%.0f;", rM);
            fprintf(file2, "%.1f;", rOtimo);
            fprintf(file2, "%.1f;", rMoreno);
            fprintf(file2, "%.1f;", rBtMedio );
            fprintf(file1, "%.1f;", rBtseedfixa100);
            fprintf(file2, "%.1f;", pagerank1);
            fprintf(file2, "%.1f", pagerank2);
            fprintf(file2, "\n");

        }
        rNanterior = rN;
        rManterior = rM;
    }
    fclose(file2);

}

int main(int argc, char ** argv){

    if(argc < 4){
        return 1;
    }

    Vector * v = setup_rbep(argv[1]);
    setup_seed_fixa100(v, argv[3]);
    setup_rbep_pagerank1(v, argv[3]);
    setup_rbep_pagerank2(v, argv[4]);
    setup_otimo(v, argv[5]);
    setup_moreno(v, argv[6]);

    printf("setup\n");
    vector_sort(v);
    printf("sort\n");
    write_output_seed_fixa(v);
    printf("write\n");

    return 0;
}

