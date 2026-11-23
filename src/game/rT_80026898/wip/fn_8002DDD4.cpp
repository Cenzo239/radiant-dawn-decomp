/* fn_8002DDD4 (r16): differs only in the first combatant block: original addresses it as lis r3 / addi r31 / sth lo(r3) and keeps the loop end in r0, ours uses sthu and shares r3. Blocks 2 and 3 match (const& params give the r29 pattern). */
/* Static constructor of the battle context lbl_803C8E80 (three combatants). */
#include "game/rT_80026898/types.h"

extern "C" {
extern void fn_80111B34(void*);
extern void fn_80111C24(void*, int);
extern void fn_8028BFD8(void*, void*, void*, u32, u32);
extern void fn_80129150(void*);
extern void fn_8002E3D4(void*);
extern void fn_8002E26C(void*, int);
extern void __register_global_object(void*, void*, void*);
extern u8 lbl_80379438[];
extern u8 lbl_803C8E70[];

struct SSlot {
    u8* item;
    u8 uses;
    u8 flags;
    u8 pad[2];
    void init() {
        item = 0;
        uses = 2;
        flags = 0;
        if (item) {
            flags |= item[0x20] == 0 ? 1 : 0;
        }
    }
};

struct CUnit {
    u16 h0;
    u8 pad2[0x108 - 2];
    u64 flags;
    u8 pad110[0x119 - 0x110];
    s8 stat[8];
    s8 pad121[8];
    u8 pad129[3];
    SSlot skills[18];
    u8 inv[7][0x28];
    u8 pad2d4[0x4a0 - 0x2d4];
};

static inline void unitCtor(CUnit* const& u) {
    u32 z = 0;
    *(u16*)u = z;
    u->flags = z;
    u->stat[7] = z;
    u->stat[6] = z;
    u->stat[5] = z;
    u->stat[4] = z;
    u->stat[3] = z;
    u->stat[2] = z;
    u->stat[1] = z;
    u->stat[0] = z;
    u->pad121[7] = z;
    u->pad121[6] = z;
    u->pad121[5] = z;
    u->pad121[4] = z;
    u->pad121[3] = z;
    u->pad121[2] = z;
    u->pad121[1] = z;
    u->pad121[0] = z;
    {
        SSlot* s = u->skills;
        do {
            s->init();
            s++;
        } while (s < (SSlot*)u->inv);
    }
    fn_8028BFD8(u->inv, (void*)fn_80111B34, (void*)fn_80111C24, 0x28, 7);
    *(u16*)((u8*)u + 0x382) = 0;
    *(u8**)((u8*)u + 0x2ec) = lbl_80379438;
    *(u8**)((u8*)u + 0x348) = lbl_80379438;
    *(u8**)((u8*)u + 0x358) = lbl_80379438;
    *(u8**)((u8*)u + 0x368) = lbl_80379438;
    *(u16*)((u8*)u + 0x384) = 0;
    *(u16*)((u8*)u + 0x386) = 0;
    *(u16*)((u8*)u + 0x388) = 0;
    *(u16*)((u8*)u + 0x38a) = 0;
    *(u16*)((u8*)u + 0x38c) = 0;
    *((u8*)u + 0x38e) = 0;
    *((u8*)u + 0x38f) = 0;
    fn_80129150((u8*)u + 0x3c4);
}

static inline void combCtor(CUnit* const& c) {
    unitCtor(c);
    fn_80111B34((u8*)c + 0x3f4);
    fn_80111B34((u8*)c + 0x41c);
    *(u16*)((u8*)c + 0x45e) = 0;
    *((u8*)c + 0x49a) = 0;
    *((u8*)c + 0x499) = 0;
    *((u8*)c + 0x498) = 0;
    *((u8*)c + 0x497) = 0;
    *((u8*)c + 0x496) = 0;
    *((u8*)c + 0x495) = 0;
    *((u8*)c + 0x494) = 0;
    *((u8*)c + 0x493) = 0;
    fn_8002E3D4(c);
}

struct BattleCtx {
    CUnit c[3];
    u8 padDE0[0x15ec - 0xde0];
    u32 f15ec;
};


void fn_8002DDD4(void) {
    BattleCtx* b = (BattleCtx*)lbl_803C8E80;
    CUnit* c0 = &b->c[0]; combCtor(c0);
    CUnit* c1 = &b->c[1]; combCtor(c1);
    CUnit* c2 = &b->c[2]; combCtor(c2);
    b->f15ec = 0;
    __register_global_object(lbl_803C8E80, (void*)fn_8002E26C, lbl_803C8E70);
}
}
