#ifndef BUKU_H
#define BUKU_H

#include <string>
using namespace std;

const int KAPASITAS = 100;

struct DetailBuku {
    string penulis;
    string penerbit;
    int tahun;
    int halaman;
};

struct Buku {
    string kode;
    string judul;
    DetailBuku detail;
    int stok;
};

struct KumpulanBuku {
    Buku data[KAPASITAS];
    int jumlah;
};

string kecil(string s);
int cariIndeks(const KumpulanBuku& koleksi, string kode);

void tambahBuku(KumpulanBuku& koleksi);
void tampilkanBuku(const KumpulanBuku& koleksi);
void cariBuku(const KumpulanBuku& koleksi);
void urutkanBuku(KumpulanBuku& koleksi);
void ubahBuku(KumpulanBuku& koleksi);
void hapusBuku(KumpulanBuku& koleksi);
void tampilkanStatistik(const KumpulanBuku& koleksi);

#endif
