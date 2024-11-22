#include "penjualan.h"
#include <stdio.h>
#include <time.h> // Header yang diperlukan untuk menangani waktu

// Fungsi untuk mencatat transaksi penjualan
void catatTransaksi(char namaBarang[][50], int jumlahBeli[],
                    float hargaBarang[], int stokBarang[], int jumlahBarang,
                    float totalHarga, float diskon, float totalBayar) {
  FILE *file = fopen("data/penjualan.txt", "a");
  if (file == NULL) {
    printf("Gagal membuka file untuk mencatat transaksi.\n");
    return;
  }

  // Mendapatkan waktu saat ini
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  // Menyimpan transaksi ke file
  fprintf(file, "Waktu: %04d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900,
          tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  // Mencatat detail barang
  for (int i = 0; i < jumlahBarang; i++) {
    fprintf(file,
            "Barang: %s, Stok: %d, Jumlah Beli: %d, Harga per Item: %.2f, "
            "Total Harga: %.2f\n",
            namaBarang[i], stokBarang[i], jumlahBeli[i], hargaBarang[i],
            hargaBarang[i] * jumlahBeli[i]);
  }

  // Mencatat diskon dan total pembayaran
  fprintf(file, "Diskon: %.2f\n", diskon);
  fprintf(file, "Grand Total Bayar: %.2f\n", totalBayar);
  fprintf(file, "=====================\n");

  fclose(file);
  printf("Transaksi telah tercatat.\n");
}

// Fungsi untuk menampilkan laporan penjualan
void laporanPenjualan() {
  FILE *file = fopen("data/penjualan.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file laporan penjualan.\n");
    return;
  }

  char line[256];
  printf("\n=== Laporan Penjualan ===\n");
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
  }

  fclose(file);
}
