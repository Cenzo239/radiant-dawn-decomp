/* r19: self-contained (helpers of fn_80263418.cpp + wip fragment); `sched` level. */
/* Dictionary menu: relation chart draw and teardown */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

#pragma use_lmw_stmw on

extern "C" {

void fn_8007E5C0(f32 x, f32 y, f32 z, f32 a, f32 b, f32 sx, f32 sy, f32 c);
void fn_80266024(void);
void fn_802652DC(void* e, int a);
void fn_80265574(void* e);
void fn_80265840(void* a, void* b, int c);
void fn_8026654C(void);
void fn_8026697C(void);
void fn_802662EC(void);
void fn_800712E8(int x, int y, int a);
void fn_800C4AA8(void* p);
void fn_800C4240(void* p);
void fn_80263B64(void);
void fn_800763E0(const char* s);
void fn_801C6EAC(const char* a, const char* b, char* out);
void fn_80068C08(void);
extern int* lbl_804CC00C;


class DtorObj28 {
public:
    u8 pad[0x28];
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void dtor(int del);
};
void fn_802636F0(void);


}

/* ---- from rN_8025EEF0/wip/fn_802643B8.cpp ---- */
extern "C" {
/* fn_802643B8: 10 words. st should be r30, the page-match flag r29; increments come y, then ofs. */
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_800CB3A8(s16 x, s16 y, u8 a, int b, int c, f32 s, f32 t, const char* f, ...);
void fn_80072ACC(int x, int y, int w, int h, int a, int b, int c);
void fn_800712E8(int x, int y, int a);
const char* fn_80118C44(void* p);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_801C6DA0(f32 x, f32 y, int a, const char* s);

static inline u8 pageSel(DictState* st, int i) { return st->page - i == 0; }

#pragma push
#pragma use_lmw_stmw off
void fn_802643B8(int x, int y) {
    DictState* st = lbl_804CC004;
    int ofs;
    int i;
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    i = 0;
    ofs = 0;
    do {
        int sel = i == st->page;
        fn_800CB3A8(x, y, (u8)sel, 1, 0, 1.0f, 0.0f, fn_800D0864(*(const char**)((u8*)lbl_804306E8.t0 + ofs)));
        i++;
        y += 0x18;
        ofs += 8;
    } while (i < 2);
    if (lbl_804CC004->mode == 0) {
        fn_801BCA5C(-1.0f);
        fn_80072ACC(st->m1A + 0x2E, st->m1C + 0xC, 0xB4, 0x17, 0x19, 0x4B, 1);
        fn_801BCA5C(-1.0f);
        fn_800712E8(st->m1A, st->m1C, 1);
        fn_801BCA5C(2.0f);
    }
    fn_801BCA5C(1.0f);
}
#pragma pop

}
