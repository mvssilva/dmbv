#include <iostream>
#include </opt/ibm/ILOG/CPLEX_Studio221/cplex/include/ilcplex/ilocplex.h>
#include <set>
#include <vector>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <float.h>
#include <cstring>
#include <queue>
#include <stdio.h>
#include <dirent.h>
#include <cstdlib>
#include <algorithm>
 
#define dimMatriz 5

using namespace std;

extern "C"
{
  #include </usr/local/include/igraph/igraph.h> 
}

#include "Grafo.h"
#include "RBEP.h"

void geraMatrizCentralidades(float to[][dimMatriz], igraph_vector_t* from, int dim, int col)
{
    for(int i=0; i<dim; i++){
        float x = (float) igraph_vector_e(from, i);
        to[i][col] = x;
    } 
}

int main(int argc, char * argv[]){

    if (argc < 2){
		cout << "Nome do arquivo não recebido" << endl;
		return 1;
	}

    igraph_set_attribute_table(&igraph_cattribute_table);
    igraph_t g_aux;

    Grafo G = Grafo::LerArquivo(argv[1], g_aux);

    double time_spent = 0.0;
    clock_t start = clock();
    
    Grafo T;
    vector<int> BT;
    vector<int> BTv;
    int BTMin = 1001;
    int BTMax = 0;
    double Time = 0.0;

    string verificado = "True";

    int n = igraph_vcount(&g_aux);
    float vectorBt[n] = {0};

    int dbranch[n] = {0};

    for(int i=0; i<100; i++)
    {
        double time_spent4 = 0.0;
        clock_t start4 = clock();

        RBEP alg = RBEP(G);

        alg.Oliveira(i);

        clock_t end = clock();
        time_spent += (double)(end - start) / CLOCKS_PER_SEC;

        Time += time_spent;

        T = alg.ObterArvore();
        BT = alg.ObterBranches();
        BTv.push_back(BT.size());

        for(int v : BT){
            dbranch[v] += 1;
        }

        if(BT.size() < BTMin){
            BTMin = BT.size();
            for (int j = 0; j < n; ++j){
                vectorBt[j] = 0;
            }
            for(int v : BT){
                vectorBt[v] = 1;
            }
        }
        if(BT.size() > BTMax)
            BTMax = BT.size();
        if(T.ValidarArvore() != true || T.V.size() != G.V.size())
            verificado = "False";

    }

    ofstream RBEPm("rbep.csv", std::ios_base::app);
    
    float soma = 0.0;
    for(int i : BTv)
       soma = soma + i;
    RBEPm << argv[1] <<  ";"<< G.n << ";" << G.m << ";" << BTMin << ";" << BTMax << ";" << soma/100 << ";"<< endl;
    RBEPm.close();

    char instanceSet[100] = {'\0'};
    char instanceName[100] = {'\0'};
    int dbranch_number;
    float matCentralidades[n][dimMatriz] = {0}; // inicializa matriz com ids dos vértices, as centralidades e a solução (vetor y)

        
    for(int i = 0; i < n; i++){
        matCentralidades[i][0] = i+1;
    }
    
    igraph_vector_t v;
    igraph_vector_t result;
    igraph_vector_init(&result, 0);
    igraph_degree(&g_aux, &result, igraph_vss_all(), IGRAPH_ALL, IGRAPH_LOOPS);
    geraMatrizCentralidades(matCentralidades, &result, n, 1);

    igraph_vector_t pagerank;
    igraph_real_t value;
    igraph_vector_init(&pagerank, 0);
    igraph_pagerank(&g_aux, IGRAPH_PAGERANK_ALGO_PRPACK, &pagerank, &value, igraph_vss_all(), IGRAPH_UNDIRECTED,
                    /* damping */ 0.85, /* weights */ NULL, NULL /* not needed with PRPACK method */);

    geraMatrizCentralidades(matCentralidades, &pagerank, n, 2);
    igraph_vector_destroy(&pagerank);

    for(int i = 0; i < n; i++){
        matCentralidades[i][3] = vectorBt[i];
    }

    for(int i = 0; i < n; i++){
        matCentralidades[i][4] = dbranch[i];
    }
    
    string inputFile = argv[1];
    string baseName = inputFile.substr(inputFile.find_last_of("/\\") + 1);
    baseName = baseName.substr(0, baseName.find_last_of("."));
    string outputFile = "Centralidades/" + baseName + ".csv";
    std::ofstream outFile(outputFile);

    outFile << "N;GRAU;PageRank;R-BEP;D-BRANCH" << endl;

    for(int i=0; i<n; i++){
        for(int j=0;j<dimMatriz;j++){
            if(j == 0)
                outFile << matCentralidades[i][j] << ";";
            if(j == 1)
                outFile << matCentralidades[i][j] << ";";
            if(j == 2)
                outFile << matCentralidades[i][j] << ";";
            if(j == 3)
                outFile << matCentralidades[i][j] << ";";
            if(j == 4)
                outFile << matCentralidades[i][j];
        }
        outFile << endl;
    }

    return 0;
}