#include "Lista.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <vector>
//#include <stack>
//include <queue>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
//#include <tuple>
#include<bits/stdc++.h>
#define INF 10000001

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
        int v0, vf;
        //Peso padrão igual a 1 para grafos sem peso
        float peso = 1;
        tmp >> v0 >> vf >> peso;
        //Verificação da condição de todos os pesos serem positivos
        if (peso < 0){
          grafoNegativo = 1;
        }
        //Verificação da condição do grafo possuir pesos
        if (peso != 1){
          grafoComPeso = 1;
        }
        this->addAresta(v0, vf, peso);
        this->addAresta(vf, v0, peso);
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
    cout << "Grafo negativo? " << grafoNegativo << endl;
    cout << "Grafo com peso? " << grafoComPeso << endl;
}

//Adiciona aresta na lista de adjacencia
void Lista::addAresta(int v0, int vf, float peso){
  //Nao precisa adicionar no m_pLista[vf] , porque chama o addAresta 2 vezes na leitura
  ListInfo* vizinho = new ListInfo;
  vizinho->vertice = vf;
  vizinho->peso = peso;
  //se vertice v0 tem alguma aresta, adiciona o novo vizinho no inicio
  if (m_pLista[v0] != NULL) m_pLista[v0]->pPrev = vizinho;
  vizinho->pNext = m_pLista[v0];
  vizinho->pPrev = NULL;
  this->m_pLista[v0] = vizinho;

}

//Retorna um vetor de tuplas de vizinhos de um vértice v, contendo o vértice
//adjacente e o peso da aresta, sendo vértice inicial igual a 0
vector<tuple<int, float> > Lista::vizinhos(int v){
  //Vetor que guarda todos os vizinhos
  vector<tuple<int, float> > vizinhos;
  //Cria estrutura para percorrer a lista e a percorre adicionando os vizinhos
  //no vetor
  ListInfo* pCrawl = new ListInfo;
  pCrawl = m_pLista[v+1];
  while(pCrawl != NULL){
    vizinhos.push_back(make_tuple(pCrawl->vertice, pCrawl->peso));
    pCrawl = pCrawl->pNext;
  }

  //for(int i=0;i<vizinhos.size();i++){
  //  cout << get<0>(vizinhos[i]) << " ";
  //  cout << get<1>(vizinhos[i]) << endl;
  //}

  //Retorna o vetor de tuplas vizinhos
  return vizinhos;
}

//Retorna o struct BFSs, que contém o vetor de explorados, de pais e de niveis
BFSs* Lista::BFS(int raiz) {

  //clock_t begin = clock();
  //Inicio da escrita no arquivo destino
  ofstream myOut;
  myOut.open (m_savePath + "/BFS.txt");
  myOut << "start" << endl;

  ofstream myOut2;
  myOut2.open (m_savePath + "/BFS - Distancia e Caminho.txt");

  //Variável auxiliar a partir do struct BFSs que contém pai, nivel e vetor de
  //explorados que será retornada pela função
  BFSs* bfs = new BFSs;

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

  bfs->pai = pai;
  bfs->nivel = nivel;
  bfs->explorado = explorado;

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
    vector<tuple<int, float> > w = vizinhos(v);
    //cout << w.size() << endl;
    for(int i = 0;i< w.size();i++){
      if(visitado[get<0>(w[i])-1] == 0) {
        visitado[get<0>(w[i])-1] = 1;
        pai[get<0>(w[i])-1] = v;
        nivel[get<0>(w[i])-1] = nivel[v]+1;
        fila.push(get<0>(w[i])-1);
        }
      }
    //cout << v << endl;
    //cout << v << endl;

    //Adiciona o vértice ao vetor explorado depois do loop
    explorado.push_back(v);
  }

  //Atribuição das variáveis atualizadas na nossa estrutura
  bfs->pai = pai;
  bfs->nivel = nivel;
  bfs->explorado = explorado;

  //Escreve no arquivo de saída o vértice, seu pai e seu nivel
  for(int i=0;i<explorado.size();i++){
    myOut << "vertice: "<< explorado[i] << ": pai:"<< pai[explorado[i]] << " nivel:" << nivel[explorado[i]] << endl;
  }

  myOut2 << "Origem: " << raiz << endl;
  myOut2 << "Vertice - Distancia a Origem - Caminho" << endl;
  for (int i = 0; i < m_numVertices; i++){
    myOut2 << i + 1 << " \t \t \t " << nivel[i];
    vector<int> caminho = retornaCaminho(pai, s, i);
    myOut2 << " \t \t \t \t ";
    for (int j = 0; j < caminho.size(); j++){
        myOut2  << caminho[j] + 1 << " " ;
    }
    myOut2 << endl;
  }

  //Retorno da estrutura principal
  return bfs;
}

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
    vector<tuple<int, float> > w = vizinhos(i-1);
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
      vector<tuple<int, float> > w = vizinhos(v);
      for(int i = 0; i < w.size();i++){
        pilha.push(get<0>(w[i])-1);
          int n = pilha.top();
          pai[n] = v;
          nivel[n] = nivel[v] + 1;
        }
      }
    }

  //Retorno do vetor visitados
	return visitado;
}


