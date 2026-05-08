#ifndef COMMON_H
#define COMMON_H

// Paket Veri Yapısı (Hash Tablosunda saklanacak)
typedef struct Packet {
    int packetId;          // Paket ID'si
    char source[50];       // Çıkış Şehri
    char destination[50];  // Hedef Şehir
    char status[30];       // Teslimat Durumu (Yolda, Teslim Edildi vb.)
} Packet;

#endif