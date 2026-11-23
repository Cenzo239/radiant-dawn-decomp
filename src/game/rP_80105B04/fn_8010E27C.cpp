#include "game/rP_80105B04/rp.h"
struct LUnit {
    u8 pad[0xE4];
    LUnit* prev;
    LUnit* next;
    u8 padEC[0x380 - 0xEC];
    s8 sideSlot;
};
struct SideList { LUnit* head; LUnit* tail; };
extern "C" {
void fn_8010E27C(SideList* l, LUnit* u) {
    if (u->next) {
        u->next->prev = u->prev;
    } else {
        l->tail = u->prev;
        if (l->tail) l->tail->next = 0;
    }
    if (u->prev) {
        u->prev->next = u->next;
    } else {
        l->head = u->next;
        if (l->head) l->head->prev = 0;
    }
    u->prev = 0;
    u->next = 0;
    u->sideSlot = -1;
}
int fn_8010E2F4(SideList* l) {
    int n = 0;
    LUnit* u = l->head;
    while (u) {
        u = u->next;
        n++;
    }
    return n;
}
}