//Funcao para achar as componentes conexas de um grafo.
void Lista::CC(){
  //Vetor de ids, que se referem ao numero da componente conexa que o vértice
  //pertence
  vector<int> id(m_numVertices+1, -1);

  //Variável contadora de componentes
  int count = 0;

  //Criação do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/CC.txt");

  //Vetor de vetores que guarda todas as componentes
  vector< vector<int> > componentes;

  //Loop principal
  for (int i = 1; i <= m_numVertices; i++){
    //Se o id for -1, significa que o vértice ainda nao foi encontrado
    //Nesse caso, roda uma BFS e adiciona o vetor de explorados retornado por essa
    //BFS no vetor de vetores componentes. Depois atualiza o id dos vértices
    //marcados e incrementa o contador de componentes
    if (id[i-1] == -1){
      vector<int> temp = BFS(i)->explorado;
      sort(temp.begin(), temp.end());
      componentes.push_back(temp);
      for (int j = 0; j<temp.size();j++){
        id[temp[j]] = count;
      }
    count++;
    }
  }

  //Ordena vetor de componentes do maior tamanho para o menor
  sort(componentes.begin(), componentes.end(), [](const vector<int> & a, const vector<int> & b){ return a.size() > b.size(); });

  //Escrita do número de componentes
  myOut << "Numero de componentes: " << count << endl;

  //Escrita de cada componente e seus respectivos vértices
  for (int i = 0; i < componentes.size();i++){
    myOut << "Componente " << i+1 << ": ";
    for (int j = 0; j < componentes[i].size();j++){
       myOut << componentes[i][j]+1 << ", ";
    }
    myOut << endl;
  }
}

//Função que, dado um vértice raiz como parâmetro, calcula a distância e o caminho
//mínimo desse vértice para todos os outros vértices do grafo
vector<float> Lista::distDijkstra(int raiz){
  //Nossa origem será raiz menos um porque nossa função de vizinhos começa
  //com a origem sendo igual a zero
	int s = raiz-1;
	//Inicialização da fila de prioridade e do vetor de distancias e de pais
	priority_queue< tuple<float, int>, vector<tuple<float, int> >, greater<tuple<float, int> > > heap;
  vector<float> dist(m_numVertices, INT_MAX);
  vector<int> pai(m_numVertices, -1);

  //Inicio do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/Dijkstra.txt");

  //Adiciona a origem no heap e coloca sua distancia como 0
  heap.push(make_tuple(0, s));
  dist[s] = 0;

  //Vetor booleano que verifica se o vértice já foi retirado do heap
  //evitando atualizações desnecessárias
  vector<bool> retiradoHeap(m_numVertices, false);

  while (!heap.empty()){

    //Pega o vértice no topo do heap e o retira do heap
    int v = get<1>(heap.top());
    heap.pop();
    retiradoHeap[v] = true;

    //Acha os vizinhos do vértice a ser analisado
    vector<tuple<int, float> > w = vizinhos(v);

    //Percorre o vetor de vizinhos
    for (int i = 0; i < w.size(); i++){
      //Pega o vértice do vizinho e o peso da aresta
      int u = get<0>(w[i]) - 1;
      float peso = get<1>(w[i]);

      //Verifica como no pseudocódigo de Dijkstra se a distancia do vértice pai
      //mais o peso da aresta é menor que a distância atual do vértice
      if (retiradoHeap[u] == false && dist[u] > dist[v] + peso){
        //Seta o pai do vértice e atualiza sua distância
        pai[u] = v;
        dist[u] = dist[v] + peso;

        //Insere no heap o vértice e sua distância
        heap.push(make_tuple(dist[u], u));
      }
    }
  }

  //Escrita no arquivo de saída
  myOut << "Origem: " << raiz << endl;
  myOut << "Vertice - Distancia a Origem - Caminho" << endl;
  for (int i = 0; i < m_numVertices; i++){
    myOut << i + 1 << " \t \t \t " << dist[i];
    vector<int> caminho = retornaCaminho(pai, s, i);
    myOut << " \t \t \t \t ";
    for (int j = 0; j < caminho.size(); j++){
        myOut  << caminho[j] + 1 << " " ;
    }
    myOut << endl;
  }

  return dist;
}

