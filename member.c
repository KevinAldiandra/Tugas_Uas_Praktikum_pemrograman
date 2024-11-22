#include "member.h"
#include <stdio.h>
#include <string.h>

// Fungsi untuk menampilkan menu kelola member
void menuMember() {
  int pilihan; // Variabel untuk menyimpan pilihan pengguna
  do {
    // Menampilkan daftar menu kelola member
    printf("\n=== Kelola Member ===\n");
    printf("1. Tambah Member\n");
    printf("2. Tambah Poin Member\n");
    printf("3. Lihat Daftar Member\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan); // Membaca pilihan pengguna

    // Memproses pilihan menggunakan switch-case
    switch (pilihan) {
    case 1:
      tambahMember(); // Memanggil fungsi untuk menambah member
      break;
    case 2:
      tambahPoinMember(); // Memanggil fungsi untuk menambah poin member
      break;
    case 3:
      lihatMember(); // Memanggil fungsi untuk melihat daftar member
      break;
    case 0:
      printf("Kembali ke menu utama.\n"); // Pesan saat kembali ke menu utama
      break;
    default:
      printf("Pilihan tidak valid.\n"); // Pesan jika pilihan salah
    }
  } while (pilihan != 0); // Perulangan berlanjut hingga pengguna memilih keluar
}

// Fungsi untuk menambah member baru
void tambahMember() {
  FILE *file =
      fopen("data/member.txt", "a"); // Membuka file untuk menambah data
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char nama[50];
  int poin = 0;

  printf("Masukkan nama member: ");
  scanf("%s", nama); // Membaca nama member dari pengguna

  // Menulis data member baru ke file
  fprintf(file, "%s %d\n", nama, poin);
  fclose(file); // Menutup file
  printf("Member berhasil ditambahkan.\n");
}

// Fungsi untuk menambahkan poin ke member
void tambahPoinMember() {
  FILE *file = fopen("data/member.txt", "r");
  FILE *tempFile =
      fopen("data/temp.txt", "w"); // File sementara untuk menyimpan perubahan
  if (file == NULL || tempFile == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char nama[50], target[50];
  int poin, tambahanPoin;
  int found = 0; // Menandai apakah member ditemukan

  printf("Masukkan nama member: ");
  scanf("%s", target); // Membaca nama member
  printf("Masukkan jumlah poin yang ingin ditambahkan: ");
  scanf("%d", &tambahanPoin); // Membaca poin yang ingin ditambahkan

  // Membaca file member dan memperbarui poin jika nama sesuai
  while (fscanf(file, "%s %d", nama, &poin) != EOF) {
    if (strcmp(nama, target) == 0) {
      poin += tambahanPoin; // Menambahkan poin ke member yang ditemukan
      found = 1;            // Menandai bahwa member ditemukan
    }
    fprintf(tempFile, "%s %d\n", nama, poin);
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    // Mengganti file lama dengan file baru
    remove("data/member.txt");
    rename("data/temp.txt", "data/member.txt");
    printf("Poin berhasil ditambahkan.\n");
  } else {
    remove("data/temp.txt");
    printf("Member tidak ditemukan.\n");
  }
}

// Fungsi untuk melihat daftar member
void lihatMember() {
  FILE *file = fopen("data/member.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char nama[50];
  int poin;

  printf("\nDaftar Member:\n");
  printf("Nama\tPoin\n");
  // Membaca data member dari file dan mencetaknya
  while (fscanf(file, "%s %d", nama, &poin) != EOF) {
    printf("%s\t%d\n", nama, poin);
  }

  fclose(file); // Menutup file
}
