#ifndef RBEP_H
#define RBEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class RBEP
{
    protected:
        Grafo G;
        Grafo T;

        vector<int> BT;
        void AtualizarCConexas(int v, int u);

    private:
        vector<bool> InBT;
        //priority_queue<pair<int, int>> Pontas; //Pontas indica caminhos possíveis
        vector<bool> InPontas;
        //vector<bool> RemPontas;
        set<int> Pontas;

    public:
        RBEP(const Grafo& pG);
        virtual ~RBEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;
};

#endif // RBEP_H
