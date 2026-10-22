#include "buku.h"
#include <iostream>
#include <iomanip>
using namespace std;

string kecil(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
    }
    return s;
}

string potong(string s, int lebar) {
    if ((int)s.size() > lebar) return s.substr(0, lebar - 2) + "..";
    return s;
}

int cariIndeks(const KumpulanBuku& koleksi, string kode) {
    for (int i = 0; i < koleksi.jumlah; i++) {
        if (kecil(koleksi.data[i].kode) == kecil(kode)) return i;
    }
    return -1;
}
bool parseAngka(const string& s, int& hasil) {
    if (s.empty() || s.size() > 9) return false;
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] < '0' || s[i] > '9') return false;
    hasil = stoi(s);
    return true;
}

bool kodeValid(const string& k) {
    if (k.size() != 5) return false;
    if (kecil(k.substr(0, 2)) != "bk") return false;
    for (int i = 2; i < 5; i++)
        if (k[i] < '0' || k[i] > '9') return false;
    return true;
}

string bacaTeks(string label) {
    string s;
    while (true) {
        cout << label;
        getline(cin, s);
        if (!s.empty() && s.find('|') == string::npos) return s;
        cout << "Tidak boleh kosong dan tidak boleh mengandung '|'.\n";
    }
}

int bacaAngka(string label, int mn, int mx) {
    string s; int n;
    while (true) {
        cout << label << " (" << mn << "-" << mx << "): ";
        getline(cin, s);
        if (parseAngka(s, n) && n >= mn && n <= mx) return n;
        cout << "Input tidak valid, ulangi.\n";
    }
}

Buku inputBuku() {
    Buku b;
    while (true) {
        b.kode = bacaTeks("Kode (BK###): ");
        if (kodeValid(b.kode)) break;
        cout << "Format kode harus BK diikuti 3 angka.\n";
    }
    b.judul           = bacaTeks("Judul: ");
    b.detail.penulis  = bacaTeks("Penulis: ");
    b.detail.penerbit = bacaTeks("Penerbit: ");
    b.tahun   = bacaAngka("Tahun terbit", TAHUN_MIN, TAHUN_MAX);
    b.halaman = bacaAngka("Jumlah halaman", HAL_MIN, HAL_MAX);
    b.stok    = bacaAngka("Stok", STOK_MIN, STOK_MAX);
    return b;
}

void cetakHeader() {
    cout << left << setw(8) << "KODE" << setw(26) << "JUDUL"
         << setw(20) << "PENULIS" << setw(24) << "PENERBIT"
         << setw(7) << "TAHUN" << setw(9) << "HALAMAN" << "STOK" << endl;
    cout << string(98, '-') << endl;
}

void cetak(const Buku& b) {
    cout << left << setw(8) << b.kode
         << setw(26) << potong(b.judul, 25)
         << setw(20) << potong(b.detail.penulis, 19)
         << setw(24) << potong(b.detail.penerbit, 23)
         << setw(7) << b.tahun
         << setw(9) << b.halaman
         << b.stok << endl;
}

void tambahBuku(KumpulanBuku& koleksi) {
    if (koleksi.jumlah >= KAPASITAS) {
        cout << "Kapasitas koleksi penuh.\n";
        return;
    }
    Buku b = inputBuku();
    if (cariIndeks(koleksi, b.kode) != -1) {
        cout << "Kode sudah dipakai.\n";
        return;
    }
    koleksi.data[koleksi.jumlah] = b;
    koleksi.jumlah++;
    cout << "Buku ditambahkan.\n";
}

void tampilkanBuku(const KumpulanBuku& koleksi) {
    if (koleksi.jumlah == 0) {
        cout << "Belum ada data.\n";
        return;
    }
    cetakHeader();
    for (int i = 0; i < koleksi.jumlah; i++) {
        cetak(koleksi.data[i]);
    }
}

