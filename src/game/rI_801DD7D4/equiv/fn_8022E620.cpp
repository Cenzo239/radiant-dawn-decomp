/* fn_8022E620: decides whether any unit (or the convoy) can use the shop/forge service: marks the job
   kinds listed in a 0xff-terminated table, scans units 1..254 for a deployed unit of a marked kind that
   passes fn_80129A8C, then the convoy; plays the matching voice line and, when nobody qualifies, shows
   the refusal help text and jumps to state 0x2d. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
struct Job { u8 p[8]; u8 kind; };
struct Un { u8 p[0xec]; int xec; u8 pf0[4]; Job* xf4; };
struct Wi { u8 p[0x64]; const char* a64; };
struct Dat { u8 p[0xc]; void* xc; u8 p10[0x60]; void* x70; u8 p74[0x30]; const char* xa4; };
struct Sm { u8 p[0x88]; Dat* a88; };
extern "C" {
void* memset(void*, int, u32);
int fn_80129A8C(Un*);
int fn_80060754(void*);
void* fn_801059B0(void);
int fn_80105194(void*);
void fn_8014C2AC(void*);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
extern u8 lbl_803CAB38[];
extern u8* lbl_804CB810;
extern int lbl_804CAA88;
}
static inline Un* unitAt(u8 id) { if (id != 0) return (Un*)(lbl_804CB810 + (id - 1) * 0x3f0); return NULL; }
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
extern "C" void fn_8022E620(Sm* s) {
    BOOL found = FALSE;
    u8 map[0xb];
    u8 kinds[3] = { 0, 5, 0xff };
    u8* p;
    int i;
    memset(map, (u8)lbl_804CAA88, 0xb);
    for (p = kinds; *p != 0xff; p++) map[*p] = 1;
    for (i = 1; i <= 0xfe; i++) {
        Un* u = unitAt(i);
        if (u->xec != 0 && map[u->xf4->kind] != 0 && fn_80129A8C(u) >= 0) {
            found = TRUE;
            break;
        }
    }
    if (!found && fn_80060754(lbl_803CAB38)) {
        if (fn_80105194(fn_801059B0()) >= 0) found = TRUE;
    }
    if (found) {
        fn_8014C2AC(s->a88->xc);
    } else {
        fn_8014C2AC(s->a88->x70);
        setHelpV(s, s->a88->xa4);
        fn_80083DC4(s, 0x2d);
    }
}
