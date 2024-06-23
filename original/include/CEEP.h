#ifndef CEEP_H
#define CEEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class CEEP
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
        CEEP(const Grafo& pG);
        virtual ~CEEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // CEEP_H
