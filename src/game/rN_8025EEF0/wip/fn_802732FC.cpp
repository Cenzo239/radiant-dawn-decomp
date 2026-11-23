/* 4 words of 0x1494 bytes: case 5 wants m42 in r5 and the row term in r6, mine swaps them. */
/* Conversation room: cursor position */
#include "game/rN_8025EEF0/room.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_80272FAC(int x, int y, int z) {
    Room* r;
    r = roomData();
    r->m38 = roomData()->m32;
    r = roomData();
    r->m3A = roomData()->m34;
    roomData()->m3C = x;
    roomData()->m3E = y;
    roomData()->m36 = z;
    if (z == 0) {
        roomData()->m32 = x;
        roomData()->m34 = y;
    }
}

void fn_802732FC(int i, int j, int z) {
    switch (roomData()->m30) {
    case 0:
        fn_80272FAC(roomData()->m40 + 0x10, roomData()->m42 + i * 0x1C + 0xC, z);
        break;
    case 1:
    case 2:
        fn_80272FAC(roomData()->m40 + 0x82, roomData()->m42 + (i - j) * 0x1C + 0xC, z);
        break;
    case 3:
        fn_80272FAC(roomData()->m40 + 8, roomData()->m42 + (i - j + 1) * 0x1C, z);
        break;
    case 4:
        fn_80272FAC(roomData()->m40 + 8, roomData()->m42 + (i - j + 1) * 0x1C, z);
        break;
    case 5:
        fn_80272FAC(roomData()->m40 + 0x172 - i * 0x1A, roomData()->m42 + (roomData()->m2C - j + 1) * 0x1C, z);
        break;
    }
}

}
