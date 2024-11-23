#include "barang.h"
#include "kategori.h"
#include "penjualan.h"
#include <stdio.h>
#include <string.h>

// Define a structure for each item
typedef struct {
    char nama[50];
    char kategori[50];
    float harga;
    int stok;
} Barang;

Barang daftarBarang[100]; // Maksimal 100 items
int totalBarang = 0;  // Jumlah item

// Fungsi untuk memuat data barang dari file
void loadBarangFromFile() {
  FILE *file = fopen("barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file barang.txt\n");
    return;
  }

  // Read data from file line by line
  while (fscanf(file, "%s %s %f %d", daftarBarang[totalBarang].nama,
                daftarBarang[totalBarang].kategori,
                &daftarBarang[totalBarang].harga,
                &daftarBarang[totalBarang].stok) == 4) {
    totalBarang++;
    if (totalBarang >= 100)
      break; // Ensure we don't exceed the array size
  }

  fclose(file);
}

// Fungsi untuk mendapatkan total jumlah barang
int getTotalBarang() { return totalBarang; }

// Fungsi untuk mendapatkan nama barang berdasarkan index
const char *getNamaBarangByIndex(int index) {
  if (index >= 0 && index < totalBarang) {
    return daftarBarang[index].nama;
  }
  return NULL; // If index is invalid
}

// Fungsi untuk mendapatkan harga barang berdasarkan index
float getHargaBarangByIndex(int index) {
  if (index >= 0 && index < totalBarang) {
    return daftarBarang[index].harga;
  }
  return -1; // If index is invalid
}

// Fungsi untuk mendapatkan stok barang berdasarkan index
int getStokBarangByIndex(int index) {
  if (index >= 0 && index < totalBarang) {
    return daftarBarang[index].stok;
  }
  return -1; // If index is invalid
}

// Fungsi untuk mendapatkan kategori barang berdasarkan index
void getKategoriBarangByIndex(int index, char *kategori) {
  if (index >= 0 && index < totalBarang) {
    strcpy(kategori, daftarBarang[index].kategori);
  } else {
    kategori[0] = '\0'; 
  }
}

// Fungsi untuk mengurangi stok barang setelah pembelian
void updateStokBarang(const char *namaBarang, int stokBaru) {
  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  FILE *tempFile = fopen("data/temp_barang.txt", "w");
  if (tempFile == NULL) {
    printf("Gagal membuat file sementara.\n");
    fclose(file);
    return;
  }

  char itemName[50], kategori[50];
  int stok;
  float harga;

  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) != EOF) {
    if (strcmp(itemName, namaBarang) == 0) {
      stok = stokBaru; // Update stok
    }
    fprintf(tempFile, "%s %d %.2f %s\n", itemName, stok, harga, kategori);
  }

  fclose(file);
  fclose(tempFile);

  remove("data/barang.txt"); // Menghapus file asli
  rename("data/temp_barang.txt", "data/barang.txt"); // Menamai file sementara menjadi file barang
}

