#include "kategori.h"
#include <stdio.h>

void menuKategori() {
  int pilihan;
  do {
    printf("\n=== Kelola Kategori ===\n");
    printf("1. Tambah Kategori\n");
    printf("2. Lihat Kategori\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
    case 1:
      tambahKategori();
      break;
    case 2:
      lihatKategori();
      break;
    case 0:
      printf("Kembali ke menu utama.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (pilihan != 0);
}

void tambahKategori() {
  FILE *file = fopen("data/kategori.txt", "a");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char kategori[50];
  printf("Masukkan nama kategori: ");
  scanf("%s", kategori);

  fprintf(file, "%s\n", kategori);
  fclose(file);
  printf("Kategori berhasil ditambahkan.\n");
}

void lihatKategori() {
  FILE *file = fopen("data/kategori.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char kategori[50];
  printf("\nDaftar Kategori:\n");
  while (fscanf(file, "%s", kategori) != EOF) {
    printf("%s\n", kategori);
  }

  fclose(file);
}

// Fungsi untuk mendapatkan jumlah kategori yang ada
int getKategoriCount() {
  FILE *file = fopen("data/kategori.txt", "r");
  if (file == NULL) {
    return 0;
  }

  int count = 0;
  char kategori[50];
  while (fscanf(file, "%s", kategori) != EOF) {
    count++;
  }

  fclose(file);
  return count;
}

void getKategoriList(char categories[][50]) {
  FILE *file = fopen("data/kategori.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file kategori.\n");
    return;
  }

  int i = 0;
  while (fscanf(file, "%s", categories[i]) != EOF) {
    i++;
  }

  fclose(file);
}
