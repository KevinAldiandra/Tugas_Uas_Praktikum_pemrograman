#include <stdio.h>
#include <string.h>
#include "user.h"

extern User user[MAX];
extern int total_user;

void load_user() {
    FILE *file = fopen("user.txt", "r");
    if (file) {
        while (fscanf(file, "%[^,],%[^\n]\n", user[total_user].username, user[total_user].password) != EOF) {
            total_user++;
        }
        fclose(file);
    }
}

// Other user functions like login
