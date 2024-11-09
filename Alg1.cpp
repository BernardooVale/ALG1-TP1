// Alg1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#include "Grafo.h"
#include "Vertice.h"

using namespace std;

int main(){

    int numCidades, numCaminhos, numConjuntos;
    string nome, origem, destino;
    Grafo grafo;

    cout << "Digite %d num cidades e %d num caminhos" << endl;
    cin >> numCidades >> numCaminhos;

    for (int i = 0; i < numCidades; i++) {
        cout << "Digite o nome da cidade" << endl;
        cin >> nome;
        Vertice aux(i, nome, numCidades);
        grafo.adCidade(aux);
    }

    for (int i = 0; i < numCaminhos; i++) {
        cout << "Digite %s nome da cidade origem e %s nome da cidade destino" << endl;
        cin >> origem >> destino;
        grafo.achaCidadeString(origem)->adCaminho(grafo.achaCidadeString(destino)->pegaID());
    }

    grafo.defCapital();
    numConjuntos = grafo.Kosaraju();
    grafo.patrulhamento(numConjuntos);

    grafo.~Grafo();
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
