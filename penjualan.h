#ifndef PENJUALAN_H
#define PENJUALAN_H

// Fungsi untuk mencatat transaksi penjualan
void catatTransaksi(char namaBarang[][50], int jumlahBeli[], float hargaBarang[], int stokBarang[], int jumlahBarang, float totalHarga, float diskon, float totalBayar);

// Fungsi untuk menampilkan laporan penjualan
void laporanPenjualan();

#endif // PENJUALAN_H
