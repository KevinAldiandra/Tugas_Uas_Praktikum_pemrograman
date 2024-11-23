#include "laporan.h"
#include <stdio.h>

void lihatLaporan() {
  FILE *file = fopen("data/laporan.txt", "r");
  if (file == NULL) {
    printf("Gagal membuka file.\n");
    return;
  }

  char deskripsi[100];
  float total;

  printf("\n=== Laporan Penjualan ===\n");
  printf("Deskripsi\t\tTotal\n");
  printf("---------------------------------\n");

  while (fscanf(file, "%s %f", deskripsi, &total) != EOF) {
    printf("%-15s %.2f\n", deskripsi, total);
  }

  fclose(file);
}
