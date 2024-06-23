#include <iostream>
#include <set>
#include <vector>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include <iostream>
#include <random>

#include "AndersonV4.h"
#include "Rodrigo.h"
#include "Algoritmo3.h"
#include "BuscaLocal.h"
#include "BEP.h"
#include "RBEP.h"
#include "CEP.h"
#include "RCEP.h"
#include "EEP.h"
#include "REEP.h"
#include "CEEP.h"
#include "RCEEP.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 2){
		cout << "Nome do arquivo não recebido" << endl;
		return 1;
	}

	Grafo G = Grafo::LerArquivo(argv[1]);

    double time_spent = 0.0;
    clock_t start1 = clock();

    // BEP alg = BEP(G);
    // alg.Oliveira();

    // clock_t end1 = clock();
    // time_spent += (double)(end1 - start1) / CLOCKS_PER_SEC;

    // double time_spent2 = 0.0;
    // clock_t start2 = clock();

    // CEP alg2 = CEP(G);
    // alg2.Oliveira();

    // clock_t end2 = clock();
    // time_spent2 += (double)(end2 - start2) / CLOCKS_PER_SEC;

    // double time_spent3 = 0.0;
    // clock_t start3 = clock();

    // EEP alg3 = EEP(G);
    // alg3.Oliveira();

    // clock_t end3 = clock();
    // time_spent3 += (double)(end3 - start3) / CLOCKS_PER_SEC;

    // double time_spent7 = 0.0;
    // clock_t start7 = clock();

    // CEEP alg7 = CEEP(G);
    // alg7.Oliveira();

    // clock_t end7 = clock();
    // time_spent7 += (double)(end7 - start7) / CLOCKS_PER_SEC;

    // Grafo T = alg.ObterArvore();
    // vector<int> BT = alg.ObterBranches();
    // Grafo T2 = alg2.ObterArvore();
    // vector<int> BT2 = alg2.ObterBranches();
    // Grafo T3 = alg3.ObterArvore();
    // vector<int> BT3 = alg3.ObterBranches();
    // Grafo T7 = alg7.ObterArvore();
    // vector<int> BT7 = alg7.ObterBranches();

    // vector<int> BV;
    // vector<int> BV2;
    // vector<int> BV3;
    // vector<int> BV7;

    // int grau;
    // for(int v : T.V)
    // {
    //     grau = 0;
    //     for(pair<int,int> ij : T.E)
    //     {
    //         int i = ij.first;
    //         int j = ij.second;
    //         if(i == v || j == v)
    //         {
    //             grau += 1;
    //         }
    //     }
    //     if(grau > 2)
    //     {
    //         BV.push_back(v);
    //     }
    // }
    // grau = 0;
    // for(int v : T2.V)
    // {
    //     grau = 0;
    //     for(pair<int,int> ij : T2.E)
    //     {
    //         int i = ij.first;
    //         int j = ij.second;
    //         if(i == v || j == v)
    //         {
    //             grau += 1;
    //         }
    //     }
    //     if(grau > 2)
    //     {
    //         BV2.push_back(v);
    //     }
    // }
    // grau = 0;
    // for(int v : T3.V)
    // {
    //     grau = 0;
    //     for(pair<int,int> ij : T3.E)
    //     {
    //         int i = ij.first;
    //         int j = ij.second;
    //         if(i == v || j == v)
    //         {
    //             grau += 1;
    //         }
    //     }
    //     if(grau > 2)
    //     {
    //         BV3.push_back(v);
    //     }
    // }
    // grau = 0;
    // for(int v : T7.V)
    // {
    //     grau = 0;
    //     for(pair<int,int> ij : T7.E)
    //     {
    //         int i = ij.first;
    //         int j = ij.second;
    //         if(i == v || j == v)
    //         {
    //             grau += 1;
    //         }
    //     }
    //     if(grau > 2)
    //     {
    //         BV7.push_back(v);
    //     }
    // }

    // string verificado;
    // string verificado2;
    // string verificado3;
    // string verificado7;

    // if(T.ValidarArvore() == true && T.V.size() == G.V.size() && BT.size() == BV.size())
    //     verificado = "True";
    // else
    //    verificado = "False";

    // if(T2.ValidarArvore() == true && T2.V.size() == G.V.size() && BT2.size() == BV2.size())
    //     verificado2 = "True";
    // else
    //    verificado2 = "False";

    // if(T3.ValidarArvore() == true && T3.V.size() == G.V.size() && BT3.size() == BV3.size())
    //     verificado3 = "True";
    // else
    //    verificado3 = "False";

    // if(T7.ValidarArvore() == true && T7.V.size() == G.V.size() && BT7.size() == BV7.size())
    //     verificado7 = "True";
    // else
    //    verificado7 = "False";

    // ofstream BEP1("BEP.txt", std::ios_base::app);
    // ofstream CEP1("CEP.txt", std::ios_base::app);
    // ofstream EEP1("EEP.txt", std::ios_base::app);
    // ofstream CEEP1("CEEP.txt", std::ios_base::app);

    // cout << argv[1] << endl;
    // BEP1 << argv[1] << "\t" << BT.size() << "\t" << std::fixed << std::setprecision(10) << time_spent << "\t" << verificado <<endl;
    // CEP1 << argv[1] << "\t" << BT2.size() << "\t" << std::fixed << std::setprecision(10) << time_spent2 << "\t" <<verificado2 <<endl;
    // EEP1 << argv[1] << "\t" << BT3.size() << "\t" << std::fixed << std::setprecision(10) << time_spent3 << "\t" <<verificado3 <<endl;
    // CEEP1 << argv[1] << "\t" << BT7.size() << "\t" << std::fixed << std::setprecision(10) << time_spent7 << "\t" <<verificado7 <<endl;

    // BEP1.close();
    // CEP1.close();
    // EEP1.close();
    // CEEP1.close();

    Grafo T4;
    vector<int> BT4;
    // Grafo T5;
    // vector<int> BT5;
    // Grafo T6;
    // vector<int> BT6;
    // Grafo T8;
    // vector<int> BT8;

    vector<int> BT4v;
    int BT4Min = 1001;
    int BT4Max = 0;
    double Time4 = 0.0;
    // vector<int> BT5v;
    // int BT5Min = 1001;
    // int BT5Max = 0.0;
    // double Time5 = 0;
    // vector<int> BT6v;
    // int BT6Min = 1001;
    // int BT6Max = 0;
    // double Time6 = 0.0;
    // vector<int> BT8v;
    // int BT8Min = 1001;
    // int BT8Max = 0;
    // double Time8 = 0.0;

    string verificado4 = "True";
    // string verificado5 = "True";
    // string verificado6 = "True";
    // string verificado8 = "True";

    ofstream RBEP100("R-BEP100.txt", std::ios_base::app);
    // ofstream RCEP100("R-CEP100.txt", std::ios_base::app);
    // ofstream REEP100("R-EEP100.txt", std::ios_base::app);
    // ofstream RCEEP100("R-CEEP100.txt", std::ios_base::app);

    for(int i=0; i<100; i++)
    {
        double time_spent4 = 0.0;
        clock_t start4 = clock();

        RBEP alg4 = RBEP(G);

        alg4.Oliveira();\

        clock_t end4 = clock();
        time_spent4 += (double)(end4 - start4) / CLOCKS_PER_SEC;

        Time4 += time_spent4;

        T4 = alg4.ObterArvore();
        BT4 = alg4.ObterBranches();
        BT4v.push_back(BT4.size());
        if(BT4.size() < BT4Min)
            BT4Min = BT4.size();
        if(BT4.size() > BT4Max)
            BT4Max = BT4.size();
        if(T4.ValidarArvore() != true || T4.V.size() != G.V.size())
            verificado4 = "False";

        RBEP100 << argv[1] <<  "\t" << BT4.size() << "\t" << std::fixed << std::setprecision(10) << time_spent4 << "\t" << verificado4 << endl;
        cout << endl;
        cout << endl;

        // double time_spent5 = 0.0;
        // clock_t start5 = clock();

        // RCEP alg5 = RCEP(G);
        // alg5.Oliveira();

        // clock_t end5 = clock();
        // time_spent5 += (double)(end5 - start5) / CLOCKS_PER_SEC;

        // Time5 += time_spent5;

        // T5 = alg5.ObterArvore();
        // BT5 = alg5.ObterBranches();
        // BT5v.push_back(BT5.size());
        // if(BT5.size() < BT5Min)
        //     BT5Min = BT5.size();
        // if(BT5.size() > BT5Max)
        //     BT5Max = BT5.size();
        // if(T5.ValidarArvore() != true || T5.V.size() != G.V.size())
        //     verificado5 = "False";

        // RCEP100 << argv[1] <<  "\t" << BT5.size() << "\t" << std::fixed << std::setprecision(10) << time_spent5 << "\t" << verificado5 << endl;

        // double time_spent6 = 0.0;
        // clock_t start6 = clock();

        // REEP alg6 = REEP(G);
        // alg6.Oliveira();

        // clock_t end6 = clock();
        // time_spent6 += (double)(end6 - start6) / CLOCKS_PER_SEC;

        // Time6 += time_spent6;

        // T6 = alg6.ObterArvore();
        // BT6 = alg6.ObterBranches();
        // BT6v.push_back(BT6.size());
        // if(BT6.size() < BT6Min)
        //     BT6Min = BT6.size();
        // if(BT6.size() > BT6Max)
        //     BT6Max = BT6.size();
        // if(T6.ValidarArvore() != true || T6.V.size() != G.V.size())
        //     verificado6 = "False";

        // REEP100 << argv[1] <<  "\t" << BT6.size() << "\t" << std::fixed << std::setprecision(10) << time_spent6 << "\t" << verificado6 << endl;

        // double time_spent8 = 0.0;
        // clock_t start8 = clock();

        // RCEEP alg8 = RCEEP(G);
        // alg8.Oliveira();

        // clock_t end8 = clock();
        // time_spent8 += (double)(end8 - start8) / CLOCKS_PER_SEC;

        // Time8 += time_spent8;

        // T8 = alg8.ObterArvore();
        // BT8 = alg8.ObterBranches();
        // BT8v.push_back(BT8.size());
        // if(BT8.size() < BT8Min)
        //     BT8Min = BT8.size();
        // if(BT8.size() > BT8Max)
        //     BT8Max = BT8.size();
        // if(T8.ValidarArvore() != true || T8.V.size() != G.V.size())
        //     verificado8 = "False";

        // RCEEP100 << argv[1] <<  "\t" << BT8.size() << "\t" << std::fixed << std::setprecision(10) << time_spent8 << "\t" << verificado8 << endl;
    }

    RBEP100.close();
    // RCEP100.close();
    // REEP100.close();
    // RCEEP100.close();

    ofstream RBEPm("R-BEP.txt", std::ios_base::app);
    // ofstream RCEPm("R-CEP.txt", std::ios_base::app);
    // ofstream REEPm("R-EEP.txt", std::ios_base::app);
    // ofstream RCEEPm("R-CEEP.txt", std::ios_base::app);

    float soma = 0.0;
    for(int i : BT4v)
       soma = soma + i;
    RBEPm << argv[1] <<  "\t" << BT4Min << "\t" << BT4Max << "\t" << soma/100 << "\t" << std::fixed << std::setprecision(10) << Time4/100 << "\t" << verificado4 << endl;

    // soma = 0.0;
    // for(int i : BT5v)
    //    soma = soma + i;
    // RCEPm << argv[1] <<  "\t" << BT5Min << "\t" << BT5Max << "\t" << soma/100 << "\t" << std::fixed << std::setprecision(10) << Time5/100 << "\t" << verificado5 << endl;

    // soma = 0.0;
    // for(int i : BT6v)
    //    soma = soma + i;
    // REEPm << argv[1] <<  "\t" << BT6Min << "\t" << BT6Max << "\t" << soma/100 << "\t" << std::fixed << std::setprecision(10) << Time6/100 << "\t" << verificado6 << endl;

    // soma = 0.0;
    // for(int i : BT8v)
    //    soma = soma + i;
    // RCEEPm << argv[1] <<  "\t" << BT8Min << "\t" << BT8Max << "\t" << soma/100 << "\t" << std::fixed << std::setprecision(10) << Time8/100 << "\t" << verificado8 << endl;

    // T4.ImprimirArvoreGraphviz();

    RBEPm.close();
    // RCEPm.close();
    // REEPm.close();
    // RCEEPm.close();

    /*
    vector<int> BT100a;
    int BTaMin = 1001;
    int BTaMax = 0;
    int BTLaMin = 1001;
    vector<int> BT100b;
    int BTbMin = 1001;
    int BTbMax = 0;
    int BTLbMin = 1001;
    vector<int> BT100c;
    int BTcMin = 1001;
    int BTcMax = 0;
    int BTLcMin = 1001;

    Grafo T;
    vector<int> BT;
    Grafo T2;
    vector<int> BT2;
    Grafo T3;
    vector<int> BT3;
    for(int i=0; i<10; i++)
    {
        AndersonV4 alg = AndersonV4(G);
        alg.Oliveira();
        T = alg.ObterArvore();
        BT = alg.ObterBranches();
        BT100a.push_back(BT.size());
        if(BT.size() < BTaMin)
            BTaMin = BT.size();
        if(BT.size() > BTaMax)
            BTaMax = BT.size();
        BuscaLocal bl = BuscaLocal(G, T, BT);
        bl.ConectaFolhas();
        set<int> BTL = bl.ObterBranches();
        if(BTL.size() < BTLaMin)
           BTLaMin = BTL.size();

        Rodrigo alg2 = Rodrigo(G);
        alg2.Oliveira();
        T2 = alg2.ObterArvore();
        BT2 = alg2.ObterBranches();
        BT100b.push_back(BT2.size());
        if(BT2.size() < BTbMin)
            BTbMin = BT2.size();
        if(BT2.size() > BTbMax)
            BTbMax = BT2.size();
        BuscaLocal bl2 = BuscaLocal(G, T2, BT2);
        bl2.ConectaFolhas();
        set<int> BTL2 = bl2.ObterBranches();
        if(BTL2.size() < BTLbMin)
           BTLbMin = BTL2.size();

        Algoritmo3 alg3 = Algoritmo3(G);
        alg3.Oliveira();
        T3 = alg3.ObterArvore();
        BT3 = alg3.ObterBranches();
        BT100c.push_back(BT3.size());
        if(BT3.size() < BTcMin)
            BTcMin = BT3.size();
        if(BT3.size() > BTcMax)
            BTcMax = BT3.size();
        BuscaLocal bl3 = BuscaLocal(G, T3, BT3);
        bl3.ConectaFolhas();
        set<int> BTL3 = bl3.ObterBranches();
        if(BTL3.size() < BTLcMin)
           BTLcMin = BTL3.size();
    }
    cout << argv[1] << endl;
    int soma = 0;
    for(int i : BT100a)
       soma = soma + i;
    cout << "AndersonV4 - Min: " << BTaMin << " Max: " << BTaMax << " Media: " << soma/10 << " Busca Local Min: " << BTLaMin << endl;

    soma = 0;
    for(int i : BT100b)
       soma = soma + i;
    cout << "Rodrigo - Min: " << BTbMin << " Max: " << BTbMax << " Media: " << soma/10 << " Busca Local Min: " << BTLbMin << endl;

    soma = 0;
    for(int i : BT100c)
       soma = soma + i;
    cout << "Algoritmo3 - Min: " << BTcMin << " Max: " << BTcMax << " Media: " << soma/10 << " Busca Local Min: " << BTLcMin << endl << endl;
    */
    /*
    vector<int> BV;
    vector<int> BV2;
    vector<int> BV3;

    int grau;
    for(int v : T.V)
    {
        grau = 0;
        for(pair<int,int> ij : T.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV.push_back(v);
        }
    }
    grau = 0;
    for(int v : T2.V)
    {
        grau = 0;
        for(pair<int,int> ij : T2.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV2.push_back(v);
        }
    }
    grau = 0;
    for(int v : T3.V)
    {
        grau = 0;
        for(pair<int,int> ij : T3.E)
        {
            int i = ij.first;
            int j = ij.second;
            if(i == v or j == v)
            {
                grau += 1;
            }
        }
        if(grau > 2)
        {
            BV3.push_back(v);
        }
    }

    string verificado;
    string verificado2;
    string verificado3;

    if(T.ValidarArvore() == true && T.V.size() == G.V.size() && BT.size() == BV.size())
        verificado = "True";
    else
       verificado = "False";

    if(T2.ValidarArvore() == true && T2.V.size() == G.V.size() && BT2.size() == BV2.size())
        verificado2 = "True";
    else
       verificado2 = "False";

    if(T3.ValidarArvore() == true && T3.V.size() == G.V.size() && BT3.size() == BV3.size())
        verificado3 = "True";
    else
       verificado3 = "False";

    float somaGrau = 0;

    cout << argv[1] << "\t " << BT.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent << "\t " << verificado << "\t ";

    for (int v : GrauBT)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT.size();
        cout << mediaGrau;
    }

    cout << "\t " << BT2.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent2 << "\t " << verificado2 << "\t ";
    somaGrau = 0;
    for (int v : GrauBT2)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT2.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT2.size();
        cout << mediaGrau;
    }

    cout << "\t " << BT3.size() << "\t ";
    cout << std::fixed << std::setprecision(10) << time_spent3 << "\t " << verificado3 << "\t ";
    somaGrau = 0;
    for (int v : GrauBT3)
    {
        somaGrau = somaGrau + v;
    }
    if (GrauBT3.size() == 0)
    {
        cout << "0";
    }
    else
    {
        float mediaGrau = somaGrau / GrauBT3.size();
        cout << mediaGrau;
    }
    cout << endl;*/
    return 0;
}
