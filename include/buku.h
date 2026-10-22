#ifndef BUKU_H
#define BUKU_H

#include <string>
using namespace std;

const int KAPASITAS = 100;
const int TAHUN_MIN = 1500, TAHUN_MAX = 2100;
const int HAL_MIN = 1, HAL_MAX = 10000;
const int STOK_MIN = 0, STOK_MAX = 1000;

struct DetailBuku {
    string penulis;
    string penerbit;
};

struct Buku {
    string kode;
    string judul;
    DetailBuku detail;
    unsigned short tahun;
    unsigned short halaman;
    unsigned short stok;
};

struct BukuAlternatif {
    unsigned short tahun;
    unsigned short halaman;
    unsigned short stok;
    DetailBuku detail;
    string kode;
    string judul;
};

struct KumpulanBuku {
    Buku data[KAPASITAS];
    int jumlah;
};

string kecil(string s);
int cariIndeks(const KumpulanBuku& koleksi, string kode);
bool parseAngka(const string& s, int& hasil);   
bool kodeValid(const string& k);                

void tambahBuku(KumpulanBuku& koleksi);
void tampilkanBuku(const KumpulanBuku& koleksi);
void cariBuku(const KumpulanBuku& koleksi);
void urutkanBuku(KumpulanBuku& koleksi);
void ubahBuku(KumpulanBuku& koleksi);
void hapusBuku(KumpulanBuku& koleksi);
void tampilkanStatistik(const KumpulanBuku& koleksi);
void tampilkanInfoMemori(const KumpulanBuku& koleksi);

#endif

