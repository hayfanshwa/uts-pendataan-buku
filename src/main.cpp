#include "buku.h"
#include "berkas.h"
#include "menu.h"
#include <iostream>
using namespace std;

int main() {
    KumpulanBuku koleksi;
    string namaBerkas = "buku.txt";

    bacaBuku(namaBerkas, koleksi);
    jalankanMenu(koleksi, namaBerkas);
    return 0;
}