//Essa função verifica a distância e o caminho mínimo entre um par de vértices
//e retorna a distância desse caminho
float Lista::caminhoMinimo(int x, int y){
  //Nossa origem será raiz menos um porque nossa função de vizinhos começa
  //com a origem sendo igual a zero
  int s = x-1;
  //Inicialização da fila de prioridade e do vetor de distancias e de pais
  priority_queue< tuple<float, int>, vector<tuple<float, int> >, greater<tuple<float, int> > > heap;
  vector<float> dist(m_numVertices, INT_MAX);
  vector<int> pai(m_numVertices, -1);

  //Inicio do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/Dijkstra.txt");

  //Adiciona a origem no heap e coloca sua distancia como 0
  heap.push(make_tuple(0, s));
  dist[s] = 0;

  //Vetor booleano que verifica se o vértice já foi retirado do heap
  //evitando atualizações desnecessárias
  vector<bool> retiradoHeap(m_numVertices, false);

  while (!heap.empty()){

    //Pega o vértice no topo do heap e o retira do heap
    int v = get<1>(heap.top());
    heap.pop();
    retiradoHeap[v] = true;

    //Acha os vizinhos do vértice a ser analisado
    vector<tuple<int, float> > w = vizinhos(v);

    //Percorre o vetor de vizinhos
    for (int i = 0; i < w.size(); i++){
      //Pega o vértice do vizinho e o peso da aresta
      int u = get<0>(w[i]) - 1;
      float peso = get<1>(w[i]);

      //Verifica como no pseudocódigo de Dijkstra se a distancia do vértice pai
      //mais o peso da aresta é menor que a distância atual do vértice
      if (retiradoHeap[u] == false && dist[u] > dist[v] + peso){
        //Seta o pai do vértice e atualiza sua distância
        pai[u] = v;
        dist[u] = dist[v] + peso;

        //Insere no heap o vértice e sua distância
        heap.push(make_tuple(dist[u], u));
      }
    }
    //Quebra o loop caso o vértice ao qual queremos achar o caminho já tenha
    //sido retirado do heap
    if (retiradoHeap[y-1]){
      break;
    }
  }

  //Escrita no arquivo de saída
  myOut << "Distância entre " << x << " e " << y << ": " << dist[y-1] << endl;
  myOut << "Caminho entre " << x << " e " << y << endl;
  vector<int> caminho = retornaCaminho(pai, s, y-1);
  for (int j = 0; j < caminho.size(); j++){
      myOut  << caminho[j] + 1 << " " ;
    }

  return dist[y-1];
}

//Função auxiliar da função caminhoMinimo principal. Serve para retornar
//o caminho mínimo entre dois vértices, retornando um vetor contendo
//os vértices pertencentes ao caminho
vector<int> Lista::retornaCaminho(vector<int> pai, int raiz, int v){
  //Variavel auxiliar
  int i = v;

  //Inicializa vetor de caminho e insere o vértice ao qual queremos achar o caminhoMinimo
  vector<int> caminho;
  caminho.push_back(v);

  //Verificação se os vértices são diferentes
  if (raiz==v){
    return caminho;
  }else{
  //Loop para inserir o pai do vértice atual no vetor caminho
  while( i!=-1 && pai[i] != raiz) {
		caminho.insert(caminho.begin(), pai[i]);
		i = pai[i];
	}

  //Insere a raiz no vetor caminho e o retorna
	caminho.insert(caminho.begin(), raiz);
  return caminho;
  }
}

