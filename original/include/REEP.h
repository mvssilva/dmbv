#ifndef REEP_H
#define REEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class REEP
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
        REEP(const Grafo& pG);
        virtual ~REEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;
};

#endif // REEP_H
