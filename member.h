#ifndef MEMBER_H
#define MEMBER_H

#define MAX_NAMA 50

typedef struct {
    char nama[MAX_NAMA];
    int poin;
} Member;

extern Member member[MAX];
extern int total_member;

void load_member();
void save_member();

#endif
