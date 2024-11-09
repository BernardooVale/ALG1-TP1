
#include <iostream>
#include <queue>
#include <stack>

#include "Grafo.h"

#define INT_MAX 2147483647

Grafo::Grafo() {

	this->idCapital = -1;
}

Grafo::~Grafo() {
	this->cidades.clear();
}

void Grafo::adCidade(Vertice nova) {
	this->cidades.push_back(nova);
}

Vertice* Grafo::achaCidadeID(int id) {
	
	for (int i = 0; i < this->cidades.size(); i++)
		if (this->cidades[i].pegaID() == id) 
			return &this->cidades[i];
}

Vertice* Grafo::achaCidadeString(std::string nome) {

	for (int i = 0; i < this->cidades.size(); i++)
		if (this->cidades[i].pegaNome() == nome)
			return &this->cidades[i];
}

void Grafo::defCapital() {

	int dist_min = INT_MAX; //menor distancia
	int cidadeID = 0; //id da cidade com menor distancia

	for (int i = 0; i < this->cidades.size(); i++) { //calcula as distancias entre as cidades para todas as cidades

		std::vector<int> percorridos(this->cidades.size(), 0);
		std::queue<Vertice> fila;
		this->calcDists(&this->cidades[i], this->cidades[i], percorridos, fila, 0);
	}

	for (int i = 0; i < this->cidades.size(); i++) { //verifica qual cidade tem menor custo, O(n)

		if (this->cidades[i].calcDistTotal() < dist_min && this->cidades[i].calcDistTotal() != -1) {
			dist_min = this->cidades[i].calcDistTotal();
			cidadeID = this->cidades[i].pegaID();
		}

	}

	if (dist_min == INT_MAX) {
		std::cout << "Nao ha capital disponivel" << std::endl;
	}
	else {
		this->idCapital = cidadeID;
		std::cout << this->cidades[cidadeID].pegaNome() << std::endl; // Escreve o nome da capital
	}
}

void Grafo::calcDists(Vertice* origem, Vertice atual, std::vector<int> percorridos, std::queue<Vertice> fila, int distAtual) {

	if (!fila.empty()) fila.pop(); // se a fila nao estiver vazia, tira o primeiro item,ja que e ele que esta em escopo

	percorridos[atual.pegaID()] = 1; // define o vertice como visitado

	for (int i = 0; i < atual.grauVertice(); i++) { // Para cada cidade adjacente, calcula a nova distancia

		if ((origem->pegaDist(atual.pegaAresta(i)) > distAtual + 1 || origem->pegaDist(atual.pegaAresta(i)) == 0) && // Se a distancia for menor,
			atual.pegaAresta(i) != origem->pegaID()) // e nao for a origem
				origem->defDist(atual.pegaAresta(i), distAtual + 1); // atualiza
		
		
		if (percorridos[atual.pegaAresta(i)] != 1) // se o vertice adjacente nao foi visitado
			fila.push(this->cidades[atual.pegaAresta(i)]); // adiciona o vertice adjacente na fila
	}

	distAtual++;
	if (!fila.empty()) { // se a fila nao estiver vazia
		this->calcDists(origem, fila.front(), percorridos, fila, distAtual); // chama o proximo da fila
	}
}

void Grafo::ordemExec(std::stack<int>& pilhaExec) {

	std::vector<int> percorridos(this->cidades.size(), 0);

	for (int i = 0; i < this->cidades.size(); i++) // para todo vertice
		if (percorridos[i] == 0) //caso ele nao tenha sido visitado
			this->percorre(pilhaExec, percorridos, &this->cidades[i]); // percorre todos os caminhos possiveis a partir dele
}

void Grafo::percorre(std::stack<int>& pilhaExec, std::vector<int>& percorridos, Vertice* atual) {

	percorridos[atual->pegaID()] = 1; // vertice percorrido

	for (int i = 0; i < atual->grauVertice(); i++) //para toda aresta deste vertice
		if (percorridos[atual->pegaAresta(i)] == 0) // se o vertice "destino" nao foi visitado ainda
			this->percorre(pilhaExec, percorridos, &this->cidades[atual->pegaAresta(i)]); // chama a mesma funcao, mas para o proximo vertice (como uma DFS)

	pilhaExec.push(atual->pegaID()); // adiciona o vertice na pilha de execucao
}