void cariBuku(const KumpulanBuku& koleksi) {
    string kunci;
    cout << "Kata kunci (kode/judul/penulis): ";
    getline(cin, kunci);
    kunci = kecil(kunci);
    bool ada = false;
    for (int i = 0; i < koleksi.jumlah; i++) {
        string gabung = kecil(koleksi.data[i].kode + " " + koleksi.data[i].judul +
                              " " + koleksi.data[i].detail.penulis);
        if (gabung.find(kunci) != string::npos) {
            if (!ada) cetakHeader();
            cetak(koleksi.data[i]);
            ada = true;
        }
    }
    if (!ada) cout << "Tidak ditemukan.\n";
}

void urutkanBuku(KumpulanBuku& koleksi) {
    for (int i = 0; i < koleksi.jumlah - 1; i++) {
        for (int j = 0; j < koleksi.jumlah - i - 1; j++) {
            if (kecil(koleksi.data[j].kode) > kecil(koleksi.data[j + 1].kode)) {
                Buku temp = koleksi.data[j];
                koleksi.data[j] = koleksi.data[j + 1];
                koleksi.data[j + 1] = temp;
            }
        }
    }
    cout << "Diurutkan berdasarkan kode.\n";
}

void ubahBuku(KumpulanBuku& koleksi) {
    string kode;
    cout << "Kode buku yang diubah: ";
    getline(cin, kode);
    int i = cariIndeks(koleksi, kode);
    if (i == -1) {
        cout << "Tidak ditemukan.\n";
        return;
    }
    Buku b = inputBuku();
    int lain = cariIndeks(koleksi, b.kode);
    if (lain != -1 && lain != i) {
        cout << "Kode sudah dipakai buku lain.\n";
        return;
    }
    koleksi.data[i] = b;
    cout << "Data diubah.\n";
}

void hapusBuku(KumpulanBuku& koleksi) {
    string kode;
    cout << "Kode buku yang dihapus: ";
    getline(cin, kode);
    int i = cariIndeks(koleksi, kode);
    if (i == -1) {
        cout << "Tidak ditemukan.\n";
        return;
    }
    for (int j = i; j < koleksi.jumlah - 1; j++) {
        koleksi.data[j] = koleksi.data[j + 1];
    }
    koleksi.jumlah--;
    cout << "Buku dihapus.\n";
}

void tampilkanStatistik(const KumpulanBuku& koleksi) {
    if (koleksi.jumlah == 0) {
        cout << "Belum ada data.\n";
        return;
    }
    int total = 0;
    int mn = koleksi.data[0].stok;
    int mx = koleksi.data[0].stok;
    for (int i = 0; i < koleksi.jumlah; i++) {
        total += koleksi.data[i].stok;
        if (koleksi.data[i].stok < mn) mn = koleksi.data[i].stok;
        if (koleksi.data[i].stok > mx) mx = koleksi.data[i].stok;
    }
    cout << "Jumlah judul : " << koleksi.jumlah << endl;
    cout << "Total stok   : " << total << endl;
    cout << "Rata-rata    : " << fixed << setprecision(2)
         << (double)total / koleksi.jumlah << endl;
    cout << "Stok min/max : " << mn << " / " << mx << endl;
}

void tampilkanInfoMemori(const KumpulanBuku& koleksi) {
    cout << "(DetailBuku)   : " << sizeof(DetailBuku) << " byte\n";
    cout << "(Buku)         : " << sizeof(Buku) << " byte\n";
    cout << "(KumpulanBuku) : " << sizeof(KumpulanBuku) << " byte\n";
    cout << "Array data (kapasitas " << KAPASITAS << ") : "
         << sizeof(koleksi.data) << " byte\n";
    cout << "Terpakai (" << koleksi.jumlah << " buku)   : "
         << koleksi.jumlah * sizeof(Buku) << " byte\n";
    cout << "Ukuran Buku awal: " << sizeof(Buku) << " byte\n";
    cout << "Ukuran Buku alternatif: "
     << sizeof(BukuAlternatif) << " byte\n";
}
