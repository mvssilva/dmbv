#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <set>
#include <vector>
#include <queue>

#include "Grafo.h"


class BuscaLocal
{
    protected:
        Grafo G;
        Grafo T;
        Grafo NewT;

        vector<int> BT;
        set<int> BV;
        void AtualizarCConexas(int v, int u);

    private:
        vector<bool> InFolhas;
        vector<bool> InBV;

    public:
        BuscaLocal(const Grafo& pG, const Grafo& pT, vector<int> B);
        virtual ~BuscaLocal();

        void ConectaFolhas();
        void Caso2(vector<int> n, vector<int> pai, vector<vector<int>> cr, queue<int> fila);

        Grafo ObterArvore() const;
        set<int> ObterBranches() const;
        vector<int> ObterGrauBV() const;

};

#endif // BUSCALOCAL_H
