#include "Lista.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include <stdlib.h>
#include <algorithm>

using namespace std;

//Construtor da lista que adiciona todas as arestas de um grafo
//e retorna o numero de vertices e arestas
Lista::Lista(string path){
    //Checa se o arquivo existe, se nao imprime uma mensagem de erro
    ifstream myFile;
    myFile.open(path);
    if(!myFile){
      cout << "Location not Found";
    }
    //Recebe a primeira linha do arquivo e guarda na variavel numero de vertices
    myFile >> m_numVertices;
    //Aloca espaco da estrutura ListInfo e preenche tudo com zero
    m_pLista = new ListInfo*[m_numVertices+1]();
    //Numero de arestas inicial igual a 0
    //Depois ocorre a leitura de cada linha do arquivo, adicionando as respectivas
    //arestas e incrementando o numero de arestas
    m_numArestas = 0;
    string s;
    while(getline(myFile, s)){
      if(s.empty() == false){
        istringstream tmp(s);                         //Leitura de Arquivo
        int v0 ,vf;
        tmp >> v0 >> vf;
        this->addAresta(v0, vf);
        this->addAresta(vf, v0);
        m_numArestas++;
      }
    //  cout << "sair do loop1" << endl;
    }
    //cout << "sair do loop2" << endl;
    //Grava no arquivo de saída o numero de vertices e arestas
    ofstream myOut;
    myOut.open (m_savePath + "/info.txt");
    myOut << "numero vertices:" << m_numVertices << endl;
    myOut << "numero arestas:" << m_numArestas << endl;
    myOut.close();
}

//Adiciona aresta na lista de adjacencia
void Lista::addAresta(int v0, int vf){
  //Nao precisa adicionar no m_pLista[vf] , porque chama o addAresta 2 vezes na leitura
  ListInfo* vizinho = new ListInfo;
  vizinho->vertice = vf;

  //se vertice v0 tem alguma aresta, adiciona o novo vizinho no inicio
  if (m_pLista[v0] != NULL) m_pLista[v0]->pPrev = vizinho;
  vizinho->pNext = m_pLista[v0];
  vizinho->pPrev = NULL;
  this->m_pLista[v0] = vizinho;

}

//Retorna os vizinhos de um vértice v, sendo vértice inicial igual a 0
vector<int> Lista::vizinhos(int v){
  //Vetor que guarda todos os vizinhos
  vector<int> vizinhos;
  //Cria strutura para percorrer a lista e a percorre adicionando os vizinhos
  //no vetor
  ListInfo* pCrawl = new ListInfo;
  pCrawl = m_pLista[v+1];
  while(pCrawl != NULL){
    vizinhos.push_back(pCrawl->vertice);
    pCrawl = pCrawl->pNext;
  }
  //for(int i=0;i<vizinhos.size();i++){
  //  cout << vizinhos[i] << endl;
  //}

  //Retorna o vetor de vizinhos
  return vizinhos;
}

//Retorna o vetor de explorados na BFS
vector<int> Lista::BFS(int raiz) {

  //clock_t begin = clock();
  //Inicio da escrita no arquivo destino
  ofstream myOut;
  myOut.open (m_savePath + "/BFS.txt");
  myOut << "start" << endl;

  //Como nossa função de vizinhos começa no vértice 0, o inteiro s, que será
  //a origem da BFS, recebe o parâmetro passado como raiz menos 1
	int s = raiz-1;
  //Inicializa e atribui valores aos vetores visitado, pai e nivel, além de
  //inicializar o vetor de explorados, que é o retorno da função, e uma fila
  //que será utilizada na nossa BFS
	vector<bool> visitado(m_numVertices,0);
	vector<int> pai(m_numVertices,-1);
	vector<int> nivel(m_numVertices,-1);
	vector<int> explorado;
	queue<int> fila;

  //Marca a raiz como visitada, atribui nivel zero e a adiciona na fila
	visitado[s] = 1;
	nivel[s] = 0;
	fila.push(s);

	cout << endl<< "BFS(" << raiz << ") Rodando..." << endl;

  //Loop principal da BFS. Pega o primeiro da fila, retira ele dela, acha seus
  //vizinhos. Depois itera pelo vetor de vizinhos e acrescenta as informações
  //de visitado, pai e nivel, além de inserir o vértice na fila.
	while(!fila.empty()){
		int v = fila.front();
		fila.pop();
    vector<int> w = vizinhos(v);
    //cout << w.size() << endl;
    for(int i = 0;i< w.size();i++){
      if(visitado[w[i]-1] == 0) {
        visitado[w[i]-1] = 1;
        pai[w[i]-1] = v;
        nivel[w[i]-1] = nivel[v]+1;
        fila.push(w[i]-1);
        }
      }
    //cout << v << endl;
    //cout << v << endl;

    //Adiciona o vértice ao vetor explorado depois do loop
    explorado.push_back(v);
  }
  //Escreve no arquivo de saída o vértice, seu pai e seu nivel
  for(int i=0;i<explorado.size();i++){
    myOut << "vertice: "<< explorado[i] << ": pai:"<< pai[explorado[i]] << " nivel:" << nivel[explorado[i]] << endl;
  }
  //Retorno do vetor explorados
  return explorado;
}


