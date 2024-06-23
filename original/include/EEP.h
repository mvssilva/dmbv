#ifndef EEP_H
#define EEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class EEP
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
        EEP(const Grafo& pG);
        virtual ~EEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // EEP_H
