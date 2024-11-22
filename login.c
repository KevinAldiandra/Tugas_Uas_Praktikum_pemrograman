#include "login.h" // Header file untuk login
#include <stdio.h>
#include <string.h>

extern int isLoggedIn; // Status login, diakses dari file lain

// Fungsi untuk melakukan login
void login() {
  char username[50], password[50];
  int loginStatus = 0; // Status login: 0 berarti gagal, 1 berarti berhasil

  // Selama login gagal, ulangi meminta input
  while (!loginStatus) {
    printf("\n=== Login ===\n");
    printf("Masukkan username: ");
    scanf("%s", username); // Membaca input username
    printf("Masukkan password: ");
    scanf("%s", password); // Membaca input password

    // Cek login berdasarkan username dan password (misalnya hardcoded)
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
      isLoggedIn = 1; // Set status login menjadi benar jika login sukses
      printf("Login berhasil!\n");
      loginStatus = 1; // Set status login menjadi sukses, keluar dari loop
    } else {
      printf("Login gagal! Username atau password salah.\n");
      printf("Silakan coba lagi.\n");
    }
  }
}
