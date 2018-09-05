#include "Matriz.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <new>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

Matriz::Matriz(string path){
  //cout << "antes" << endl;


  ifstream myFile;
  myFile.open(path);
  if(!myFile){
    cout << "Location not Found";
  }
  myFile >> m_numVertices;

  ofstream myOut;
  myOut.open ("output/info.txt");
  myOut << "Mnumero vertices:" << m_numVertices << endl;


  m_Matriz = new bool*[m_numVertices+1];
  for (int i=0;i<m_numVertices+1;i++){
    m_Matriz[i] = new bool[m_numVertices+1];
  }

  for (int i = 0; i <= m_numVertices; i++){
    for (int j = 0; j <= m_numVertices; j++){
      //  if ((i%10 and j%10) == 0){cout<<"test"<<i<<j<<endl;};
      m_Matriz[i][j] = false;
    }
  }


  m_numArestas = 0;
  string s;
  // while(getline(myFile, s)){
  while(getline(myFile, s)){
    if(s.empty() == false){
      istringstream tmp(s);                         //Leitura de Arquivo
      int v0, vf;
      tmp >> v0 >> vf;
      //cout << v0 << " " << vf << endl;
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
  myOut << "Mnumero arestas:" << m_numArestas << endl;
  myOut.close();

}
void Matriz::addAresta(int v0, int vf){
      m_Matriz[v0][vf] = true;
}

//Retorna os vizinhos do vertice v, sendo vertice inicial igual a 1
vector<int> Matriz::vizinhos(int v){
  vector<int> vizinho;
  for (int i = 0; i <= m_numVertices; i++){
    if (m_Matriz[v][i] == true){
      vizinho.push_back(i);
    }
  }
  //for(int i=0;i<vizinho.size();i++){
  //  cout << vizinho[i] << endl;
  //}
  //cout << vizinho.size();
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

Matriz::~Matriz(){
  for(int i=0;i<m_numVertices;i++){
         delete[] m_Matriz[i];
  }
  delete[] m_Matriz;
}
