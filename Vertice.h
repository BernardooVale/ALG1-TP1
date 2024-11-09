#ifndef Vertice_HPP
#define Vertice_HPP

#include <string>
#include <vector>

using namespace std;

class Vertice{

private:
	int id;
	int conjunto;
	string nome;
	std::vector<int> caminhos;
	std::vector<int> caminhos_percorridos;
	std::vector<int> dists;
	bool batalhao;

public:

	Vertice(int id, string nome, int tamCidades);
	Vertice(int id, string nome, int tamCidades, int conjunto, bool batalhao);
	~Vertice();

	int pegaID();
	string pegaNome();
	int calcDistTotal();
	int grauVertice();
	int pegaAresta(int pos);
	int pegaDist(int pos);
	int pegaConjunto();
	bool eBatalhao();
	bool percorrido();
	bool verfPercorrido(int pos);

	void defID(int id);
	void defNome(string nome);
	void defConjunto(int conjunto);
	void defBatalhao();
	void defPercorrido(int pos);
	void adCaminho(int id);
	void defDist(int pos, int dist);
	void printDist();
	void tiraAresta(int i);
};

#endif