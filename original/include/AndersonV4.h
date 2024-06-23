#ifndef ANDERSONV4_H
#define ANDERSONV4_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"

using namespace std;

class AndersonV4
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
        AndersonV4(const Grafo& pG);
        virtual ~AndersonV4();

        void Oliveira();

        Grafo ObterArvore() const;
        vector<int> ObterBranches() const;
        vector<int> ObterGrauBT() const;

};

#endif // ANDERSONV4_H
