#include <stdio.h>
#include <stdlib.h>
#include "barang.h"
#include "member.h"
#include "user.h"
#include "kasir.h"

int main() {
    load_barang();
    load_member();
    load_user();
    if (!login()) {
        return 0;
    }
    menu();
    return 0;
}

