#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>


using namespace std;

int main() {
    // Defina a seed explicitamente fora do loop while
    unsigned long long seedaleatoria = 100; // Aqui você pode usar o valor desejado
    std::mt19937_64 gen(seedaleatoria); // Inicialize o gerador de números aleatórios com a seed definida

    // Distribuição uniforme no intervalo [0, 1)
    std::uniform_real_distribution<> rndInterval(0, 1);

    for (int i = 0; i < 100; i++) {
        // Gerar um número aleatório
        double d = rndInterval(gen);
        cout << d << endl;
    }

    return 0;
}