#include "pembayaran.h"
#include "barang.h"    // Untuk mengakses stok barang
#include "penjualan.h" // Untuk mencatat laporan penjualan
#include <stdio.h>

// Fungsi untuk memproses pembayaran
void prosesPembayaran() {
  int jumlahBarang;
  float totalHarga = 0, hargaBarang;
  float diskon = 0, totalBayar;
  char isMember;
  char namaBarang[50][50]; // Array to store names of items
  int jumlahBeli[50];       // Array to store quantity of each item
  float hargaBarangArray[50]; // Array to store prices of each item
  int stokBarang[50];       // Array to store stock of each item

  printf("\n=== Proses Pembayaran ===\n");

  // Menampilkan daftar barang, stok, kategori, dan harga
  printf("\nDaftar Barang Tersedia:\n");
  int totalBarang = getTotalBarang();  // Asumsi fungsi untuk mengambil total barang
  for (int i = 0; i < totalBarang; i++) {
    char kategori[50];
    int stok = getStokBarangByIndex(i);  // Ambil stok barang berdasarkan index
    float harga = getHargaBarangByIndex(i);  // Ambil harga barang berdasarkan index
    getKategoriBarangByIndex(i, kategori);  // Ambil kategori barang berdasarkan index

    printf("%d. Nama Barang: %s\n", i + 1, getNamaBarangByIndex(i));  // Menampilkan nama barang
    printf("   Kategori: %s\n", kategori);
    printf("   Stok: %d\n", stok);
    printf("   Harga: %.2f\n\n", harga);
  }

  printf("Masukkan jumlah barang yang dibeli: ");
  scanf("%d", &jumlahBarang);

  for (int i = 0; i < jumlahBarang; i++) {
    printf("Masukkan nama barang ke-%d: ", i + 1);
    scanf("%s", namaBarang[i]);
    printf("Masukkan jumlah barang yang dibeli: ");
    scanf("%d", &jumlahBeli[i]);

    hargaBarang = getHargaBarang(namaBarang[i]); // Mengambil harga barang
    if (hargaBarang == -1) {
      printf("Barang dengan nama '%s' tidak ditemukan.\n", namaBarang[i]);
      continue;
    }

    int stok = getStokBarang(namaBarang[i]); // Mengecek stok barang
    if (stok < jumlahBeli[i]) {
      printf("Stok barang '%s' tidak cukup.\n", namaBarang[i]);
      continue;
    }

    // Menyimpan harga dan stok barang ke array
    hargaBarangArray[i] = hargaBarang;
    stokBarang[i] = stok;

    // Mengurangi stok barang yang dibeli
    updateStokBarang(namaBarang[i], stok - jumlahBeli[i]);

    totalHarga += hargaBarang * jumlahBeli[i];
  }

  printf("Apakah pelanggan adalah member? (y/n): ");
  scanf(" %c", &isMember);

  if (isMember == 'y' || isMember == 'Y') {
    diskon = totalHarga * 0.1; // Member mendapat diskon 10%
  }

  totalBayar = totalHarga - diskon;

  printf("Total Harga: %.2f\n", totalHarga);
  printf("Diskon: %.2f\n", diskon);
  printf("Total yang harus dibayar: %.2f\n", totalBayar);

  // Mencatat transaksi ke laporan penjualan
  catatTransaksi(namaBarang, jumlahBeli, hargaBarangArray, stokBarang, jumlahBarang, totalHarga, diskon, totalBayar);

  printf("Pembayaran selesai.\n");
}
