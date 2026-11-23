/* Small leftovers: widget counter, palette refresh, null u64, position setter. */
#include "game/rR_80175E5C/types.h"
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))
extern "C" {
extern u8 lbl_80387A40[];
void* fn_80081050(void*, void*);
void fn_80010F94(void*, void*);
#if TARGET_PC
FE10_PROTO void fn_801C6D98(f32, f32, i32arg, int);
#else
void fn_801C6D98(f32, f32, void*, int);
#endif

void* fn_80177418(u8* o, void* parent) {
    void* p = fn_80081050(lbl_80387A40, parent);
    F(p, u8*, 0x30) = o;
    F(o, int, 0x30)++;
    return p;
}

unsigned long long fn_8017DA30() {
    return 0;
}

void fn_8017E30C(u8* p) {
    void* a = F(p, void*, 0x64);
    void* b;
    if (a != NULL && (b = F(p, void*, 0x68)) != NULL) {
        fn_80010F94(a, b);
        if (p[0x54] != 0) {
            u8* q = F(p, u8*, 0x64);
            q[2] = p[0x59];
            q[3] = p[0x5A];
            q[4] = p[0x5B];
            q[5] = p[0x5C];
            u8* r = F(p, u8*, 0x6C);
            if (r != NULL) {
                r[4] = p[0x5D];
                r[5] = p[0x5E];
                r[6] = p[0x5F];
                r[7] = p[0x60];
            }
        }
    }
}

void fn_801DBD98(int x, int y, void* p) {
    fn_801C6D98(x, y, p, 0);
}
}
