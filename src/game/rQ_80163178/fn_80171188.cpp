#include "game/rQ_80163178/common.h"
extern "C" {
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5C4;
#else
extern u32 lbl_804CA5C4;
#endif
int fn_80163178(Unit*);
int fn_8012BB48(Unit*, u8*);
int fn_8012BA20(Unit*, u8*);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
u8* fn_801116B8(Inv*);
void fn_80170D64(Unit*);
void fn_80170E60(Unit*);
int fn_80109348(void*);
}
extern "C" void fn_80171188(Unit* u) {
    int k;
    int i;
    Inv* p;
    Inv* base;
    Inv* q;
    u->w3B4 &= 0xFAFFC02B;
    fn_80163178(u);
    base = u->inv;
    p = base;
    for (i = 0; i < 7; i++, p++) {
        if (!p || !p->item) break;
        if (fn_8012BB48(u, p->item)) {
            u8* it = p->item;
            if ((u8)(it ? it[0x14] : 0x13) == 0x81 || (u8)(it ? it[0x14] : 0x13) == 0x82) {
                u->w3B4 |= 4;
            }
        }
    }
    k = 0;
    q = base;
    while (k < 7) {
        if (!q || !q->item) break;
        if (fn_8012BB48(u, q->item) && (u8)(q->item ? q->item[0x14] : 0x13) == 0x86) {
            u->w3B4 |= 0x10;
        }
        k++;
        q++;
    }
    if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
        u->w3B4 |= 0x2000;
    }
    for (i = 0; i < 7; i++, base++) {
        if (!base || !base->item) break;
        if (fn_8012BA20(u, base->item) && (*(u32*)(fn_801116B8(base) + 4) & 2)) {
            u->w3B4 |= 0x40;
            break;
        }
    }
    fn_80170D64(u);
    fn_80170E60(u);
    if (fn_80109348((u8*)u + 0x110)) {
        u->w3B4 |= 0x1000000;
    }
}
