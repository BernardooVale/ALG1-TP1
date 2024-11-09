#include "Vertice.h"

#include <iostream>

#define INT_MAX 2147483647

Vertice::Vertice(int id, std::string nome, int tamCidades) {
	
	this->id = id;
	this->nome = nome;
	std::vector<int> novo(tamCidades, 0);
	this->dists = novo;
	this->conjunto = 0;
	this->batalhao = false;
}

Vertice::Vertice(int id, std::string nome, int tamCidades, int conjunto, bool batalhao) {

	this->id = id;
	this->nome = nome;
	std::vector<int> novo(tamCidades, 0);
	this->dists = novo;
	this->conjunto = conjunto;
	this->batalhao = batalhao;
}

Vertice::~Vertice() {}

int Vertice::pegaID() { return this->id; }
std::string Vertice::pegaNome() { return this->nome; }
int Vertice::grauVertice() { return this->caminhos.size(); }
int Vertice::pegaAresta(int pos) { return this->caminhos[pos]; }
int Vertice::pegaDist(int pos) { return this->dists[pos]; }
int Vertice::pegaConjunto() { return this->conjunto; }
bool Vertice::eBatalhao() { return this->batalhao; }
bool Vertice::percorrido() {

	for (int i = 0; i < this->caminhos_percorridos.size(); i++) {
		if (this->caminhos_percorridos[i] == 0) {
			return false;
		}
	}
	return true;
}
bool Vertice::verfPercorrido(int pos) { return (this->caminhos_percorridos[pos] == 1 ? true : false); }

void Vertice::defID(int id) { this->id = id; }
void Vertice::defNome(std::string nome) { this->nome = nome; }
void Vertice::defConjunto(int conjunto) { this->conjunto = conjunto; }

void Vertice::adCaminho(int id) {

	this->caminhos.push_back(id);
	this->caminhos_percorridos.push_back(0);
}

void Vertice::defDist(int pos, int dist) { this->dists[pos] = dist; }
void Vertice::tiraAresta(int i) { this->caminhos.erase(this->caminhos.begin() + i); }
void Vertice::defBatalhao() { this->batalhao = true; }
void Vertice::defPercorrido(int pos) { this->caminhos_percorridos[pos] = 1; }

int Vertice::calcDistTotal() {

	int dist = 0;
	for (int i = 0; i < this->dists.size(); i++) {

		if (this->dists[i] == 0 && i != this->id) { // se a distancia for 0, o vertice nao e alcansavel
			dist = -1;
			return dist;
		}

		dist += this->dists[i];
	}
	return dist;
}

void Vertice::printDist() {
	for (int i = 0; i < this->dists.size(); i++) {
		std::cout << this->dists[i] << " ";
	}
	std::cout << std::endl;
}