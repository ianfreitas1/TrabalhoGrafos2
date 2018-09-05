#include "Matriz.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <new>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;


//Construtor da matriz
Matriz::Matriz(string path){
  //cout << "antes" << endl;

  //Verifica se o arquivo passado como parâmetro existe, caso contrário exibe
  //uma mensagem de erro
  ifstream myFile;
  myFile.open(path);
  if(!myFile){
    cout << "Location not Found";
  }
  myFile >> m_numVertices;

  //Inicia processo de escrita no arquivo de saída
  ofstream myOut;
  myOut.open ("output/info.txt");
  myOut << "Mnumero vertices:" << m_numVertices << endl;

  //Alocacao da matriz na memória
  m_Matriz = new bool*[m_numVertices+1];
  for (int i=0;i<m_numVertices+1;i++){
    m_Matriz[i] = new bool[m_numVertices+1];
  }

  //Seta todos os valores da matriz como zero
  for (int i = 0; i <= m_numVertices; i++){
    for (int j = 0; j <= m_numVertices; j++){
      //  if ((i%10 and j%10) == 0){cout<<"test"<<i<<j<<endl;};
      m_Matriz[i][j] = false;
    }
  }

  //Numero de arestas inicial igual a zero
  m_numArestas = 0;
  string s;
  //Percorre cada linha do arquivo, verificando os vértices e suas adjacências,
  //adicionando suas respectivas arestas na matriz e incrementa o numero de arestas
  while(getline(myFile, s)){
    if(s.empty() == false){
      //Leitura de Arquivo
      istringstream tmp(s);
      int v0, vf;
      tmp >> v0 >> vf;
      m_Matriz[v0][vf] = true;
      m_Matriz[vf][v0] = true;
      // this->addAresta(v0, vf);
      // this->addAresta(vf, v0);
      m_numArestas++;
    }
  }
  cout << "sair do loop2" << endl;

  //ofstream myOut;
  //myOut.open ("output/info.txt");
  //myOut << "Mnumero vertices:" << m_numVertices << endl;

  //Escreve o numero de arestas total no arquivo de saída
  myOut << "Mnumero arestas:" << m_numArestas << endl;
  myOut.close();
}

//Funcao que adiciona uma aresta na matriz, setando como true
void Matriz::addAresta(int v0, int vf){
      m_Matriz[v0][vf] = true;
}

//Retorna os vizinhos do vertice v, sendo vertice inicial igual a 1
vector<int> Matriz::vizinhos(int v){

  //Criação do vetor de vizinhos
  vector<int> vizinho;

  //Percorre a linha de adjacências do vértice passado como parâmetro e adiciona
  //no vetor de vizinhos caso exista a adjacência
  for (int i = 0; i <= m_numVertices; i++){
    if (m_Matriz[v][i] == true){
      vizinho.push_back(i);
    }
  }
  //for(int i=0;i<vizinho.size();i++){
  //  cout << vizinho[i] << endl;
  //}
  //cout << vizinho.size();

  //Retorna o vetor de vizinhos
  return vizinho;
}
/*
void Matriz::Grau()
{
  int aux2 = 0;
  vector<int> vetorGrau = {0,10000000,0};
  for(int i=0; i < m_numVertices; i++){
    for(int j=0; j < m_numVertices; j++){
      if (m_Matriz[i][j] = true){
        aux2++;
      }
    }
    if (aux2 > vetorGrau[0]) {vetorGrau[0] = aux2;}
    cout << aux2 << endl;
    aux2 = 0;
  }
  ofstream myOut;
  myOut.open ("output/grau.txt");
  myOut << "GrauMax: " << vetorGrau[0] << endl;
}*/

//Funcao que retorna os graus máximo, minimo, medio e mediana
void Matriz::Grau2(){
  //Vetor de comparação para achar os graus máximo e mínimo
  vector<int> vetorGrau = {0, 10000000, 0};
  //Vetor que guarda todos os graus
  vector<int> graus(m_numVertices, 0);
  int count, avg = 0;
  int mediana;
  //Percorre todos os vertices, achando seus respectivos graus
  //Caso o vértice que está sendo analisado tenha maior grau do que o atual
  //maior grau no vetor de comparação, atualiza o vetor. O mesmo para o menor
  for (int i = 0; i<m_numVertices;i++){
    vector<int> w = vizinhos(i+1);
    count = w.size();
    graus[i] = count;
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

//Retorna o vetor de visitados da BFS a partir de um vértice indicado
vector<bool> Matriz::DFS(int raiz) {

  //Diferentemente da lista, na matriz nosso vetor de vizinhos começa em 1;
  //Assim, inicializamos a variável s, origem da DFS, como a raiz passada como
  //parâmetro
	int s = raiz;
	//Inicializa vetores de visitado, pai, nivel e a pilha da DFS
	vector<bool> visitado(m_numVertices,0);
	vector<int> pai(m_numVertices,-1);
	vector<int> nivel(m_numVertices,-1);
	stack<int> pilha;
  //vector<int> explorado;

  //Inicio da escrita no arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/DFS.txt");
  myOut << "start" << endl;

	//visitado[s] = 1;

  //Atribui a raiz nivel 0 e o insere na pilha
	nivel[s] = 0;
	pilha.push(s);
  //myOut << "Vertice: " << s << ", Nivel: " << nivel[s] << ", Pai: " << pai[s] << endl;
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
        pilha.push(w[i]);
          //pai[w[i]-1] = v;
          //nivel[w[i]-1] = nivel[v]+1;
          //visitado[w[i]-1] = 1;
          int n = pilha.top();
          pai[n] = v;
          nivel[n] = nivel[v] + 1;
    }
  }
}
  // explorado.push_back(v);
  //}
  //for(int i=0;i<explorado.size();i++){
  //  myOut << "vertice: "<< explorado[i] << ": pai:"<< pai[explorado[i]] << " nivel:" << nivel[explorado[i]] << endl;
  //}

  //Retorno do vetor visitados
	return visitado;
}

//Retorna o vetor de explorados na BFS
vector<int> Matriz::BFS(int raiz) {

  //clock_t begin = clock();
  //Inicio da escrita no arquivo destino
  ofstream myOut;
  myOut.open (m_savePath + "/BFS.txt");
  myOut << "start" << endl;

  //Assim como na DFS, ocorre uma diferenciação em relação ao código da Lista
  //por nossa função de vizinhos da matriz ter vértice inicial 1 e na lista zero.
  //Assim a variável s, origem da BFS, recebe a raiz passada como parâmetro
	int s = raiz;

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
      if(visitado[w[i]] == 0) {
        visitado[w[i]] = 1;
        pai[w[i]] = v;
        nivel[w[i]] = nivel[v]+1;
        fila.push(w[i]);
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

Matriz::~Matriz(){
  for(int i=0;i<m_numVertices;i++){
         delete[] m_Matriz[i];
  }
  delete[] m_Matriz;
}
