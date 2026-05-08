# Lojistik Yönetim Sistemi (Graf & Hash Table Hibrit Yapısı)

Bu proje, bir lojistik firmasının şehirler arası bağlantılarını ve paket sorgulama işlemlerini yöneten hibrit bir veri yapısı uygulamasıdır.

## Kullanılan Teknolojiler & Algoritmalar
* **Graf Yapısı:** Şehirler komşuluk listesi (Adjacency List) ile modellenmiştir.
* **Graf Gezinmesi:** Genişlik Öncelikli Arama (BFS - Breadth-First Search) algoritması kullanılmıştır.
* **Hash Tablosu:** Paket sorgulamaları için Tip A (Modulo) hash fonksiyonu tercih edilmiştir.
* **Çakışma Çözümü:** Zincirleme (Chaining) bağlı liste yöntemi uygulanmıştır.

## Proje Yapısı
* `main.c`: Kullanıcı arayüzü ve test senaryoları.
* `hash.c` / `hash.h`: Hash tablosu ve bağlı liste operasyonları.
* `graph.c` / `graph.h`: Graf yapısı ve BFS arama algoritması.
* `common.h`: Ortak veri yapıları (Paket struct'ı).


