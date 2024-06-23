#ifndef ALGORITMO3_H
#define ALGORITMO3_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class Algoritmo3
{
    protected:
        Grafo G;
        Grafo T;

        vector<int> BT;
        void AtualizarCConexas(int v, int u);

    private:
        vector<bool> InBT;
        //Pontas indica caminhos possíveis
        vector<bool> InPontas;

        set<int> Pontas;

    public:
        Algoritmo3(const Grafo& pG);
        virtual ~Algoritmo3();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // ALGORITMO3_H
