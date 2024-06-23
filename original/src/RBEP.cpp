#include "RBEP.h"
#include <algorithm>
#include <iostream>

#include "Roleta.h"

RBEP::RBEP(const Grafo& pG):
    G(pG), T(pG.n,pG.m), InBT(G.n, 0), InPontas(G.n, false)//, RemPontas(G.n, false)
{
    //constructor
    G.nome = "G";
    T.nome = "T";
}

RBEP::~RBEP()
{
    //destructor
}

Grafo RBEP::ObterArvore() const
{
    return T;

}

vector<int> RBEP::ObterBranches() const
{
    return BT;
}

vector<int> RBEP::ObterGrauBT() const
{
    vector<int> GrauBT;
    for (int v : BT)
    {
        GrauBT.push_back(T.Grau(v));
    }
    return GrauBT;
}

//Algoritmo Árvore Geradora - V4.3 - Primeira Heurística Randomizada
void RBEP::Oliveira()
{
    int excessao = 0;
    cout << endl;
    cout << endl;

    cout << "************  INICIALIZAÇÃO ALGORITMO R-BEP  ************" <<endl;
    BT.clear();
    //while (!Pontas.empty()) Pontas.pop();

    for (int i = 0; i < G.n; i++)
    {
        InBT[i] = 0;
        InPontas[i] = false;
        //RemPontas[i] = false;
    }

    //Detectar articulações e pontes com DFS.
    G.DetectarArticulacoesEPontes();
    cout << endl;
    cout << "****  PRÉ-PROCESSAMENTO INIT  ****" << endl;
    cout << endl;
    cout << "ADD in T:" << endl;

    for(int v : G.ArticulacoesW2)
    {   
        cout << "  - BT = " << v + 1 << endl;
        T.AdicionarVertice(v); //Adicionar vértices na Árvore.
        BT.push_back(v); //Considera que todos são ramificações da árvore.
        InBT[v] = 1; //Marca o vértice como uma ramificação.
    }

    //Tratar Pontes:
    for(pair<int,int> vu : G.Pontes)
    {
        int v = vu.first;
        int u = vu.second;
        cout << "  - PONTE = " << v  + 1 << " -- " << u  + 1 << endl;      
        T.AdicionarVertice(v);
        T.AdicionarVertice(u);

        T.AdicionarAresta(v,u);

        if (T.Grau(v) > 2 && InBT[v] == 0)
        {
            cout << "    - BT*= " << v + 1 << endl;
            BT.push_back(v);
            InBT[v] = 1;
        }

        if (T.Grau(u) > 2 and InBT[u] == 0)
        {
            cout << "    - BT*= " << u + 1 << endl;
            BT.push_back(u);
            InBT[u] = 1;
        }
    }
    cout << endl;

    //Tratar vértices marcados como ramificações da Árvore:
    cout << "Expansão INIT" << endl;
    for(int v : BT)
    {   
        cout << "  BT atual: " << v + 1 << endl;
        for(int u : G.Adjacentes(v))
        {   
            if(T.BuscarVertice(u) == false)
            {   
                cout << "    - "<< v  + 1 << " -- " << u  + 1 << endl; 
                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
            }
            else
            {
                if ((T.Grau(u) == 1 || InBT[u] == 1) && T.CConexa(v) != T.CConexa(u))
                {   
                    cout << "    - "<< v  + 1 << " -- " << u  + 1 << endl; 
                    T.AdicionarAresta(v,u);
                }
            }
        }
    }
    cout << "Expansão END" << endl;
    cout << endl;

    cout << "Pontas LIST" << endl;
    //Verificar quais caminhos pode ser explorados:
    for(int v : T.V)
    {
        if(T.Grau(v) == 1 && G.Grau(v) > 1)
        {
            //Pontas.push(make_pair(-1 * G.Grau(v), v));
            InPontas[v] = true;
            Pontas.insert(v);
            cout <<"  - "<< v  + 1 << endl; 
        }
        
    }


    //Se nenhuma ponta foi identificada, cria uma nova:
    if(Pontas.empty())
    {   
        cout << "Pontas == NULO" << endl;
        int v = G.VerticeGrauMinimo();
        int u = G.AdjacenteGrauMinimo(v);
        cout << "Add in T" << endl;

        T.AdicionarVertice(v);
        T.AdicionarVertice(u);
        T.AdicionarAresta(v,u);
        cout << "  -" << v + 1 << endl;
        cout << "  -" << u + 1 << endl;
        cout << "  -" << v + 1 << " -- " << u+1 << endl;

        //Pontas.push(make_pair(-1 * G.Grau(v), v));
        InPontas[v] = true;
        Pontas.insert(v);

        //Pontas.push(make_pair(-1 * G.Grau(u), u));
        InPontas[u] = true;
        Pontas.insert(u);
        
    }

    cout << "Pontas END" << endl;
    cout << endl;

    cout<< "****  PRÉ-PROCESSAMENTO END  ****" << endl;

    cout << endl;
    cout << endl;

    //Continuação
    cout<< "****       R-BEP INIT       ****" << endl;
    cout << endl;

    while(T.NumeroArestas() < G.n - 1)
    {
        if(Pontas.empty() == false)
        {
           
            int v;
            int grauMax = 0;

            Roleta R = Roleta();
            // cout << "ROLETA 1 - INIT" << endl;

            for(int i : Pontas)
            {
                if(G.Grau(i) > grauMax)
                {
                    grauMax = G.Grau(i);
                }
            }
            grauMax = grauMax + 1;


            // cout << " - GrauMax = " << grauMax << endl;
            // cout << endl;
            // cout << "Add Pontas Roleta 1" << endl;

            for(int p : Pontas)
            {
                double peso = grauMax - G.Grau(p);
                // cout << " - " << p + 1 << " [Peso: "<< peso << "]" << endl;
                
                R.Adicionar(p, peso);
            }
            v = R.Sortear();
            // cout << "Ponta Sorteada: " << v+1 << endl;
            // cout << endl;

            Pontas.erase(v);
            InPontas[v] = false;
            cout << "- REMOVED PONTA: " << v+1 << endl;

            /*
                Salvando todos os adjacentes do Vértice V
                que foi sorteado no vector.
            */
            vector<pair<int,pair<int,int>>> Nv;
            for(int u : G.Adjacentes(v))
                if(T.BuscarVertice(u) == false || (T.CConexa(u) != T.CConexa(v) && 
                (InBT[u] == 1 || T.Grau(u) == 1))){
                    
                    Nv.push_back(make_pair(u, make_pair(G.Grau(u), T.Grau(u))));

                }

            if(Nv.empty() == false)
            {
                int du_G;// = G.n + 1;
                int du_T;// = G.n + 1;
                int u;
                int grauMax2 = 0;

                Roleta R = Roleta();

                for(pair<int,pair<int,int>> j : Nv)
                {
                    du_G = j.second.first;
                    if(du_G > grauMax2)
                    {
                        grauMax2 = du_G;
                    }
                }
                grauMax2 = grauMax2 + 1;

                for(pair<int,pair<int,int>> i : Nv)
                {
                    u = i.first;
                    du_G = i.second.first;
                    du_T = i.second.second;

                    if(du_T == 0)
                    {
                        du_G = du_G - 1;
                    }
                    double peso = grauMax2 - du_G;
                    R.Adicionar(u, peso);

                }
                u = R.Sortear();

                T.AdicionarVertice(u);
                T.AdicionarAresta(v,u);
                cout << "- ADD EDGE     : " << v  + 1 << " -- " << u  + 1 << endl; 

                
				if (T.Grau(u) == 1)
                {
                    InPontas[u] = true;
                    Pontas.insert(u);
                }
				else
                {
                    if(InPontas[u] == true)
                    {
                        Pontas.erase(u);
                        InPontas[u] = false;
                    }
                }
            }
        }
        else
        {
            //Não existe uma nova ponta para ser explorada: necessário converter um vértice da árvore em ramificação.
            cout << endl;
            cout << "Pontas == NULL" << endl;
			
            int v;
			int nCC = -1;
			vector<int> C;


            for (int i : T.V) // Todos os vértices da arvore atual.
            {   
                vector<int> listaC;
                set<int> listaCC;

                for (int u : G.Adjacentes(i)) 
                {
                    /*
                    Salvar todos os vértices adjacentes de 
                    i que se adequam nesses critérios.
                    */
                    if (T.BuscarVertice(u) == false || 
                        (T.CConexa(u) != T.CConexa(i) && 
                        (InBT[u] == 1 || T.Grau(u) == 1)))
                    {
                        listaC.push_back(u);
                        listaCC.insert(T.CConexa(u));
                    }
                }

                //Salvar o vértice com a maior quantidade de opções.
                if ((int)listaCC.size() > nCC)
                {
                    v = i;
                    nCC = listaCC.size();
                    C = listaC;
                }
            }

            if(C.size() > 0) //Se existir vértice que tenha opções que possa ser escolhida
            {   
                //Trasformar v em ramificação permite estabelecer novas conexões:
                cout << "  CC > 0" << endl;
                cout << "    ADD int T: " << endl;
                cout << "      - BT = " << v + 1 << endl;

                BT.push_back(v);
                InBT[v] = 1;
                cout << "    Expansão NEW BT INIT" << endl;
                for(int u : C)
                {
                    if(T.CConexa(u) != T.CConexa(v)) //Expansão desse novo vértice
                    {
                        T.AdicionarVertice(u);
                        T.AdicionarAresta(v,u);
                        cout << "      - " << v  + 1 << " -- " << u  + 1 << endl; 

						if(T.Grau(u) == 1)
                        {
                            InPontas[u] = true;
                            Pontas.insert(u); //Atualização de Pontas
						}
                    }
                }
                cout << "    Expansão END" << endl;
                cout << endl;

            }
            else
            {   
                excessao++;

                cout << "  CC <= 0" << endl;

                int v;
                int nCC = -1;
                vector<int> C;

                for (int i : T.V) // Todos os vértices de V
                {
                    vector<int> listaC;
                    set<int> listaCC;

                    for (int u : G.Adjacentes(i)) //Adjacentes de V no grafo.
                    {
                        if (T.CConexa(u) != T.CConexa(i)) // Ainda não estão conectados
                        {
                            listaC.push_back(u);
                            listaCC.insert(T.CConexa(u));
                        }
                    }

                    if ((int)listaCC.size() > nCC) //Seleciona o maior
                    {
                        v = i;
                        nCC = listaCC.size();
                        C = listaC;
                    }
                }
                //Torna esse novo vetor uma ramificação.
                BT.push_back(v);
                InBT[v] = 1;
                cout << "    ADD int T: " << endl;
                cout << "      - BT = " << v + 1 << endl;
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
    cout << excessao << endl;
    cout << endl;
    cout<< "****       R-BEP END        ****" << endl;
    cout << endl;
}