/*
void Lista::Grau(){
  vector<int> vetorGrau = {0,100000000,0};
  int count = 0;
  ListInfo* aux = new ListInfo;
  int avg = 0;
  for (int i=1;i<=m_numVertices;i++){
    aux = m_pLista[i]->pNext;
    while(aux != NULL){
      aux = aux->pNext;
      count++;
    }
    avg = avg + count;
    if (count > vetorGrau[0]) {vetorGrau[0] = count+1;}
    if (count < vetorGrau[1]) {vetorGrau[1] = count+1;}
    count = 0;
  }
  ofstream myOut;
  myOut.open (m_savePath + "/grau.txt");
  myOut << "GrauMax: " << vetorGrau[0] << endl;
  myOut << "GrauMin:" << vetorGrau[1] << endl;
  myOut << "GrauMedio: " <<   (avg/m_numVertices)+1 << endl;
  // myOut << "GrauMediana: " << vetorGrau[3] << endl;
  myOut.close();
}*/

//Funcao que retorna os graus máximo, minimo, medio e mediana
void Lista::Grau2(){
  //Vetor de comparação para achar os graus máximo e mínimo
  vector<int> vetorGrau = {0, 10000000, 0};
  //Vetor que guarda todos os graus
  vector<int> graus(m_numVertices, 0);
  int count, avg = 0;
  int mediana;
  //Percorre todos os vertices, achando seus respectivos graus
  //Caso o vértice que está sendo analisado tenha maior grau do que o atual
  //maior grau no vetor de comparação, atualiza o vetor. O mesmo para o menor
  for (int i = 1; i<=m_numVertices;i++){
    vector<int> w = vizinhos(i-1);
    count = w.size();
    graus[i-1] = count;
    if (count > vetorGrau[0]) {vetorGrau[0] = count;}
    if (count < vetorGrau[1]) {vetorGrau[1] = count;}
    avg += count;
  }
  //Ordena o vetor com todos os graus e acha a mediana
  sort(graus.begin(), graus.end());
  if (m_numVertices%2){
    mediana = graus[m_numVertices/2];
  }else
  {
    mediana = (graus[m_numVertices/2] + graus[m_numVertices/2+1])/2;
  }

  //Escreve no arquivo de saida todas as informações
  ofstream myOut;
  myOut.open (m_savePath + "/grau.txt");
  myOut << "GrauMax: " << vetorGrau[0] << endl;
  myOut << "GrauMin:" << vetorGrau[1] << endl;
  myOut << "GrauMedio: " <<   (avg*1.0/m_numVertices) << endl;
  myOut << "GrauMediana: " << mediana << endl;
  myOut.close();
}

