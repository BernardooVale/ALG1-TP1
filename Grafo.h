#ifndef Grafo_HPP
#define Grafo_HPP

#include "Vertice.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Grafo{

private:

	vector<Vertice> cidades;
	int idCapital;

public:
	Grafo();
	~Grafo();

	void adCidade(Vertice nova);
	void defCapital();
	void calcDists(Vertice* origem, Vertice atual, vector<int> percorridos, queue<Vertice> fila, int distAtual);

	void inverterGrafo();
	void ordemExec(stack<int>& pilhaExec);
	void percorre(stack<int>& pilhaExec, vector<int>& percorridos, Vertice* atual);
	void agrupador(Vertice* atual, int numConjunto);
	void defBat(int numConjuntos);
	int Kosaraju();
	int encBat(int pos);
	int pegaPos(int id);
	bool eEuleriano(Grafo invertido);
	bool equilibradoEnt(Grafo invertido, int pos);
	bool equilibradoSai(Grafo invertido, int pos);
	void euleriano();
	void patrulhamento(int numConjuntos);
	void Hierholzer(stack<string>& caminho, Vertice* atual);


	Vertice* achaCidadeID(int id);
	Vertice* achaCidadeString(string nome);

};

#endif

