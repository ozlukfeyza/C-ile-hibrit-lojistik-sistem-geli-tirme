#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (HashNode**)malloc(size * sizeof(HashNode*));
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// Tip A Hash Fonksiyonu: Modulo Aritmetiği
int hashFunctionA(int key, int size) {
    return key % size;
}

// Zincirleme (Chaining) ile Ekleme
void insertPacket(HashTable* table, Packet pkt) {
    int index = hashFunctionA(pkt.packetId, table->size);
    
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->packet = pkt;
    newNode->next = table->buckets[index]; // Başa ekleme yapıyoruz (O(1))
    table->buckets[index] = newNode;
}

// Paket Sorgulama (Hızlı Erişim)
Packet* searchPacket(HashTable* table, int packetId) {
    int index = hashFunctionA(packetId, table->size);
    HashNode* current = table->buckets[index];
    
    while (current != NULL) {
        if (current->packet.packetId == packetId) {
            return &(current->packet);
        }
        current = current->next;
    }
    return NULL; // Bulunamadı
}

// Hash Tablosunu Ekrana Yazdırma (Hata ayıklama ve bellek takibi için)
void printHashTable(HashTable* table) {
    printf("\n--- HASH TABLOSU DURUMU (Zincirleme) ---\n");
    for (int i = 0; i < table->size; i++) {
        printf("Bucket [%d] (%p): ", i, (void*)&table->buckets[i]);
        HashNode* temp = table->buckets[i];
        while (temp != NULL) {
            printf(" -> [ID: %d | Adres: %p | Next: %p]", 
                   temp->packet.packetId, (void*)temp, (void*)temp->next);
            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashNode* current = table->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}