#define nc 7

#include "src/Graph.h"
#include </opt/ibm/ILOG/CPLEX_Studio2211/cplex/include/ilcplex/ilocplex.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <dirent.h>
#include <cstdlib>
#include <float.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <queue>

#include "src/ReadFile.h"
#include "src/Heuristic.h"
//#include "PlotGrafo.h"
//#include "Centralidades.h"

extern "C"
{
  #include </usr/local/include/igraph/igraph.h> 
}

int NumCut = 0;

int main(int argc, char *argv[])
{
    int min_HV, numb_OH, numb_NH;
    float time_solve, real_time;   
    clock_t start;
    FILE *file;

    if (argc < 6)
    {
        cout << "Faltam argumentos na chamada: dmbv nome_arquivo parametro_d leitor_instancia." << endl;
        cout << "Exemplo: dmbv Spd_RF2_80_133_1555.txt 2 2 1 1" << endl;
        return 1;
    }

    int d = atoi(argv[2]); // Representa quantos graus o vertice tem que ter para ser um d-brnach. 
    int inst = atoi(argv[3]); // Qual tipo de instancia, variação na funcao de leitura
    int degreeLocal = atoi(argv[4]); // Classificacao por grau = 0, por pagerank = 1;
    int degreePertu = atoi(argv[5]); // Classificacao por grau = 0, por pagerank = 1;
    int modo = atoi(argv[6]); // Seleção de visinhos em "firt best" = 0, por "best" = 1;

    
    igraph_set_attribute_table(&igraph_cattribute_table);

    igraph_t g;
    vector<float> pagerank;
    readInstance(inst, argv[1], g, pagerank);    

    time_solve = 0;
    start = clock();

    Heuristic heuristic(d);
    int n = igraph_vcount(&g);
    int m = igraph_ecount(&g);

    bool*OH = new bool[n];
    bool*NH = new bool[n];
    int*L = new int[n];
    bool solved;
    int timeLimit = 3600;

    for(int i = 0; i < n; i++)
    {
        OH[i] = NH[i] = false;
        L[i] = 0;
    }

    srand(igraph_vcount(&g));
    NumCut = 0;
    numb_OH = 0;

    heuristic.ILS(g,L,OH, pagerank, argv[1], degreeLocal, degreePertu, modo);

    real_time = ((double)clock() - (double)start) / CLOCKS_PER_SEC;
    ofstream RBEPm("output/cn1.csv", std::ios_base::app);
    
    RBEPm << argv[1] << ";"<< n << ";" << m << ";" << heuristic.numHV << ";" << real_time << ";" << endl;
    RBEPm.close();

    igraph_destroy(&g);
    return 0;
}