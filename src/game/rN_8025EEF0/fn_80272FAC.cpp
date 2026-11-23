/* Conversation room: cursor position */
#include "game/rN_8025EEF0/room.h"

#pragma use_lmw_stmw on

extern "C" {

struct RoomEntry { const char* name; u8 pad4[8]; const char* tag; u8 pad10[0x20]; };
struct RoomList { u8 pad0[0xC]; int n; RoomEntry* tbl; };
struct RoomArg { const char* name; u8 pad4[4]; int m8; const char* tag; };
void* fn_8010B100(const char* s);
void fn_8012CBF0(void* u);
void fn_80044758(void* u);
void fn_80061098(void);
void fn_80068C08(void);
void fn_800A0998(int i, void* p);

void fn_80272ED0(RoomArg* a) {
    int off;
    int n;
    RoomList* l;
    int i;
    int c;
    void* u;
    u = fn_8010B100(a->name);
    fn_8012CBF0(u);
    fn_80044758(u);
    fn_80061098();
    if (a->m8 == 0) {
        fn_80068C08();
    }
    l = (RoomList*)lbl_804CC06C;
    c = 0;
    n = l->n;
    for (i = 0, off = 0; i < n; off += 0x30, i++) {
        RoomEntry* e = (RoomEntry*)((u8*)l->tbl + off);
        if (fn_80291188(a->name, e->name) == 0) {
            if (fn_80291188(a->tag, e->tag) == 0) {
                break;
            }
            c++;
        }
    }
    fn_800A0998(c, lbl_804CC068);
}

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

}
