#include "menu.h"
#include "berkas.h"
#include <iostream>
using namespace std;

void jalankanMenu(KumpulanBuku& koleksi, string namaBerkas) {
    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n=== PENDATAAN BUKU PERPUSTAKAAN ===\n"
             << "1. Tambah buku\n"
             << "2. Tampilkan semua buku\n"
             << "3. Cari buku\n"
             << "4. Urutkan buku\n"
             << "5. Ubah buku\n"
             << "6. Hapus buku\n"
             << "7. Statistik koleksi\n"
             << "8. Info memori\n"
             << "0. Simpan dan keluar\n"
             << "Pilihan: ";
        cin >> pilihan;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan angka.\n";
            pilihan = -1;
            continue;
        }
        cin.ignore(1000, '\n');

        if (pilihan == 1) {
            tambahBuku(koleksi);
            simpanBuku(namaBerkas, koleksi);
        } else if (pilihan == 2) {
            tampilkanBuku(koleksi);
        } else if (pilihan == 3) {
            cariBuku(koleksi);
        } else if (pilihan == 4) {
            urutkanBuku(koleksi);
            simpanBuku(namaBerkas, koleksi);
        } else if (pilihan == 5) {
            ubahBuku(koleksi);
            simpanBuku(namaBerkas, koleksi);
        } else if (pilihan == 6) {
            hapusBuku(koleksi);
            simpanBuku(namaBerkas, koleksi);
        } else if (pilihan == 7) {
            tampilkanStatistik(koleksi);
        } else if (pilihan == 8) {
            tampilkanInfoMemori(koleksi);
        } else if (pilihan == 0) {
            simpanBuku(namaBerkas, koleksi);
            cout << "Data tersimpan. Sampai jumpa.\n";
        } else {
            cout << "Pilihan tidak tersedia.\n";
        }
    }
}

