#include "Roleta.h"
#include <iostream>

ItemRoleta::ItemRoleta(int k, double p)
{
	key = k;
	prob = p;
	lowerBound = 0;
	upperBound = 0;
	probCalc = 0;
}

Roleta::Roleta()
{
	soma = 0;
}

Roleta::~Roleta()
{
}

void Roleta::Adicionar(int key, double probabilidade)
{
	if (probabilidade < 0)
		itens.push_back(ItemRoleta(key, 0));
	else
		itens.push_back(ItemRoleta(key, probabilidade));
}

int Roleta::Sortear(int seed)
{
	double soma = 0;
	for (int i = 0; i < (int)itens.size(); i++)
		soma = soma + itens[i].prob;

	/*Seed Aleatória*/
	uniform_real_distribution<> rndInterval(0, 1); // Define a distribuição uniforme no intervalo [0, 1)	
	random_device rd; // Gera uma semente aleatória usando random_device
	unsigned long long seedaleatoria = rd();
	// std::ofstream seedFile("seed.txt", std::ios_base::app);
    // if (seedFile.is_open()) {
    //     seedFile << seed << std::endl;
    //     seedFile.close();
    // } else {
    //     std::cerr << "Erro ao abrir o arquivo de semente!" << std::endl;
    //     return 1;
    // }
	mt19937_64 gen(seedaleatoria); // Inicializa o gerador Mersenne Twister com a semente gerada
	double d = rndInterval(gen);

	/*Seed Fixa*/
	// uniform_real_distribution<> rndInterval(0, 1);
	// mt19937_64 gen(seed);
	// double d = rndInterval(gen);

    /*
	constexpr int FLOAT_MIN = 0;
    constexpr int FLOAT_MAX = 1;
    //srand(time(nullptr));
    double d = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
    */

	double step = 0;
	for (int i = 0; i < (int)itens.size(); i++)
	{
		itens[i].probCalc = itens[i].prob / soma;
		itens[i].lowerBound = step;
		itens[i].upperBound = step + itens[i].probCalc;
		step = step + itens[i].probCalc;

		if (d >= itens[i].lowerBound && d < itens[i].upperBound)
		{
			return itens[i].key;
		}
	}
	return itens[itens.size() - 1].key;
}