#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Estrutura que representa um nó do MinHeap
struct MinHeapNode
{
    int  v;
    float dist;
};

//Estrutura que representa o MinHeap
struct MinHeap
{
    int size;      //Número de nós atualmente no heap
    int capacity;  //Capacidade máxima do heap
    vector<int> pos;     //Necessário para a função decreaseKey()
    struct MinHeapNode **array;
};

//Função para criar um nó do minHeap
struct MinHeapNode* newMinHeapNode(int v, float dist)
{
    struct MinHeapNode* minHeapNode = new MinHeapNode;
           //(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

//Função para criar um MinHeap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = new MinHeap;
         //(struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos.reserve(capacity);
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

//Função para trocar dois nós do heap, necessária para fazer o heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

//Função heapify a partir de um índice idx
//Atualiza as posições quando trocamos dois nós, necessárias para decreaseKey
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        //Guarda os nós a serem trocados
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        //Troca posições
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        //Troca os nós
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

//Função para verificar se o heap está vazio
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode* returnMin(struct MinHeap* minHeap){
  return minHeap->array[0];
}
//Função para extrair a raiz do heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    //Guarda o nó raiz
    struct MinHeapNode* root = minHeap->array[0];

    //Troca a raiz pelo último nó
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    //Atualiza posição do último nó
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    //Reduz o tamanho do heap e faz o heapify a partir da raiz
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

//Função que altera o valor da chave de um determinado vértice no heap.
//Essa função usa o array pos para verificar o índice do vértice no heap.
void decreaseKey(struct MinHeap* minHeap, int v, float dist)
{
    //Guarda o índice do vértice no heap
    int i = minHeap->pos[v];

    //Atualiza  a distância do nó
    minHeap->array[i]->dist = dist;

    //Percorre o loop enquanto a árvore não está na posição correta
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        //Troca o nó com o pai
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        //Muda para o índice do pai
        i = (i - 1) / 2;
    }
}

//Função que checa se o vértice está no heap ou não
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
