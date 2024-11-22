# Nama file output yang dihasilkan
TARGET = main
# Compiler yang digunakan
CC = gcc

# Opsi kompilasi
CFLAGS = -Wall -g

# Daftar file sumber (.c)
SRCS = main.c barang.c kategori.c login.c member.c pembayaran.c penjualan.c

# Daftar file objek yang dihasilkan (.o)
OBJS = $(SRCS:.c=.o)

# Rule untuk mengkompilasi file objek dari file sumber
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule untuk menghasilkan file eksekusi
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule untuk membersihkan file objek dan file eksekusi
clean:
	rm -f $(OBJS) $(TARGET)

# Rule untuk menjalankan program
run: $(TARGET)
	./$(TARGET)
