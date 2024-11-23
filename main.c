#include "barang.h"     // Header untuk fitur kelola barang
#include "kategori.h"   // Header untuk fitur kelola kategori barang
#include "login.h"      // Header untuk fitur login pengguna
#include "member.h"     // Header untuk fitur kelola member
#include "pembayaran.h" // Header untuk fitur proses pembayaran
#include "penjualan.h"  // Header untuk fitur penjualan
#include <stdio.h>

int isLoggedIn =
    0; // Status login, 0 berarti belum login, 1 berarti sudah login

// Fungsi untuk menampilkan menu utama dan memanggil fitur yang dipilih
void menuUtama() {
  int pilihan; // Variabel untuk menyimpan pilihan pengguna
  // Jika belum login, tampilkan menu login terlebih dahulu
  if (!isLoggedIn) {
    printf("Anda belum login. Silakan login terlebih dahulu.\n");
    login(); // Panggil fungsi login
  }

  do {
    // Menampilkan daftar menu utama hanya jika sudah login
    printf("\n=== Sistem Kasir ===\n");
    printf("1. Kelola Barang\n");          // Menu untuk fitur kelola barang
    printf("2. Kelola Kategori Barang\n"); // Menu untuk fitur kelola kategori
                                           // barang
    printf("3. Proses Pembayaran\n");      // Menu untuk fitur proses pembayaran
    printf("4. Kelola Member\n");          // Menu untuk fitur kelola member
    printf("5. Laporan Penjualan\n");      // Menu untuk fitur laporan penjualan
    printf("6. Logout\n");         // Menu untuk fitur login pengguna
    printf("0. Keluar\n");                 // Pilihan untuk keluar dari program
    printf("Pilih menu: ");
    scanf("%d", &pilihan); // Membaca input pilihan dari pengguna

    // Memproses pilihan pengguna dengan switch-case
    switch (pilihan) {
    case 1:
      menuBarang(); // Memanggil fungsi menuBarang() untuk kelola barang
      break;
    case 2:
      menuKategori(); // Memanggil fungsi menuKategori() untuk kelola kategori
      break;
    case 3:
      prosesPembayaran(); // Memanggil fungsi prosesPembayaran() untuk
                          // pembayaran
      break;
    case 4:
      menuMember(); // Memanggil fungsi menuMember() untuk kelola member
      break;
    case 5:
      laporanPenjualan(); // Memanggil fungsi laporanPenjualan() untuk
                          // menampilkan laporan
      break;
    case 6:
      login(); // Memanggil fungsi login() untuk fitur login pengguna
      break;
    case 0:
      printf("Keluar dari sistem.\n"); // Pesan ketika keluar dari program
      break;
    default:
      printf("Pilihan tidak valid.\n"); // Pesan untuk pilihan yang salah
    }
  } while (pilihan != 0); // Perulangan berlanjut hingga pengguna memilih keluar
}
// Fungsi utama untuk menjalankan program
int main() {
  menuUtama(); // Memanggil fungsi menu utama
  return 0;    // Mengembalikan 0 untuk menandakan program berjalan sukses
}
