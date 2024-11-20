#ifndef USER_H
#define USER_H

#define MAX_NAMA 50
#define MAX_PASSWORD 20

typedef struct {
    char username[MAX_NAMA];
    char password[MAX_PASSWORD];
} User;

extern User user[MAX];
extern int total_user;

void load_user();
// Declare other user functions like login here

#endif