//Retorna o vetor de visitados da DFS a partir de um vértice indicado
vector<bool> Lista::DFS(int raiz) {

  //Assim como na BFS, nossa origem será a raiz definida no parametro menos 1,
  //uma vez que precisaremos da nossa função vizinhos e o vértice inicial dela
  //é zero
	int s = raiz-1;
	//Inicialização dos vetores visitado, pai, nivel e pilha
	vector<bool> visitado(m_numVertices,0);
	vector<int> pai(m_numVertices,-1);
	vector<int> nivel(m_numVertices,-1);
	stack<int> pilha;

  //Inicio do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/DFS.txt");
  myOut << "start" << endl;

	//visitado[s] = 1;
  //int count;
  //Atribui a raiz nivel 0 e o insere na pilha
	nivel[s] = 0;
	pilha.push(s);
  cout << endl<< "DFS(" << raiz << ") Rodando..." << endl;

  //Loop principal da DFS que percorre a pilha enquanto ela não estiver vazia.
  //Pega o vértice topo da pilha, o retira dela e verifica se já foi visitado.
  //Em caso positivo, escreve no arquivo de destino suas informações. Caso
  //contrário, é marcado como visitado e percorre seus vizinhos, definindo
  //seus pais e niveis
	while(!pilha.empty()) {
		int v = pilha.top();
		pilha.pop();
    if (visitado[v]==0){
      myOut << "Vertice: " << v << ", Nivel: " << nivel[v] << ", Pai: " << pai[v] << endl;
      visitado[v]=1;
      vector<int> w = vizinhos(v);
      for(int i = 0; i < w.size();i++){
        pilha.push(w[i]-1);
          int n = pilha.top();
          pai[n] = v;
          nivel[n] = nivel[v] + 1;
        }
      }
    }

  //Retorno do vetor visitados
	return visitado;
}


//Funcao para achar as componentes conexas de um grafo. Ainda está incorreta
void Lista::CC(){
  //Vetor que se refere ao numero da componente
  vector<int> id(m_numVertices, -1);
  //Vetor de visitados
  vector<bool> visitado(m_numVertices, 0);
  //Pilha da DFS
  stack<int> pilha;
  //Contador de componentes
  int count = 0;


  //Inicia arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/CC.txt");
  //DFS atualiza o id do vértice e aumenta o número de componentes
  for (int i = 0; i < m_numVertices; i++){
    if (id[i] == -1){
      pilha.push(i);
      while (!pilha.empty()){
        int v = pilha.top();
        pilha.pop();
        if (visitado[v]==0){
          visitado[v]=1;
          vector<int> w = vizinhos(v);
          for(int i = 0; i < w.size();i++){
            pilha.push(w[i]-1);
            int n = pilha.top();
            //Atualizando id do vértice
            id[n] = count;
            }
          }
      }
      //Aumentando número de componentes
      count++;
    }

  }
  //Escreve número de componentes no arquivo de saída
  myOut << "Numero de componentes: " << count << endl;
  //Variavel auxiliar
  int aux = 0;
  //Vetor de vetores para salvar as componentes
  vector< vector<int> > componentes;

  //Loop que adiciona no vetor de vetores cada componente
  while (componentes.size() != count){
    //Vetor temporario que recebe uma componente
    vector<int> temp;
    for (int i = 0; i < m_numVertices; i++){
      //Se o id do vértice é igual a variavel auxiliar, adiciona o vértice
      //em temp, ou seja, adiciona todos os vértices com mesma id no vetor
      if (id[i] == aux){
        temp.push_back(i);
      }
    }
    //Adiciona temp no vetor de componentes
    componentes.push_back(temp);
    //Incrementa variavel auxiliar para verificação do id
    aux++;
  }

  //Loop de escrita de cada componente no arquivo de saída
  for (int i = 0; i < componentes.size();i++){
    myOut << "Componente " << i+1 << ": ";
    for (int j = 0; j < componentes[i].size();j++){
       myOut << componentes[i][j] + 1 << ", ";
    }
    myOut << endl;
  }
  }


//Destrutor da lista
Lista::~Lista(){
    ListInfo* aux;
    for(int i=1;i<=m_numVertices;i++){
        for(ListInfo* neigh = m_pLista[i]; neigh != NULL;){
          aux = neigh;
          neigh=neigh->pNext;
          delete aux;
          }
    }
  delete[] m_pLista;
}
