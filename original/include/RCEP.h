#ifndef RCEP_H
#define RCEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class RCEP
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
        RCEP(const Grafo& pG);
        virtual ~RCEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // RCEP_H
