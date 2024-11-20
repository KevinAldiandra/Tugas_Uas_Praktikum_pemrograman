#ifndef BARANG_H
#define BARANG_H

#define MAX 100
#define MAX_NAMA 50
#define MAX_PASSWORD 20

typedef struct {
    char nama[MAX_NAMA];
    float harga;
    int stok;
    char kategori[MAX_NAMA];
} Barang;

extern Barang barang[MAX];
extern int total_barang;

void load_barang();
void save_barang();
// Declare other barang functions here like tambah_barang, hapus_barang, etc.

#endif

