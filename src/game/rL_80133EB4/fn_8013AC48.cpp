/* Looks the map up in the environment sound table and copies its parameters. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct SndMap { const char* name; u8 a, b; u8 pad[2]; f32 x, y, z; };
struct Env2 { u8 pad[0x6A]; u8 a, b; f32 x, y, z; };
struct MA2 { u8 pad0[0x8A]; char name[0x27]; u8 xb1; };
#define MapModel MA2
extern "C" {
extern char lbl_803694D4[];
#if TARGET_PC
extern FE10_PROTO void * fn_80076F54(const char*);
#else
extern int fn_80076F54(const char*);
#endif
extern int* fn_80077064(const char*);
extern int fn_80291188(const char*, const char*);
static inline SndMap* FindA(const char* const& name) {
    /*P*/
    const char* f;
    int* d;
    int n;
    SndMap* e;
    int i;
/*E*/
    f = lbl_803694D4 + 0x1BA;
    if (fn_80076F54(f)) {
        d = fn_80077064(f);
        n = *d;
        e = (SndMap*)(d + 1);
        for (i = 0; i < n; i++, e++) {
            if (e->name && fn_80291188(e->name, name) == 0) return e;
        }
    }
    return 0;
}
static inline SndMap* FindB(const char* const& name) {
    /*P*/
    const char* f;
    int n;
    int i;
    SndMap* e;
    int* d;
/*E*/
    f = lbl_803694D4 + 0x1BA;
    if (fn_80076F54(f)) {
        d = fn_80077064(f);
        n = *d;
        e = (SndMap*)(d + 1);
        for (i = 0; i < n; i++, e++) {
            if (e->name && fn_80291188(e->name, name) == 0) return e;
        }
    }
    return 0;
}
static inline SndMap* FindB2(const char* name) { return FindB(name); }
static inline SndMap* FindC(const char* const& name) {
    /*P*/
    const char* f;
    int* d;
    int n;
    SndMap* e;
    int i;
/*E*/
    f = lbl_803694D4 + 0x1BA;
    if (fn_80076F54(f)) {
        d = fn_80077064(f);
        n = *d;
        e = (SndMap*)(d + 1);
        for (i = 0; i < n; i++, e++) {
            if (e->name && fn_80291188(e->name, name) == 0) return e;
        }
    }
    return 0;
}
void fn_8013AC48(MapModel* mm) {
    const char* nb;
    char* name = mm->name;
    if (name) {
        SndMap* e = FindA(name);
        if (e == 0) {
            switch (mm->xb1) {
            case 0:
                { const char* nb = lbl_803694D4 + 0x1C7; e = FindB2(nb); }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                { const char* nc = lbl_803694D4 + 0x1CE; e = FindC(nc); }
                break;
            }
        }
        if (e) {
            Env2* v = (Env2*)mm;
            v->a = e->a;
            v->b = e->b;
            v->x = e->x;
            v->y = e->y;
            v->z = e->z;
        }
    }
}

}
