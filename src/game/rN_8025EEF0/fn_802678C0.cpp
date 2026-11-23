/* Unit slot menu: move the cursor and handle the buttons */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

struct Slot { void* unit; s16 a; s16 b; };
extern Slot lbl_80430740[3][20];
struct Pt { s16 x, y; Pt() {} Pt(const Pt& o) { *(u16*)&x = *(u16*)&o.x; *(u16*)&y = *(u16*)&o.y; } };
static inline BOOL ne(const Pt& a, const Pt& b) { BOOL r = 0; if (a.x != b.x || a.y != b.y) r = 1; return r; }
struct Tag { void* vt; const void* name; u8 pad[8]; };
extern s8 lbl_804CC020; extern void* lbl_804CC024;
extern s8 lbl_804CC028; extern void* lbl_804CC02C;
extern s8 lbl_804CC030;
extern char lbl_80383F28[], lbl_80391C70[], lbl_80391C18[], lbl_80391A98[], lbl_80391CC8[];
extern Tag lbl_80430730;
extern char lbl_80391E14[], lbl_80391D5C[], lbl_80391E04[], lbl_80391DF0[], lbl_80391DD8[], lbl_80391DC8[];
void fn_8017A968(void* p, void* q);
void fn_80253EE4(void* p, f32 v);
void fn_800D5448(void* a, void* b, int c);
void fn_801E6B64(f32 x, f32 y, void* s, void* p);

struct SlotCur { u8 pad[0x3C]; void* unit; };
struct SlotAnim { u8 pad[0x30]; u8 m30; s8 m31; u8 pad32[0xA]; void* unit; u8 pad40[8]; f32 m48; f32 m4C; f32 m50; };
struct PtP { s16 x, y; };
static inline PtP mk(u32 r) { PtP p; p.x = r >> 16; p.y = r; return p; }
#define NXT m->p.x = (g2 + 1) % 3; m->p.y &= ~3;
struct SlotMenuB { u8 pad[0x30]; };
struct SlotMenu : SlotMenuB {
    virtual u32 pos();
    u8 pad34[8];
    void* m3C;
    SlotCur* cur;
    SlotAnim* anim;
    u8 pad48;
    u8 m49;
    u8 m4A;
    u8 pad4B;
    Pt p;
    s16 grp2;
    s16 idx2;
    u8 pad54[4];
    int m58;
};

static inline BOOL isEnd(SlotMenu* m, Slot* row, s16 i) {
    BOOL r;
    if (i == 0x13) {
        r = 1;
    } else if (m->m49) {
        r = 0;
        if (row[i].unit == 0 && row[i + 1].unit == 0) r = 1;
    } else {
        r = row[i + 1].unit == 0;
    }
    return r;
}

static inline void isEnd8(SlotMenu* m, Slot* row, s16 i, BOOL& r) {
    if (i == 0x13) {
        r = 1;
    } else if (m->m49) {
        r = 0;
        if (row[i].unit == 0 && row[i + 1].unit == 0) r = 1;
    } else {
        r = row[i + 1].unit == 0;
    }
}
static inline void down(SlotMenu* m, int held, int pr, Slot* row, s16 i) {
    if (i < 0x10 && (i = ((i + 4) & ~3) - 1, !isEnd(m, row, i))) {
        m->p.y += 4;
    } else if (held == pr) {
        m->p.y &= 3;
    }
}

