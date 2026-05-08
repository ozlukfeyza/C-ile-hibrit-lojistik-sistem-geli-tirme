#ifndef GRAPH_H
#define GRAPH_H

// Graf Komşuluk Listesi Düğümü
typedef struct AdjListNode {
    int destVertex;
    struct AdjListNode* next;
} AdjListNode;

// Graf Vertex (Şehir) Yapısı
typedef struct AdjList {
    char cityName[50];
    AdjListNode* head;
} AdjList;

// Graf Yapısı
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// Fonksiyon Prototipleri
Graph* createGraph(int numVertices);
void addCity(Graph* graph, int vertexIndex, const char* name);
void addRoute(Graph* graph, int src, int dest); // Yönlendirmesiz rota (Çift taraflı)
void BFS(Graph* graph, int startVertex);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);

#endif