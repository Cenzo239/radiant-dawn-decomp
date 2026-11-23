#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

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
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual u32 getHeld();    /* vtable +0x48 */
};

typedef struct StateProc {
    u8 pad[0x30];
    u8 state; /* 0x30 */
} StateProc;

typedef struct EvUnitData {
    u8 pad[0x24];
    u8 name[1]; /* 0x24 */
} EvUnitData;

typedef struct EvUnit {
    u8 pad[0xF0];
    EvUnitData* data; /* 0xF0 */
} EvUnit;

typedef struct ChildProc {
    u8 pad[0x54];
    void* unit; /* 0x54 */
} ChildProc;

typedef struct EvProc2 {
    u8 pad[0x30];
    u8 mode;      /* 0x30 */
    u8 pad31[3];
    struct EvUnit* unit; /* 0x34 */
    u32 savedFlag; /* 0x38 */
    u8 unk3C;     /* 0x3C */
    u8 active;    /* 0x3D */
    u8 unk3E;     /* 0x3E */
    u8 pad3F;
    s16 unk40;    /* 0x40 */
} EvProc2;

/* class-change event process (class lbl_80388140): mode at +0x30, unit at +0x34 */
typedef EvProc2 ClassChangeProc;

typedef struct Model Model;
typedef struct ModelNode {
    u8 pad[0x8];
    s16 unk8;                   /* 0x08 */
    u8 padA[0x98 - 0xA];
    void (*onStart)(void);      /* 0x98 */
    void (*onUpdate)(Model* m); /* 0x9C */
    void (*onEnd)(void);        /* 0xA0 */
} ModelNode;

struct Model {
    u8 pad[0x30];
    ModelNode* node; /* 0x30 */
};

extern Pad* lbl_804CB5B8;
extern u32 lbl_804CB700;
extern u8 lbl_80388140[];
extern u8 lbl_803880A0[]; /* process class */
extern u8 lbl_803C8DA0[0xD0];
extern const char lbl_8036BCAC[];
extern ChildProc* fn_80081194(void* cls, void* parent);
extern void* fn_80083B84(void* cls);
extern u8 fn_8013B9CC(void);
extern void fn_80134E30(void);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */
extern void fn_80250D64(f32 a, f32 b, int ch);
extern void fn_800E4B20(Model* m, int frame);

