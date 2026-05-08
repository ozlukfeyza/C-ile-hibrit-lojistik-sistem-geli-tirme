#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    
    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
        strcpy(graph->array[i].cityName, "");
    }
    return graph;
}

void addCity(Graph* graph, int vertexIndex, const char* name) {
    if (vertexIndex >= 0 && vertexIndex < graph->numVertices) {
        strcpy(graph->array[vertexIndex].cityName, name);
    }
}

// İki şehir arasına rota ekleme (Komşuluk Listesine ekleme)
void addRoute(Graph* graph, int src, int dest) {
    // src -> dest bağlantısı
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->destVertex = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // dest -> src bağlantısı (Çift yönlü lojistik ağı için)
    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->destVertex = src;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// BFS (Breadth-First Search) Gezinmesi
void BFS(Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    // Basit bir Queue (Kuyruk) Yapısı
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    printf("\n--- BFS Rota Tarama Sirasi (%s merkezli) ---\n", graph->array[startVertex].cityName);

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("[Şehir ID: %d] %s -> ", currentVertex, graph->array[currentVertex].cityName);

        AdjListNode* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->destVertex;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("SON\n");

    free(visited);
    free(queue);
}

void printGraph(Graph* graph) {
    printf("\n--- SEHIR BAGLANTILARI (GRAF) ---\n");
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* temp = graph->array[v].head;
        printf("[%d] %s (Adres: %p):", v, graph->array[v].cityName, (void*)&graph->array[v]);
        while (temp) {
            printf(" -> %s (ID: %d | Node Adresi: %p)", 
                   graph->array[temp->destVertex].cityName, temp->destVertex, (void*)temp);
            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
}

void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        AdjListNode* temp = graph->array[v].head;
        while (temp != NULL) {
            AdjListNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->array);
    free(graph);
}