static inline void moveCursor2(SlotMenu* m) {
/*P*/
    int held;
    int pr;
    int k;
    Slot* row;
    s16 i;
    s16 i3;
    Slot* row3;
    int mod;
    s16 j;
/*E*/
        held = lbl_804CB5B8->v3C();
        pr = lbl_804CB5B8->v48();
        Pt old(m->p);
        if (held & 0x100001) {
            s16 i = m->p.y;
            if (i % 4 != 0) {
                m->p.y = i - 1;
            } else {
                s16 g = m->p.x;
                if (g != 0) {
                    m->p.x = g - 1;
                    m->p.y = i + 3;
                } else if (held == pr) {
                    m->p.x = 2;
                    m->p.y = i + 3;
                }
            }
        } else if (held & 0x200002) {
            s16 i2;
            s16 g2;
            Slot* row2;
            BOOL r2;
            i2 = m->p.y;
            g2 = m->p.x;
            row2 = lbl_80430740[g2];
            if (i2 % 4 != 3 && (isEnd8(m, row2, i2, r2), !r2)) {
                m->p.y++;
            } else if (g2 != 2) {
            NXT
            } else if (held == pr) {
            NXT
            }
        }
        if (held & 0x800008) {
            s16 i = m->p.y;
            if (i >= 4) {
                m->p.y = i - 4;
            } else if (held == pr) {
                m->p.y = i + 0x10;
            }
        } else if (held & 0x400004) {
            down(m, held, pr, lbl_80430740[m->p.x], m->p.y);
        }
        {
            i3 = m->p.y;
            row3 = lbl_80430740[m->p.x];
            if (row3[i3].unit == 0) {
                mod = i3 % 4;
                while (row3[j = m->p.y].unit == 0) {
                    m->p.y--;
                }
                if (j < 0x13 && row3[j].unit != 0 && m->m49) {
                    m->p.y = j + 1;
                }
                while (mod < m->p.y % 4) {
                    m->p.y--;
                }
            }
        }
        {
            if (ne(old, m->p)) fn_80253EE4(lbl_80391D5C, 0.0f);
        }
    }

static inline void moveCursor(SlotMenu* m) { moveCursor2(m); }

void fn_802678C0(SlotMenu* m) {
/*P*/
    void* unit;
/*E*/
    unit = lbl_80430740[m->p.x][m->p.y].unit;
    fn_8017A968(m->m3C, lbl_80391E14);
    if (!inputBlocked()) {
        moveCursor(m);
    }
    {
        void* u2 = lbl_80430740[m->p.x][m->p.y].unit;
        if (unit != u2) {
            if (unit != 0 && u2 == 0) {
                SlotAnim* an = m->anim;
                if ((int)*(u8*)&an->m31 != 1) {
                    an->m48 = 64.0f;
                    an->m4C = 0.0f;
                    an->m30 = 0;
                    an->m50 = 800.0f;
                    an->m31 = 1;
                    fn_80083DC4(an, 2);
                }
            } else if (unit == 0 && u2 != 0) {
                SlotAnim* an = m->anim;
                if (an->m31) {
                    an->m48 = 64.0f;
                    an->m4C = 0.0f;
                    an->m30 = 0;
                    an->m50 = 798.0f;
                    an->m31 = 0;
                    fn_80083DC4(an, 1);
                }
                m->anim->unit = lbl_80430740[m->p.x][m->p.y].unit;
            } else if (u2 != 0) {
                m->anim->unit = u2;
            }
            unit = lbl_80430740[m->p.x][m->p.y].unit;
        }
    }
    if (!inputBlocked()) {
        int pp = lbl_804CB5B8->v48();
        if (pp & 0x400) {
            if (unit != 0 && (*(u32*)((u8*)unit + 0x10C) & 0x10000)) {
                PtP t = mk(m->pos());
                fn_801E6B64(t.x, t.y, lbl_80391E04, m);
            } else if (unit != 0 && m->cur->unit == unit) {
                PtP t = mk(m->pos());
                fn_801E6B64(t.x, t.y, lbl_80391DF0, m);
            } else {
                fn_80083B78(m);
                fn_80253EE4(lbl_80391DD8, 0.0f);
            }
        } else if ((pp & 0x2000) && unit != 0) {
            m->m58 = 1;
            fn_80083DC4(m, 5);
        } else if ((pp & 0x1000) && unit != 0) {
            m->m58 = 1;
            fn_80083DC4(m, 6);
        } else if (pp & 0x800) {
            SlotAnim* an;
            m->p.x = m->grp2;
            m->p.y = m->idx2;
            an = m->anim;
            m->m49 = 0;
            if ((int)*(u8*)&an->m31 != 1) {
                an->m48 = 64.0f;
                an->m4C = 0.0f;
                an->m30 = 0;
                an->m50 = 800.0f;
                an->m31 = 1;
                fn_80083DC4(an, 2);
            }
            fn_80083DC4(m, 0);
            fn_80253EE4(lbl_80391DC8, 0.0f);
        }
    }
}

}