void fn_801868E8(void* unit, void* parent)
{
    fn_80081194(lbl_803880A0, parent)->unit = unit;
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

void fn_80186920(EvProc2* p)
{
    p->unk3E = fn_8013B9CC();
    p->active = StateProc_IsActive((StateProc*)fn_80083B84(lbl_80388140));
    p->unk3C = 0;
    p->unk40 = 0;
    if (p->mode == 5) {
        lbl_803C8DA0[0xA1] = 1;
    }
}

void fn_801869B4(EvProc2* p)
{
    p->savedFlag = lbl_804CB700 & 4;
    lbl_804CB700 |= 4;
}

void fn_801869D0(EvProc2* p)
{
    if (p->savedFlag == 0) {
        lbl_804CB700 &= ~4;
    }
}

void fn_801869EC(EvProc2* p)
{
    if (p->unk3E) {
        fn_80134E30();
    }
    fn_80081194(lbl_803880A0, p)->unit = p->unit;
}

void fn_80186A44(void)
{
    fn_80253EE4(0.0f, lbl_8036BCAC + 0x4D /* "SFX_FF_LEVEL_UP1" */);
    fn_80250D64(0.5f, 500.0f, 6);
}

void fn_80186A84(void)
{
    fn_80250D64(1.0f, 1000.0f, 6);
}

void fn_80186A94(Model* m)
{
    if (lbl_804CB5B8->getHeld() & 0xFFF0) {
        fn_800E4B20(m, -1);
        m->node->onUpdate = NULL;
    }
}

extern void* lbl_804CA4E0;
extern BOOL fn_8011B77C(void* name, void* key);
extern Model* fn_800E3A10(const char* name, void* parent); /* spawn effect */
extern void fn_80068AFC(int ms);
extern void fn_80068A6C(int ms);
extern void fn_80068AB4(int ms);
extern s16 fn_80068CF8(void);
extern void fn_80134DB0(void);
extern void fn_80062598(void* sys, void* p);
extern void fn_8012D78C(void);
extern u8 lbl_803CAB38[];

static inline void SpawnClassChangeFx(EvUnit* unit, void* parent)
{
    if (unit != NULL) {
        fn_8011B77C(unit->data->name, lbl_804CA4E0);
        Model* m = fn_800E3A10(lbl_8036BCAC + 0x5E /* "EID_CLASSCHANGE1_F" */, parent);
        if (m != NULL) {
            m->node->onStart = fn_80186A44;
            m->node->onEnd = fn_80186A84;
            m->node->onUpdate = fn_80186A94;
            m->node->unk8 = 200;
        }
    }
}

void fn_80186AF0(EvUnit* unit, void* parent)
{
    SpawnClassChangeFx(unit, parent);
}

void fn_80186B88(EvProc2* p)
{
    if (p->mode != 5) {
        SpawnClassChangeFx(p->unit, p);
    }
}

void fn_80186C30(void)
{
    fn_80068AFC(1000);
    fn_80068A6C(1000);
}

void fn_80186C5C(void)
{
    fn_80068AB4(1000);
}

void fn_80186C64(EvProc2* p)
{
    if (p->unk3E) {
        p->unk40 = fn_80068CF8();
        fn_80134DB0();
        fn_80062598(lbl_803CAB38, p);
    }
    fn_8012D78C();
}

extern void fn_80062380(void* sys, void* p);
extern void fn_80062454(void* sys);
extern void fn_80068D34(int v);
extern void fn_801314E0(void);
extern void fn_8012D620(void);
extern void fn_8012D6B4(void);
extern void fn_8012DDBC(void);
extern void fn_8012D908(void);
extern void fn_801D3E68(void);
extern void fn_80058638(void);
extern void fn_801D3ED0(void);
extern void fn_8005868C(void);
extern void fn_803080DC(int x0, int y0, int x1, int y1);

void fn_80186CB8(EvProc2* p)
{
    if (p->unk3E) {
        fn_80062380(lbl_803CAB38, lbl_803CAB38 + 0x914);
        fn_80134E30();
        fn_80062454(lbl_803CAB38);
        fn_80068D34(p->unk40);
        fn_801314E0();
    }
    switch (p->mode) {
    case 1:
    case 2:
    case 3:
    case 4:
        fn_8012D620();
        fn_8012D6B4();
        fn_8012DDBC();
        break;
    default:
        fn_8012D620();
        break;
    }
    fn_8012D908();
}

void fn_80186D4C(EvProc2* p)
{
    switch (p->mode) {
    case 1:
    case 2:
        fn_801D3E68();
        break;
    case 3:
    case 4:
        fn_80058638();
        break;
    }
}

void fn_80186D7C(EvProc2* p)
{
    switch (p->mode) {
    case 1:
    case 2:
        fn_801D3ED0();
        break;
    case 3:
    case 4:
        fn_8005868C();
        break;
    }
}

typedef struct UnitClassInfo {
    u8 pad[0x14];
    void* unk14; /* 0x14 */
} UnitClassInfo;

typedef struct CCUnit {
    u8 pad[0xF0];
    UnitClassInfo* info; /* 0xF0 */
} CCUnit;

static inline void StartClassChange(CCUnit* unit, void* parent, u8 mode)
{
    if (unit->info->unk14 != NULL) {
        ClassChangeProc* p = (ClassChangeProc*)fn_80081194(lbl_80388140, parent);
        p->unit = (EvUnit*)unit;
        p->mode = mode;
    }
}

void fn_80186DAC(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 0);
}

void fn_80186DFC(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 2);
}

void fn_80186E4C(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 1);
}

void fn_80186E9C(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 4);
}

void fn_80186EEC(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 3);
}

void fn_80186F3C(CCUnit* unit, void* parent)
{
    StartClassChange(unit, parent, 5);
}

typedef struct Rect16 {
    s16 x0, y0, x1, y1;
} Rect16;

void fn_80186F8C(void* p, Rect16* r)
{
    fn_803080DC(r->x0, r->y0, r->x1, r->y1);
}

}