void menuBarang() {
  int pilihan;
  do {
    printf("\n=== Kelola Barang ===\n");
    printf("1. Tambah Barang\n");
    printf("2. Hapus Barang\n");
    printf("3. Tambah Stok Barang\n");
    printf("4. Kurangi Stok Barang\n");
    printf("5. Lihat Daftar Barang\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
    case 1:
      tambahBarang();
      break;
    case 2:
      hapusBarang();
      break;
    case 3:
      tambahStokBarang();
      break;
    case 4:
      kurangiStokBarang();
      break;
    case 5:
      lihatBarang();
      break;
    case 0:
      printf("Kembali ke menu utama.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (pilihan != 0);
}

void tambahBarang() {
  FILE *file = fopen("data/barang.txt", "a");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char nama[50], kategori[50];
  int stok;
  float harga;

  // Menampilkan kategori yang ada
  int kategoriCount = getKategoriCount();
  if (kategoriCount == 0) {
    printf("Tidak ada kategori yang tersedia. Tambahkan kategori terlebih "
           "dahulu.\n");
    fclose(file);
    return;
  }

  // Menampilkan daftar kategori
  char categories[kategoriCount][50];
  getKategoriList(categories);

  printf("Pilih kategori barang:\n");
  for (int i = 0; i < kategoriCount; i++) {
    printf("%d. %s\n", i + 1, categories[i]);
  }

  int kategoriPilihan;
  printf("Masukkan pilihan kategori (1 - %d): ", kategoriCount);
  scanf("%d", &kategoriPilihan);

  // Validasi pilihan kategori
  if (kategoriPilihan < 1 || kategoriPilihan > kategoriCount) {
    printf("Kategori tidak valid.\n");
    fclose(file);
    return;
  }

  // Menambahkan barang
  printf("Masukkan nama barang: ");
  scanf("%s", nama);
  printf("Masukkan stok barang: ");
  scanf("%d", &stok);
  printf("Masukkan harga barang: ");
  scanf("%f", &harga);

  // Menyimpan data barang dan kategori ke file
  fprintf(file, "%s %d %.2f %s\n", nama, stok, harga,
          categories[kategoriPilihan - 1]);
  fclose(file);
  printf("Barang berhasil ditambahkan.\n");
}

void hapusBarang() {
  char nama[50];
  printf("Masukkan nama barang yang akan dihapus: ");
  scanf("%s", nama);

  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  FILE *tempFile = fopen("data/temp_barang.txt", "w");
  if (tempFile == NULL) {
    printf("Gagal membuat file sementara.\n");
    fclose(file);
    return;
  }

  char itemName[50], kategori[50];
  int stok;
  float harga;

  int found = 0;

  // Membaca file barang dan menyalin ke file sementara, kecuali barang yang
  // ingin dihapus
  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) !=
         EOF) {
    if (strcmp(itemName, nama) != 0) {
      fprintf(tempFile, "%s %d %.2f %s\n", itemName, stok, harga, kategori);
    } else {
      found = 1;
    }
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove("data/barang.txt"); // Menghapus file asli
    rename("data/temp_barang.txt",
           "data/barang.txt"); // Menamai file sementara menjadi file barang
    printf("Barang '%s' berhasil dihapus.\n", nama);
  } else {
    printf("Barang dengan nama '%s' tidak ditemukan.\n", nama);
    remove("data/temp_barang.txt"); // Menghapus file sementara
  }
}

void tambahStokBarang() {
  char nama[50];
  printf("Masukkan nama barang yang stoknya akan ditambah: ");
  scanf("%s", nama);

  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  FILE *tempFile = fopen("data/temp_barang.txt", "w");
  if (tempFile == NULL) {
    printf("Gagal membuat file sementara.\n");
    fclose(file);
    return;
  }

  char itemName[50], kategori[50];
  int stok, stokTambah;
  float harga;

  int found = 0;

  // Membaca file barang dan menyalin ke file sementara sambil menambah stok
  // barang yang ditemukan
  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) !=
         EOF) {
    if (strcmp(itemName, nama) == 0) {
      printf("Masukkan jumlah stok yang ingin ditambahkan: ");
      scanf("%d", &stokTambah);
      stok += stokTambah; // Menambah stok
      found = 1;
    }
    fprintf(tempFile, "%s %d %.2f %s\n", itemName, stok, harga, kategori);
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove("data/barang.txt"); // Menghapus file asli
    rename("data/temp_barang.txt",
           "data/barang.txt"); // Menamai file sementara menjadi file barang
    printf("Stok barang '%s' berhasil ditambahkan.\n", nama);
  } else {
    printf("Barang dengan nama '%s' tidak ditemukan.\n", nama);
    remove("data/temp_barang.txt"); // Menghapus file sementara
  }
}

void kurangiStokBarang() {
  char nama[50];
  printf("Masukkan nama barang yang stoknya akan dikurangi: ");
  scanf("%s", nama);

  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  FILE *tempFile = fopen("data/temp_barang.txt", "w");
  if (tempFile == NULL) {
    printf("Gagal membuat file sementara.\n");
    fclose(file);
    return;
  }

  char itemName[50], kategori[50];
  int stok, stokKurang;
  float harga;

  int found = 0;

  // Membaca file barang dan menyalin ke file sementara sambil mengurangi stok
  // barang yang ditemukan
  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) !=
         EOF) {
    if (strcmp(itemName, nama) == 0) {
      printf("Masukkan jumlah stok yang ingin dikurangi: ");
      scanf("%d", &stokKurang);
      if (stokKurang > stok) {
        printf("Stok tidak cukup untuk dikurangi.\n");
        fclose(file);
        fclose(tempFile);
        return;
      }
      stok -= stokKurang; // Mengurangi stok
      found = 1;
    }
    fprintf(tempFile, "%s %d %.2f %s\n", itemName, stok, harga, kategori);
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove("data/barang.txt"); // Menghapus file asli
    rename("data/temp_barang.txt",
           "data/barang.txt"); // Menamai file sementara menjadi file barang
    printf("Stok barang '%s' berhasil dikurangi.\n", nama);
  } else {
    printf("Barang dengan nama '%s' tidak ditemukan.\n", nama);
    remove("data/temp_barang.txt"); // Menghapus file sementara
  }
}

void lihatBarang() {
  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char nama[50], kategori[50];
  int stok;
  float harga;

  printf("\nDaftar Barang:\n");
  printf("%-20s %-10s %-10s %-20s\n", "Nama", "Stok", "Harga", "Kategori");
  while (fscanf(file, "%s %d %f %s", nama, &stok, &harga, kategori) != EOF) {
    printf("%-20s %-10d %-10.2f %-20s\n", nama, stok, harga, kategori);
  }

  fclose(file);
}
float getHargaBarang(char *nama) {
  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return -1;
  }

  char itemName[50], kategori[50];
  int stok;
  float harga;

  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) !=
         EOF) {
    if (strcmp(itemName, nama) == 0) {
      fclose(file);
      return harga;
    }
  }

  fclose(file);
  return -1; // Jika barang tidak ditemukan
}

int getStokBarang(char *nama) {
  FILE *file = fopen("data/barang.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return -1;
  }

  char itemName[50], kategori[50];
  int stok;
  float harga;

  while (fscanf(file, "%s %d %f %s", itemName, &stok, &harga, kategori) !=
         EOF) {
    if (strcmp(itemName, nama) == 0) {
      fclose(file);
      return stok;
    }
  }

  fclose(file);
  return -1; // Jika barang tidak ditemukan
}
