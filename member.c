#include <stdio.h>
#include <string.h>
#include "member.h"

extern Member member[MAX];
extern int total_member;

void load_member() {
    FILE *file = fopen("member.txt", "r");
    if (file) {
        while (fscanf(file, "%[^,],%d\n", member[total_member].nama, &member[total_member].poin) != EOF) {
            total_member++;
        }
        fclose(file);
    }
}

void save_member() {
    FILE *file = fopen("member.txt", "w");
    for (int i = 0; i < total_member; i++) {
        fprintf(file, "%s,%d\n", member[i].nama, member[i].poin);
    }
    fclose(file);
}

// Other member functions like tambah_member, tambah_poin_member, etc.

