#ifndef RODRIGO_H
#define RODRIGO_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class Rodrigo
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
        Rodrigo(const Grafo& pG);
        virtual ~Rodrigo();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // RODRIGO_H