//Função que escreve no arquivo de saída o peso total de uma MST do grafo,
//junto com o numero de vértices e as arestas pertencentes a essa árvore
void Lista::PrimMST(){
  //Inicializa o vértice 0 como nossa raiz
  int s = 0;
  //Inicialização da fila de prioridade e do vetor de pais, custo e o booleano
  //tree serve para verificar se o vertice já está na árvore
  priority_queue< tuple<float, int>, vector<tuple<float, int> >, greater<tuple<float, int> > > heap;
  vector<float> custo(m_numVertices, INT_MAX);
  vector<int> pai(m_numVertices, -1);
  vector<bool> tree(m_numVertices, false);
  float pesoTotal = 0;
  //Inicio do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/Prim.txt");

  //Adiciona a origem no heap e coloca seu custo como 0
  heap.push(make_tuple(0, s));
  custo[s] = 0;

  while (!heap.empty()){

    //Pega o vértice no topo do heap e o retira do heap
    int v = get<1>(heap.top());
    heap.pop();

    //Insere o vértice na árvore
    tree[v] = true;

    //Acha os vizinhos do vértice a ser analisado
    vector<tuple<int, float> > w = vizinhos(v);

    //Percorre o vetor de vizinhos
    for (int i = 0; i < w.size(); i++){
      //Pega o vértice do vizinho e o peso da aresta
      int u = get<0>(w[i]) - 1;
      float peso = get<1>(w[i]);

      //Verifica se o vértice já está na árvore e compara o custo atual do vértice
      //com o peso da aresta analisada
      if (tree[u] == false && custo[u] > peso){
        //Seta o pai do vértice e atualiza seu custo
        custo[u] = peso;
        pai[u] = v;
        //Insere no heap o vértice e seu custo
        heap.push(make_tuple(custo[u], u));
      }
    }
  }
  //Atualização do peso total
  for (int i = 0; i < m_numVertices; i++){
    pesoTotal += custo[i];
  }



  //Escrita no arquivo de saída
  myOut << "Peso total: " << pesoTotal << endl;
  myOut << m_numVertices << endl;
  for (int i = 1; i < m_numVertices; ++i){
    myOut << pai[i] + 1 << " " << i + 1 << endl;
  }
}

//Função que retorna a excentricidade de um vértice v
float Lista::excentricidade(int v){
  clock_t begin = clock();
  //Nossa origem será raiz menos um porque nossa função de vizinhos começa
  //com a origem sendo igual a zero
	int s = v-1;
	//Inicialização da fila de prioridade e do vetor de distancias e de pais
	priority_queue< tuple<float, int>, vector<tuple<float, int> >, greater<tuple<float, int> > > heap;
  vector<float> dist(m_numVertices, INT_MAX);
  vector<int> pai(m_numVertices, -1);

  //Inicio do arquivo de saída
  ofstream myOut;
  myOut.open (m_savePath + "/Excentricidade.txt");

  //Adiciona a origem no heap e coloca sua distancia como 0
  heap.push(make_tuple(0, s));
  dist[s] = 0;

  //Vetor booleano que verifica se o vértice já foi retirado do heap
  //evitando atualizações desnecessárias
  vector<bool> retiradoHeap(m_numVertices, false);

  while (!heap.empty()){

    //Pega o vértice no topo do heap e o retira do heap
    int v = get<1>(heap.top());
    heap.pop();
    retiradoHeap[v] = true;

    //Acha os vizinhos do vértice a ser analisado
    vector<tuple<int, float> > w = vizinhos(v);

    //Percorre o vetor de vizinhos
    for (int i = 0; i < w.size(); i++){
      //Pega o vértice do vizinho e o peso da aresta
      int u = get<0>(w[i]) - 1;
      float peso = get<1>(w[i]);

      //Verifica como no pseudocódigo de Dijkstra se a distancia do vértice pai
      //mais o peso da aresta é menor que a distância atual do vértice
      if (retiradoHeap[u] == false && dist[u] > dist[v] + peso){
        //Seta o pai do vértice e atualiza sua distância
        pai[u] = v;
        dist[u] = dist[v] + peso;

        //Insere no heap o vértice e sua distância
        heap.push(make_tuple(dist[u], u));
      }
    }
  }
  //Obtenção do valor máximo no vetor de distâncias
  auto maximo = max_element(dist.begin(), dist.end());
  cout << "Excentricidade do vertice " << v << ": " << *maximo << endl;
  myOut << "Excentricidade do vertice " << v << ": " << *maximo << endl;
  clock_t	end = clock();
	double elapsed_time = double(end-begin)/CLOCKS_PER_SEC;
	cout << "-------------------" << endl << "TOTAL elapsed time: " << elapsed_time << "s" << endl;
  return *maximo;
}


//Função que retorna a distância média de um grafo
float Lista::distMedia(){

  //Inicialização das variáveis de soma e contadora de distâncias
  float soma = 0;
  int count = 0;

  for (int i=1; i <= m_numVertices; i++){
    //A funcao distDijkstra retorna o vetor de distâncias a partir de um vértice
    vector<float> aux = distDijkstra(i);
    //Adiciona ao somatório a soma do vetor aux (todas as distâncias)
    soma += accumulate(aux.begin(), aux.end(), 0);
    //Aumenta o contador
    count += aux.size();
  }
  //Retira do contador o número de vértices pois a distância i-i (igual a zero)
  //é incluida na função de Dijkstra
  count -= m_numVertices;
  cout << soma << endl;
  cout << count << endl;
  cout << soma*1.0/count << endl;
  return soma*1.0/count;

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
