/* fn_80168098: functionally equal (renamed level per tools/check_regs.py; registers differ from the original). AI: collect the units that act this phase into the order list. Declarations copied from fn_80165B48.cpp (bodies stripped). */
/* AI: move range setup, turn order. */
#include "game/rQ_80163178/types.h"
#pragma use_lmw_stmw on
#pragma auto_inline off
#define ABS(a) ((a) < 0 ? -(a) : (a))

class Filter {
public:
    virtual int check(Unit*);
    virtual int at(int, int, int);
};
struct ListHdr { int n; };
struct Side { Unit* head; Unit* tail; int n; };
struct SkillAct { char* name; void* item; int (*func)(Unit*, int, int, int); };

extern "C" Unit* lbl_804CB810;
static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
extern "C" int fn_8010E398(void*, void*);
static inline BOOL SameT(Unit* a, Unit* b, int w) {
    return (u8)fn_8010E398(a->team, b->team) == w;
}

struct Bf110 { u8 pad[0x110]; u16 a : 9; u16 s : 3; };
class Pad5B8 {
public:
    virtual void v8(); virtual void vc(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual u32 v34();
};
struct Filt {
    void* vt;
    Unit* u;
};
struct Tb { void* n; void (*f)(Unit*, int); };
struct Cmp { int (*f)(u32, u32); };
extern "C" {
extern Side* lbl_804CB814;
extern Pad5B8* lbl_804CB5B8;
extern Tb lbl_80387768[];
extern u8 lbl_80387338[];
void fn_80133034(void);
void fn_8004564C(AiAct*, void*);
int fn_8011B680(void*, u8* skill);
void* fn_8010B23C(void*);
void fn_80152C20(Unit*, void*, int);
int fn_8010931C(void*);
int fn_8016D0B0(Unit*);
u8 fn_80106E30(void*);
void fn_80167704(Side*);
int fn_801681C4(Unit*, Unit*);
void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB830;
extern u32 lbl_804CA5C0;
extern u32 lbl_804CA5C4;
extern int lbl_804CA7B0;
extern SkillAct lbl_80387690[];
extern u8 lbl_80387468[];
extern s16 lbl_8036B218[];
void* fn_8010B228(char*);
u8* fn_8010B240(u8);
void fn_80114888(Map*, int);
void fn_801151BC(Map*, Unit*);
void fn_8011567C(Map*, void*);
void fn_80115658(Map*, int, int);
void fn_80115764(Map*, int, int, u16);
void fn_80114B44(Map*, int, int);
void fn_80115DEC(Map*, int, int, u8, u8);
void fn_80116098(Map*, int, int, u8, u8);
s8 fn_8012408C(Unit*);
int fn_8012B868(Unit*, u8*);
u8 fn_801107C0(u8*, Unit*);
u16 fn_801676D8(int, int);
int fn_8011B77C(void*, u32);
Unit* fn_80127CA0(Unit*);
int fn_8012BB48(Unit*, void*);
void fn_80081194_(void);
void fn_80053A7C(void);
int fn_8015804C(Unit*, int, int);
int fn_801658E4(Unit*, s8, s8);
void fn_80083DC4(void*, int);
void fn_800620A8(u8*, f32, f32);
void fn_801030B8(Unit*, int, int, int, int, void*);

}
static inline BOOL MapOutU(Map* m, Unit* v) {
    s8 x = v->x;
    s8 y = v->y;
    BOOL r = 0;
    if (x < m->x0 || m->x1 - 1 < x || y < m->y0 || m->y1 - 1 < y) {
        r = 1;
    }
    return r;
}
extern "C" int fn_801681C4(Unit*, Unit*);
extern "C" void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
static inline void Sort(Unit** const& b, int n) {
    fn_801681E0(b, b + n, fn_801681C4);
}
static inline Tb* FindTb(Unit* u, u8* s, int k) {
    if (fn_8011B680(u->skills, s)) {
        Tb* t;
        for (t = lbl_80387768; t->f; t++) {
            if (k == ((u8*)fn_8010B23C(t->n))[0x1C] && t->f) {
                return t;
            }
        }
    }
    return 0;
}
static inline SkillAct* FindAct(Unit* u, u8* it) {
    if (fn_8012BB48(u, it)) {
        SkillAct* e;
        for (e = lbl_80387690; e->name; e++) {
            if (it == e->item && e->func) {
                return e;
            }
        }
    }
    return 0;
}
extern "C" {

void fn_80165B48(s8 x, s8 y, Unit* u, int k, int range);

void fn_80165CB0(s8 x, s8 y, Unit* u, int k, int range);

void fn_80165E18(Unit* u, int k, int range);

void fn_80165F94(Unit* u, int k, int range);

void fn_80166110(Unit* u, int k, int range);

void fn_801662AC(int x, int y, u8* s, int k, u16 v);

void fn_801663E0(int x, int y, int a, int r, int k);

void fn_80166580(int x, int y, int a, int r, int k);

u32 fn_80167E94(Unit* u);

int fn_80167F5C(Unit* u);

void fn_80169510(void);

void fn_80168BC0(void* parent);

void fn_80168A90_unused(void);
void fn_801689C8(f32* p);

void fn_80168A90(f32* p);

int fn_8016A8D0(Unit* u);

BOOL fn_80169B20(Unit* u, u16 lim, s16 x, s16 y, Filter* f, s16* ox, s16* oy);

void fn_80169C70(Unit* u, Filter* f);

void fn_80168B54(u8* p);
void fn_80169254(u8* p);
u8 fn_80169718(Unit* u, int a, int b);
u8 fn_80169870(Unit* u, int a, int b);
u8 fn_801699C8(Unit* u, int a, int b);
#pragma use_lmw_stmw off
int fn_8016C9C8(Unit* u, u8* s, int a);
#pragma use_lmw_stmw on
#pragma auto_inline off
void fn_8016CA94(Unit* a, Unit* u);
void fn_801688D0(u32* a, u32* b, u32* c, Cmp* f);
int fn_80168098(void);
void fn_80167E08(void);
}


/* ---- fn_80168098 ---- */
extern "C" {
int fn_80168098(void) {
/*P*/
    Map* m = &lbl_803EC898;
    AiCfg* c = &lbl_804183F0;
    int n = 0;
    int off = 0;
    Unit* v;
    Unit* nx;
/*E*/
    for (v = lbl_804CB814[lbl_803CAB38[0x11]].head; v; v = nx) {
        nx = v->next;
        if (!MapOutU(m, v) && !fn_8010931C((u8*)v + 0x110) && !(v->flags10C & 0x9D) && (!fn_8016D0B0(v) || fn_80106E30(v->ai))) {
            *(int*)((u8*)v + 0x3AC) = fn_80167F5C(v);
            *(Unit**)((u8*)c->order + off) = v;
            n++;
            off = off + sizeof(Unit*);
        }
    }
    return n;
}
}
