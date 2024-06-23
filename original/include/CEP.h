#ifndef CEP_H
#define CEP_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class CEP
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
        CEP(const Grafo& pG);
        virtual ~CEP();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;
};

#endif // CEP_H