void Grafo::inverterGrafo() {

	std::vector<int> graus;

	for (int i = 0; i < this->cidades.size(); i++) {
		graus.push_back(this->cidades[i].grauVertice()); // armazena o grau dos vertices
	}

	for (int i = 0; i < this->cidades.size(); i++) { // para todo vertice

		Vertice* atual = &this->cidades[i];
		for (int j = 0; j < graus[i]; j++) { // para toda aresta original desse vertice

			Vertice* destino = &this->cidades[this->pegaPos(atual->pegaAresta(0))];
			destino->adCaminho(atual->pegaID());
			atual->tiraAresta(0); // remove a aresta antiga
		}
	}
}

void Grafo::agrupador(Vertice* atual, int numConjuntos) {

	for (int i = 0; i < atual->grauVertice(); i++){ // para cada aresta

		Vertice* destino = &this->cidades[atual->pegaAresta(i)];

		if (destino->pegaConjunto() == 0) { // verifica se o destino nao tem conjunto
			destino->defConjunto(numConjuntos);
			this->agrupador(destino, numConjuntos); //mesma funcao para o proximo vertice
		}
	}
}

void Grafo::defBat(int numConjuntos) {

	std::vector<int> batalhoes(numConjuntos, 0);

	batalhoes[this->cidades[this->idCapital].pegaConjunto() - 1] = 1;

	for (int i = 0; i < this->cidades.size(); i++) { // para todo vertice
		if (batalhoes[this->cidades[i].pegaConjunto() - 1] == 0) { // ve se um batalhao ja foi alocado para esse conjunto
			this->cidades[i].defBatalhao(); // se nao foi, define como batalhao
			batalhoes[this->cidades[i].pegaConjunto() - 1] = 1; // batalhao para conjunto alocado
		}
	}
}

int Grafo::Kosaraju() {

	std::stack<int> pilhaExec;

	this->ordemExec(pilhaExec); // descobre o temppo de execucao de cada vertice e adiciona na pilha
	this->inverterGrafo(); //inverte o grafo

	int numConjuntos = 0;

	while (!pilhaExec.empty()) {

		Vertice* atual = &this->cidades[pilhaExec.top()];

		if (atual->pegaConjunto() == 0) { // coloca todos os vertices alcancaveis, a partir do atual, em um mesmo conjunto (fortemente conectados)
			numConjuntos++;
			atual->defConjunto(numConjuntos);
			this->agrupador(atual, numConjuntos);
		}

		pilhaExec.pop();
	}

	this->inverterGrafo(); // desinverte o grafo
	std::cout << "Numero minimo de batalhoes: " << numConjuntos - 1;
	defBat(numConjuntos);
	return numConjuntos;
}

int Grafo::encBat(int pos) {

	while (pos < this->cidades.size()) { // enquanto todos os vertices nao tenham sido percorridos
		if (this->cidades[pos].eBatalhao() || this->cidades[pos].pegaID() == this->idCapital) { // se o vertice e batalhao ou capital
			return pos; // retorna o id dele
		}
		pos++;
	}
}

int Grafo::pegaPos(int id) {

	for (int i = 0; i < this->cidades.size(); i++)
		if (this->cidades[i].pegaID() == id)
			return i;
}

bool Grafo::eEuleriano(Grafo invertido) { //

	for (int i = 0; i < this->cidades.size(); i++)
		if (this->cidades[i].grauVertice() != invertido.cidades[i].grauVertice())
			return false;

	return true;
}

bool Grafo::equilibradoEnt(Grafo invertido, int pos) {

	return this->cidades[pos].grauVertice() < invertido.cidades[pos].grauVertice() ? false : true; // mais entrando q saindo
}

bool Grafo::equilibradoSai(Grafo invertido, int pos) {

	return this->cidades[pos].grauVertice() > invertido.cidades[pos].grauVertice() ? false : true; // mais saindo q entrando
}

