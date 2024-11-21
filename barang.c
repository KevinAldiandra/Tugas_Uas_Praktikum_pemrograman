#include <stdio.h>
#include <string.h>
#include "barang.h"

extern Barang barang[MAX];
extern int total_barang;

void load_barang() {
    FILE *file = fopen("barang.txt", "r");
    if (file) {
        while (fscanf(file, "%[^,],%f,%d,%[^\n]\n", barang[total_barang].nama, &barang[total_barang].harga, &barang[total_barang].stok, barang[total_barang].kategori) != EOF) {
            total_barang++;
        }
        fclose(file);
    }
}

void save_barang() {
    FILE *file = fopen("barang.txt", "w");
    for (int i = 0; i < total_barang; i++) {
        fprintf(file, "%s,%.2f,%d,%s\n", barang[i].nama, barang[i].harga, barang[i].stok, barang[i].kategori);
    }
    fclose(file);
}
