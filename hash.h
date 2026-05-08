#ifndef HASH_H
#define HASH_H

#include "common.h"

// Zincirleme (Chaining) için Bağlı Liste Düğümü
typedef struct HashNode {
    Packet packet;
    struct HashNode* next;
} HashNode;

// Hash Tablosu Yapısı
typedef struct HashTable {
    int size;
    HashNode** buckets; // Dizi pointer'ı (Node pointer dizisi)
} HashTable;

// Fonksiyon Prototipleri
HashTable* createHashTable(int size);
int hashFunctionA(int key, int size); // Tip A: Modulo Hash
void insertPacket(HashTable* table, Packet pkt);
Packet* searchPacket(HashTable* table, int packetId);
void printHashTable(HashTable* table);
void freeHashTable(HashTable* table);

#endif