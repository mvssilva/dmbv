#include "BEP.h"
#include <algorithm>
#include <iostream>

BEP::BEP(const Grafo& pG):
    G(pG), T(pG.n,pG.m), InBT(G.n, 0), InPontas(G.n, false), RemPontas(G.n, false)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
}

BEP::~BEP()
{
    //destructor
}

Grafo BEP::ObterArvore() const
{
    return T;
}

vector<int> BEP::ObterBranches() const
{
    return BT;
}

vector<int> BEP::ObterGrauBT() const
{
    vector<int> GrauBT;
    for (int v : BT)
    {
        GrauBT.push_back(T.Grau(v));
    }
    return GrauBT;
}

//Algoritmo Árvore Geradora - V4.3 - Primeira Heurística
void BEP::Oliveira()
{   
    //Inicialização de todos os dados como nulo.
    BT.clear(); // Conjunto de Ramificações
    while (!Pontas.empty()) Pontas.pop();

    for (int i = 0; i < G.n; i++)
    {   
        /*
        Vetor auxiliar para identificação dos vértices.
        Principalmente para evitar a repetição de vértices, e quebra de loops.
        */
        InBT[i] = false; 
        InPontas[i] = false; 
        RemPontas[i] = false; 
    }

    //Detectar articulações e pontes com DFS.
    G.DetectarArticulacoesEPontes();

    for(int v : G.ArticulacoesW2)
    {
        T.AdicionarVertice(v); //Adicionar vértices na árvore
        BT.push_back(v); //Considerar que todos são ramificações da árvore
        InBT[v] = 1; //Marca o vértice como uma ramificação.
    }

    for(pair<int,int> vu : G.Pontes) // Tratar Pontes
    {
        int v = vu.first;
        int u = vu.second;

        //Adicionar vertices referente as pontes detectadas.
        T.AdicionarVertice(v);
        T.AdicionarVertice(u);

        T.AdicionarAresta(v,u); //Corresponde Et no pseudocódigo.

        if (T.Grau(v) > 2 && InBT[v] == 0)
        {
            BT.push_back(v); // Adicionar vértices d-branch no vetor de ramificações
            InBT[v] = 1;
        }

        if (T.Grau(u) > 2 and InBT[u] == 0)
        {
            BT.push_back(u); // Adicionar vértices d-branch no vetor de ramificações
            InBT[u] = 1;
        }
    }


    //EXPANSAO
    for(int v : BT) //Esse vetor tem os vértices d-branch e as articulações.
    {
        for(int u : G.Adjacentes(v)) //Maximizar o grau do vértice d-branch
        {
            if(T.BuscarVertice(u) == false) //Se o vértice adjacente não estiver na árvore.
            {
                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
            }
            else//Faz a conexão entre vértices se estiver.
            {
                if ((T.Grau(u) == 1 || InBT[u] == 1) && T.CConexa(v) != T.CConexa(u))
                {
                    T.AdicionarAresta(v,u);
                }
            }
        }
    }

    //Verificar quais caminhos pode ser explorados:
    for(int v : T.V)
    {
        if(T.Grau(v) == 1 && G.Grau(v) > 1)
        {
            Pontas.push(make_pair(-1 * G.Grau(v), v));
            InPontas[v] = true;
        }
    }

    //Se nenhuma ponta foi identificada, cria uma nova:
    if(Pontas.empty())
    {
        int v = G.VerticeGrauMinimo();
        int u = G.AdjacenteGrauMinimo(v);

        T.AdicionarVertice(v);
        T.AdicionarVertice(u);
        T.AdicionarAresta(v,u);

        Pontas.push(make_pair(-1 * G.Grau(v), v));
        InPontas[v] = true;

        Pontas.push(make_pair(-1 * G.Grau(u), u));
        InPontas[u] = true;
    }

    //Continuação
    while(T.NumeroArestas() < G.n - 1)
    {
        if(Pontas.empty() == false)
        {
            int v;
            do
            {
                pair<int,int> topo = Pontas.top();
                v = topo.second;

                Pontas.pop();
                InPontas[v] = false;

                if (RemPontas[v] == false)
                {
                    break;
                }
                else
                {
                    RemPontas[v] = false;
                    v = -1;
                    continue;
                }
            }
            while(Pontas.empty() == false);

            if (v == -1) continue;

            vector<pair<int,pair<int,int>>> Nv;
            for(int u : G.Adjacentes(v))
                if(T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(v) && (InBT[u] == 1 || T.Grau(u) == 1)))
                    Nv.push_back(make_pair(u, make_pair(G.Grau(u), T.Grau(u))));

            if(Nv.empty() == false)
            {
                int du_G = G.n + 1;
                int du_T = G.n + 1;
                int u;

                for(pair<int,pair<int,int>> i : Nv)
                {
                    if(i.second.first < du_G)
                    {
                        u = i.first;
                        du_G = i.second.first;
                        du_T = i.second.second;
                    }
                    else
                    {
                        if(i.second.first == du_G)
                        {
                            if (i.second.second < du_T)
                            {
                                u = i.first;
                                du_G = i.second.first;
                                du_T = i.second.second;
                            }
                        }
                    }
                }

                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
				if (T.Grau(u) == 1)
                {
                    Pontas.push(make_pair(-1 * G.Grau(u), u));
                    InPontas[u] = true;
                }
				else
                {
                    if(InPontas[u] == true)
                    {
                        RemPontas[u] = true; //Como pontas ж lista de prioridade, nсo ж possьvel remover diretamente
                    }
                }
            }
        }
        else
        {
            //Nсo existe uma nova ponta para ser explorada: necessрrio converter um vжrtice da рrvore em ramificaусo.



			int v;
			int nCC = -1;
			vector<int> C;


            for (int i : T.V)
            {
                vector<int> listaC;
                set<int> listaCC;

                for (int u : G.Adjacentes(i))
                {
                    if (T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(i) && (InBT[u] == 1 || T.Grau(u) == 1)))
                    {
                        listaC.push_back(u);
                        listaCC.insert(T.CConexa(u));
                    }
                }

                if ((int)listaCC.size() > nCC)
                {
                    v = i;
                    nCC = listaCC.size();
                    C = listaC;
                }
            }

            if(C.size() > 0)
            {
                //Trasformar v em ramificaусo permite estabelecer novas conexшes:
                BT.push_back(v);
                InBT[v] = 1;

                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v))
                    {
                        T.AdicionarVertice(u);
                        T.AdicionarAresta(v,u);
						if(T.Grau(u) == 1)
                        {
                            Pontas.push(make_pair(-1 * G.Grau(u), u));
                            InPontas[u] = true;
						}
                    }
                }
            }
            else
            {
                int v;
                int nCC = -1;
                vector<int> C;

                for (int i : T.V)
                {
                    vector<int> listaC;
                    set<int> listaCC;

                    for (int u : G.Adjacentes(i))
                    {
                        if (T.CConexa(u) != T.CConexa(i))
                        {
                            listaC.push_back(u);
                            listaCC.insert(T.CConexa(u));
                        }
                    }

                    if ((int)listaCC.size() > nCC)
                    {
                        v = i;
                        nCC = listaCC.size();
                        C = listaC;
                    }
                }

                BT.push_back(v);
                InBT[v] = 1;

                /*
                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v))
                    {
                        BT.push_back(u);
						InBT[u] = 1;
                        T.AdicionarAresta(v,u);
                    }
                }
                */
            }
        }
    }
}
