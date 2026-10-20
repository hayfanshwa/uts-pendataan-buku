#ifndef BERKAS_H
#define BERKAS_H

#include "buku.h"
#include <string>
using namespace std;

void bacaBuku(string namaBerkas, KumpulanBuku& koleksi);
void simpanBuku(string namaBerkas, const KumpulanBuku& koleksi);

#endif