void Grafo::euleriano() {

	Grafo invertido = *this;
	invertido.inverterGrafo(); // grafo invertido para medir balanceamento

	while (!this->eEuleriano(invertido)){ // enquanto o grafo nao for euleriano

		for (int i = 0; i < this->cidades.size(); i++) { // para todos os vertices
			if (!this->equilibradoEnt(invertido, i)) { // caso ele tenha poucas saidas
				Vertice* atual = &this->cidades[i];

				int modificado = 0;

				for (int j = 0; j < atual->grauVertice(); j++) { // para todos os vertices
					if (!this->equilibradoSai(invertido, this->pegaPos(atual->pegaAresta(j)))) { // da preferencia para os que nao estejam equilibrados na saida
						atual->adCaminho(atual->pegaAresta(j));
						invertido.cidades[this->pegaPos(atual->pegaAresta(j))].adCaminho(atual->pegaID());
						modificado = 1;
					}
				}

				if (modificado == 0) {
					for (int j = 0; j < atual->grauVertice(); j++) { // para todos os vertices
						if (this->equilibradoEnt(invertido, this->pegaPos(atual->pegaAresta(j)))) { // da preferencia para os que estejam equilibrados
							atual->adCaminho(atual->pegaAresta(j));
							invertido.cidades[this->pegaPos(atual->pegaAresta(j))].adCaminho(atual->pegaID());
							modificado = 1;
						}
					}
				}

				if (modificado == 0) { //ultimo caso
					atual->adCaminho(atual->pegaAresta(0));
					invertido.cidades[this->pegaPos(atual->pegaAresta(0))].adCaminho(atual->pegaID());
				}
			}
		}
	}
}

void Grafo::patrulhamento(int numConjuntos) {

	int conjuntosPercorridos = 1;

	while (conjuntosPercorridos <= numConjuntos){ // enquanto nao tenha patrulha para todos os conjuntos

		Grafo grafoAux;
		int idBatalhao = 0;

		for (int i = 0; i < this->cidades.size(); i++) {
			if (this->cidades[i].pegaConjunto() == conjuntosPercorridos) { // pega os vertices do conjunto

				if (this->cidades[i].eBatalhao() || this->cidades[i].pegaID() == this->idCapital) //marca posicao de inicio do Hierholzer
					idBatalhao = this->cidades[i].pegaID();

				Vertice* original = &this->cidades[i];
				Vertice aux(original->pegaID(), original->pegaNome(), 0, original->pegaConjunto(), original->eBatalhao()); // cria uma copia quase igual

				for (int j = 0; j < original->grauVertice(); j++) { //para todos as arestas do vertice original
					if (this->cidades[original->pegaAresta(j)].pegaConjunto() == aux.pegaConjunto()) { //se o vertice destino for do mesmo conjunto que o vertice atual
						aux.adCaminho(original->pegaAresta(j)); // adiciona a aresta no vertice copiado
					}
				}
				grafoAux.adCidade(aux); // adiciona o novo vertice ao novo grafo
			}
		}

		std::stack<std::string> caminho;

		grafoAux.euleriano();
		grafoAux.Hierholzer(caminho, grafoAux.achaCidadeID(idBatalhao));

		std::cout << std::endl;
		while (caminho.size() > 1){
			std::cout << caminho.top() << " ";
			caminho.pop();
		}

		conjuntosPercorridos++;
	}
}

void Grafo::Hierholzer(stack<string>& caminho, Vertice* atual) {

	//std::cout << "Nome vertice atual: " << atual->pegaNome() << std::endl;

	for (int i = 0; i < atual->grauVertice(); i++) {
		//std::cout << "Nome vertice destino " << this->achaCidadeID(atual->pegaAresta(i))->pegaNome() << std::endl;
		if (!atual->verfPercorrido(i)) {
			//std::cout << "Nao percorrido" << std::endl;
			atual->defPercorrido(i);
			this->Hierholzer(caminho, this->achaCidadeID(atual->pegaAresta(i)));
		}
	}
	//std::cout << "nome entrando na pilha " << atual->pegaNome() << std::endl;
	caminho.push(atual->pegaNome());
}