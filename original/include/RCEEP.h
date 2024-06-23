#ifndef RCEEP_H
#define RCEEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class RCEEP
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
        RCEEP(const Grafo& pG);
        virtual ~RCEEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;
};

#endif // RCEEP_H
