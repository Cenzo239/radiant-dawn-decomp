#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

typedef struct AnimRes {
    u8 pad[0x18];
    int frames; /* 0x18 */
} AnimRes;

typedef struct Anim {
    u8 pad[0x58];
    f32 frame; /* 0x58 */
} Anim;

typedef struct ModelNode {
    Anim* anim; /* 0x0 */
} ModelNode;

typedef struct Model {
    u8 pad[0x30];
    ModelNode* node; /* 0x30 */
} Model;

typedef struct EvProc {
    u8 pad[0x40];
    void* unk40;  /* 0x40 */
    void* unk44;  /* 0x44 */
    u8 pad48[0xC];
    struct EvUnit* unit; /* 0x54 */
} EvProc;

typedef struct EvUnitData {
    u8 pad[0x24];
    u8 name[1]; /* 0x24 */
} EvUnitData;

typedef struct EvUnit {
    u8 pad[0xF0];
    EvUnitData* data; /* 0xF0 */
} EvUnit;

class Pad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 getTrigger(); /* vtable +0x34 */
};

typedef struct StateProc {
    u8 pad[0x30];
    u8 state; /* 0x30 */
} StateProc;

extern Pad* lbl_804CB5B8;
extern void* lbl_804CA4E4;
extern u8 lbl_803C8E80[];
extern u8 lbl_80388140[];
extern Model* fn_800E45B0(int id);
extern void fn_80083DC4(void* proc, int result); /* script proc: finish with result */
extern void fn_80083B78(void* proc);
extern BOOL fn_80008C98(Anim* a, int ev);
extern AnimRes* fn_80007F10(Anim* a);
extern void fn_800A4B00(void* a, void* b);
extern void fn_800A4A98(void* a);
extern void fn_800E4B20(Model* m, int frame);
extern void fn_800C835C(int a, int b);
extern void fn_800E4548(void);
extern void fn_802551E8(f32 v);
extern void fn_800A9E64(void* p, int a, int b);
extern BOOL fn_8011B77C(void* name, void* key);
extern void fn_801AA148(void* sys, void* p);
extern void fn_801AA0DC(void* sys, void* p);
extern void* fn_80083B84(void* cls);
extern void fn_801D5EC8(void);

void fn_80186544(EvProc* p)
{
    Model* m = fn_800E45B0(6);
    if (m == NULL) {
        fn_80083DC4(p, 0);
        return;
    }
    Anim* a = m->node->anim;
    if (a != NULL) {
        if (fn_80008C98(a, 0)) {
            fn_800A4B00(p->unk44, p->unk40);
        }
        if (fn_80008C98(a, 5)) {
            fn_800E4B20(m, (f32)fn_80007F10(a)->frames - a->frame);
            fn_80083B78(p);
            return;
        }
    }
    if (lbl_804CB5B8->getTrigger() & 0xFFF0) {
        fn_800C835C(3, 0x10A);
        fn_80083DC4(p, 1);
    }
}

void fn_80186668(EvProc* p)
{
    fn_800E4548();
    fn_802551E8(133.0f);
    fn_800A4B00(p->unk44, p->unk40);
    fn_800A4A98(p->unk44);
}

static inline BOOL StateProc_IsActive(StateProc* s)
{
    if (s != NULL) {
        switch (s->state) {
        case 1:
        case 2:
        case 3:
        case 4:
            return TRUE;
        }
    }
    return FALSE;
}

void fn_801866B0(EvProc* p)
{
    fn_800A9E64(p, 100, 0xB4);
    if (fn_8011B77C(p->unit->data->name, lbl_804CA4E4)) {
        fn_801AA148(lbl_803C8E80, p);
    } else {
        fn_801AA0DC(lbl_803C8E80, p);
    }
    if (StateProc_IsActive((StateProc*)fn_80083B84(lbl_80388140))) {
        fn_801D5EC8();
    }
}

}
