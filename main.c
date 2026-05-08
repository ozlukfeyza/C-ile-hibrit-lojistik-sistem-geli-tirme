#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "graph.h"

int main() {
    // 5 Şehirli Graf Yapısı Tanımlayalım (ID'ler: 0, 1, 2, 3, 4)
    Graph* logisticGraph = createGraph(5);
    addCity(logisticGraph, 0, "Istanbul");
    addCity(logisticGraph, 1, "Kocaeli");
    addCity(logisticGraph, 2, "Ankara");
    addCity(logisticGraph, 3, "Bursa");
    addCity(logisticGraph, 4, "Izmir");

    // Rotaları Ekleyelim
    addRoute(logisticGraph, 0, 1); // Istanbul - Kocaeli
    addRoute(logisticGraph, 0, 3); // Istanbul - Bursa
    addRoute(logisticGraph, 1, 2); // Kocaeli - Ankara
    addRoute(logisticGraph, 3, 4); // Bursa - Izmir
    addRoute(logisticGraph, 2, 4); // Ankara - Izmir

    // Hash Tablosu Tanımlayalım (Boyut: 5 seçelim ki çakışma/zincirleme kolay gözlensin)
    HashTable* packetTable = createHashTable(5);

    // En az 5 adet veri girişi (Bellek raporu için stabil veri kümesi)
    Packet p1 = {101, "Istanbul", "Ankara", "Yolda"};
    Packet p2 = {102, "Kocaeli", "Izmir", "Dagitimda"};
    Packet p3 = {106, "Bursa", "Istanbul", "Teslim Edildi"}; // 106 % 5 = 1 (101 ile çakışacak)
    Packet p4 = {107, "Izmir", "Ankara", "Yolda"};          // 107 % 5 = 2 (102 ile çakışacak)
    Packet p5 = {110, "Istanbul", "Bursa", "Hazirlaniyor"}; // 110 % 5 = 0

    insertPacket(packetTable, p1);
    insertPacket(packetTable, p2);
    insertPacket(packetTable, p3); // Zincirlenecek
    insertPacket(packetTable, p4); // Zincirlenecek
    insertPacket(packetTable, p5);

    int choice;
    int searchId;

    while (1) {
        printf("\n=================================");
        printf("\n   LOJISTIK YONETIM SISTEMI     ");
        printf("\n=================================");
        printf("\n1. Sehirleri ve Rotalari Listele (Graf)");
        printf("\n2. BFS ile Rota Tarama Yap");
        printf("\n3. Tum Paketleri Listele (Hash Tablosu)");
        printf("\n4. Paket Sorgula (O(1) Hizi)");
        printf("\n5. Yeni Paket Ekle");
        printf("\n6. Cikis");
        printf("\nSeciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printGraph(logisticGraph);
                break;
            case 2:
                printf("Baslangic Sehir ID'sini girin (0:Istanbul, 1:Kocaeli, 2:Ankara, 3:Bursa, 4:Izmir): ");
                int start;
                scanf("%d", &start);
                if(start >= 0 && start < 5) {
                    BFS(logisticGraph, start);
                } else {
                    printf("Gecersiz sehir ID'si!\n");
                }
                break;
            case 3:
                printHashTable(packetTable);
                break;
            case 4:
                printf("Sorgulanacak Paket ID girin: ");
                scanf("%d", &searchId);
                Packet* found = searchPacket(packetTable, searchId);
                if (found) {
                    printf("\n>>> PAKET BULUNDU! <<<\n");
                    printf("ID: %d | Nereden: %s | Nereye: %s | Durum: %s\n", 
                           found->packetId, found->source, found->destination, found->status);
                } else {
                    printf("\n>>> Paket Bulunamadi! <<<\n");
                }
                break;
            case 5: {
                Packet newPkt;
                printf("Yeni Paket ID: ");
                scanf("%d", &newPkt.packetId);
                printf("Nereden (Sehir): ");
                scanf("%s", newPkt.source);
                printf("Nereye (Sehir): ");
                scanf("%s", newPkt.destination);
                strcpy(newPkt.status, "Kabul Edildi");
                insertPacket(packetTable, newPkt);
                printf("Paket basariyla sisteme ve Hash Tablosuna eklendi!\n");
                break;
            }
            case 6:
                printf("Sistem kapatiliyor. Bellek temizleniyor...\n");
                freeGraph(logisticGraph);
                freeHashTable(packetTable);
                return 0;
            default:
                printf("Gecersiz secim!\n");
        }
    }
    return 0;
}