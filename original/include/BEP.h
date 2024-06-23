#ifndef BEP_H
#define BEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class BEP
{
    protected:
        Grafo G;
        Grafo T;

        vector<int> BT;
        void AtualizarCConexas(int v, int u);
    private:
        vector<bool> InBT;
        priority_queue<pair<int, int>> Pontas; //Pontas indica caminhos possíveis
        vector<bool> InPontas;
        vector<bool> RemPontas;

    public:
        BEP(const Grafo& pG);
        virtual ~BEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;
};

#endif // BEP_H
