#include "berkas.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Memecah satu baris berdasarkan tanda '|' ke dalam array kolom.
// Mengembalikan jumlah kolom yang ditemukan.
int pisah(string baris, string kolom[], int maks) {
    int n = 0;
    string sementara = "";
    for (int i = 0; i < (int)baris.size(); i++) {
        if (baris[i] == '|') {
            if (n < maks) kolom[n] = sementara;
            n++;
            sementara = "";
        } else if (baris[i] != '\r') {
            sementara += baris[i];
        }
    }
    if (n < maks) kolom[n] = sementara;
    n++;
    return n;
}

void bacaBuku(string namaBerkas, KumpulanBuku& koleksi) {
    koleksi.jumlah = 0;
    ifstream f(namaBerkas.c_str());
    if (!f) {
        cout << "File " << namaBerkas << " belum ada, mulai dengan data kosong.\n";
        return;
    }

    string baris;
    string k[7];
    while (getline(f, baris)) {
        if (baris == "") continue;
        if (pisah(baris, k, 7) != 7) continue;  // jumlah kolom salah
        if (k[0] == "kode") continue;   
        int th, hal, st;
        if (!kodeValid(k[0])) continue;
        if (!parseAngka(k[4], th)  || th  < TAHUN_MIN || th  > TAHUN_MAX) continue;
        if (!parseAngka(k[5], hal) || hal < HAL_MIN   || hal > HAL_MAX)   continue;
        if (!parseAngka(k[6], st)  || st  < STOK_MIN  || st  > STOK_MAX)  continue;

        Buku b;
        b.kode = k[0];
        b.judul = k[1];
        b.detail.penulis = k[2];
        b.detail.penerbit = k[3];
        b.tahun = th;
        b.halaman = hal;
        b.stok = st;        

        if (cariIndeks(koleksi, b.kode) != -1) continue;  // kode duplikat
        if (koleksi.jumlah >= KAPASITAS) break;           // array penuh

        koleksi.data[koleksi.jumlah] = b;
        koleksi.jumlah++;
    }
    cout << koleksi.jumlah << " buku dimuat dari " << namaBerkas << endl;
}

void simpanBuku(string namaBerkas, const KumpulanBuku& koleksi) {
    ofstream f(namaBerkas.c_str());
    if (!f) {
        cout << "Gagal menyimpan ke " << namaBerkas << endl;
        return;
    }
    f << "kode|judul|penulis|penerbit|tahun|halaman|stok\n";
    for (int i = 0; i < koleksi.jumlah; i++) {
        const Buku& b = koleksi.data[i];
        f << b.kode << "|" << b.judul << "|" << b.detail.penulis << "|"
          << b.detail.penerbit << "|" << b.tahun << "|"
          << b.halaman << "|" << b.stok << "\n";
    }
}
