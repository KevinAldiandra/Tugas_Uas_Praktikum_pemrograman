#include "barang.h"
#include "kategori.h"
#include "login.h"
#include "member.h"
#include "pembayaran.h"
#include "penjualan.h"
#include <stdio.h>

int isLoggedIn = 0;

void menuUtama() {
  int pilihan;
  if (!isLoggedIn) {
    printf("Anda belum login. Silakan login terlebih dahulu.\n");
    login();
  }

  do {
    printf("\n=== Sistem Kasir ===\n");
    printf("1. Kelola Barang\n");
    printf("2. Kelola Kategori Barang\n");
    printf("3. Proses Pembayaran\n");
    printf("4. Kelola Member\n");
    printf("5. Laporan Penjualan\n");
    printf("6. Logout\n");
    printf("0. Keluar\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
    case 1:
      menuBarang();
      break;
    case 2:
      menuKategori();
      break;
    case 3:
      prosesPembayaran();
      break;
    case 4:
      menuMember();
      break;
    case 5:
      laporanPenjualan();
      break;
    case 6:
      login();
      break;
    case 0:
      printf("Keluar dari sistem.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (pilihan != 0);
}

int main() {
  menuUtama();
  return 0;
}
