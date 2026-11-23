/*
 * fn_8004B870 (round 22 draft, not compared at a counted level: `other`).
 * Static initialiser (__sinit) of the translation unit around 0x8004xxxx whose file-static data pool
 * is lbl_8037B268 (.data, scripts) and whose .bss pool is lbl_803CAA20 (0x118 bytes of objects).
 * It sets, in this order in the original:
 *   - about 60 small-data pointers (lbl_804CB2D8..lbl_804CB3F0) to tables in .data (proc scripts),
 *     one of them (lbl_804CB348 = lbl_8037CF90 + 0x58) computed through a stack spill;
 *   - eighteen 12-byte objects {script, vtable, u16, u16} in the .bss pool and one 8-byte {script,
 *     vtable} object in .sbss (lbl_804CB3B0). Each constructor first stores the base vtable
 *     lbl_80383F28 and then its own; three classes have a middle class (lbl_803804E4, lbl_80380050);
 *   - an item slot (FSlot, 0x28 bytes) at lbl_803CAAE0, constructed by fn_80111B34 and registered
 *     for destruction (fn_80111C24) with its record at lbl_803CAAD4 (= pool + 0xB4);
 *   - an item reference at lbl_804CB3E8 (pointer 0, kind 2, flag: the `if (p) flag = ...` of the
 *     Ref constructor is kept by the compiler here as a real test of the constant 0).
 * Every store was extracted from the original by symbolic evaluation of the asm, and the same
 * evaluation of this file's compiled code gives the same final memory state for all 107 stored
 * locations (the only difference is that the compiler folds the `if (p)` of the item reference, which
 * the original keeps as a test of a register holding 0; same result).
 *
 * What differs from the original code: the original references both pools through one base register
 * each (`addi rX, r30, off` on lbl_8037B268, `stw rY, off(r31)` on lbl_803CAA20) because the objects
 * are file statics of its own translation unit; here they are externs with their symbols.txt names
 * (data pool offsets written as lbl_8037B268 + off), so the code is lis/addi per object. The register
 * spill of lbl_804CB348 is not reproduced. Writing the pools as real file statics needs the TU's whole
 * .data pool (0x268+ bytes of scripts with relocations) reconstructed from the DOL: not done.
 *
 * Port: these are global definitions with initialisers (pointer globals) and C++ objects whose
 * constructors only set a script pointer and a vtable; define them as such and drop this function.
 */
#include "game/rB_8002E1C4/types.h"
#pragma use_lmw_stmw on

extern "C" {

struct ScriptObj {          /* 12 bytes: script pointer, vtable, two halfwords (only some classes) */
    const void* script;
    const void* vt;
    u16 a, b;
};

struct ScriptRef {          /* 8 bytes: script pointer, vtable */
    const void* script;
    const void* vt;
};

struct ItemRef {            /* 8 bytes: item pointer, kind, flag (as in fn_8004B03C) */
    u8* p;
    u8 kind;
    u8 flag;
};

struct DtorRecord { void* next; void* dtor; void* obj; };

extern const void* lbl_804CB2D8;
extern const void* lbl_804CB2DC;
extern const void* lbl_804CB2E0;
extern const void* lbl_804CB2E4;
extern const void* lbl_804CB2E8;
extern const void* lbl_804CB2EC;
extern const void* lbl_804CB2F0;
extern const void* lbl_804CB2F8;
extern const void* lbl_804CB300;
extern const void* lbl_804CB304;
extern const void* lbl_804CB308;
extern const void* lbl_804CB30C;
extern const void* lbl_804CB310;
extern const void* lbl_804CB314;
extern const void* lbl_804CB318;
extern const void* lbl_804CB31C;
extern const void* lbl_804CB320;
extern const void* lbl_804CB324;
extern const void* lbl_804CB328;
extern const void* lbl_804CB32C;
extern const void* lbl_804CB330;
extern const void* lbl_804CB334;
extern const void* lbl_804CB338;
extern const void* lbl_804CB33C;
extern const void* lbl_804CB340;
extern const void* lbl_804CB344;
extern const void* lbl_804CB350;
extern const void* lbl_804CB358;
extern const void* lbl_804CB35C;
extern const void* lbl_804CB360;
extern const void* lbl_804CB364;
extern const void* lbl_804CB368;
extern const void* lbl_804CB36C;
extern const void* lbl_804CB370;
extern const void* lbl_804CB374;
extern const void* lbl_804CB378;
extern const void* lbl_804CB37C;
extern const void* lbl_804CB380;
extern const void* lbl_804CB384;
extern const void* lbl_804CB388;
extern const void* lbl_804CB38C;
extern const void* lbl_804CB390;
extern const void* lbl_804CB394;
extern const void* lbl_804CB398;
extern const void* lbl_804CB39C;
extern const void* lbl_804CB3A0;
extern const void* lbl_804CB3A4;
extern const void* lbl_804CB3A8;
extern const void* lbl_804CB3AC;
extern const void* lbl_804CB3B8;
extern const void* lbl_804CB3BC;
extern const void* lbl_804CB3C0;
extern const void* lbl_804CB3C4;
extern const void* lbl_804CB3C8;
extern const void* lbl_804CB3CC;
extern const void* lbl_804CB3D0;
extern const void* lbl_804CB3D4;
extern const void* lbl_804CB3DC;
extern const void* lbl_804CB3F0;
extern const void* lbl_804CB348;
extern const u8 lbl_8037BDA8[], lbl_8037BE08[], lbl_8037BE60[], lbl_8037BEB8[], lbl_8037BF10[], lbl_8037BF68[], lbl_8037BFC0[], lbl_8037C018[], lbl_8037C070[], lbl_8037C0C8[], lbl_8037C120[], lbl_8037C178[], lbl_8037C1D0[], lbl_8037C228[], lbl_8037C280[], lbl_8037C2D8[], lbl_8037C330[], lbl_8037C388[], lbl_8037C3E0[], lbl_8037C438[], lbl_8037C490[], lbl_8037C4E8[], lbl_8037C540[], lbl_8037C598[], lbl_8037C5F0[], lbl_8037C648[], lbl_8037C6A0[], lbl_8037C6F8[], lbl_8037C750[], lbl_8037C7A8[], lbl_8037C800[], lbl_8037C858[], lbl_8037C8B0[], lbl_8037C908[], lbl_8037C960[], lbl_8037C9B8[], lbl_8037CA10[], lbl_8037CA68[], lbl_8037CAC0[], lbl_8037CB18[], lbl_8037CB70[], lbl_8037CBC8[], lbl_8037CC20[], lbl_8037CC78[], lbl_8037CCD0[], lbl_8037CD28[], lbl_8037CD80[], lbl_8037CDD8[], lbl_8037CE30[], lbl_8037CE88[], lbl_8037CEE0[], lbl_8037CF38[], lbl_8037CF90[], lbl_8037D04C[], lbl_8037D0B0[], lbl_8037D108[], lbl_8037D160[], lbl_8037D1B8[], lbl_8037D210[];
extern const u8 lbl_8037B268[];          /* .data pool of the TU */
extern const u8 lbl_80383F28[];          /* base class vtable */
extern const u8 lbl_803804E4[], lbl_80380238[], lbl_80380050[];
extern const u8 lbl_8037BD14[], lbl_8037BC80[], lbl_8037BBEC[], lbl_8037BB50[], lbl_8037BAB4[];
extern const u8 lbl_8037BA18[], lbl_8037B984[], lbl_8037B8F0[], lbl_8037B854[], lbl_8037B7C0[];
extern const u8 lbl_8037B72C[], lbl_8037B690[], lbl_8037B5FC[], lbl_8037B560[], lbl_8037B4CC[];
extern const u8 lbl_804CA0C8[8];
extern ScriptObj lbl_803CAA20, lbl_803CAA2C, lbl_803CAA38, lbl_803CAA44, lbl_803CAA50, lbl_803CAA5C;
extern ScriptObj lbl_803CAA68, lbl_803CAA74, lbl_803CAA80, lbl_803CAA8C, lbl_803CAA98, lbl_803CAAA4;
extern ScriptObj lbl_803CAAB0, lbl_803CAABC, lbl_803CAAC8;
extern DtorRecord lbl_803CAAD4;          /* pool + 0xB4 (inside the analyser's lbl_803CAAC8) */
extern u8 lbl_803CAAE0[0x28];            /* FSlot */
extern ScriptObj lbl_803CAB08, lbl_803CAB14, lbl_803CAB20, lbl_803CAB2C;
extern ScriptRef lbl_804CB3B0;
extern ItemRef lbl_804CB3E8;
void* fn_80111B34(void* slot);
void* fn_80111C24(void* slot, int del);
void* __register_global_object(void* obj, void* dtor, void* rec);

}

static inline void Base(ScriptObj* o) { o->vt = lbl_80383F28; }
static inline void Base(ScriptRef* o) { o->vt = lbl_80383F28; }

static inline void Init(ScriptObj* o, const void* script, const void* vt)
{
    Base(o);
    o->script = script;
    o->vt = vt;
}

extern "C" void fn_8004B870(void)
{
    u8* p;
    lbl_804CB2D8 = lbl_8037D210;
    lbl_804CB2DC = lbl_8037D1B8;
    lbl_804CB2E0 = lbl_8037D160;
    lbl_804CB2E4 = lbl_8037CEE0;
    lbl_804CB2E8 = lbl_8037CE88;
    lbl_804CB2EC = lbl_8037CE30;
    lbl_804CB2F0 = lbl_8037CDD8;
    lbl_804CB2F8 = lbl_8037CD80;
    lbl_804CB300 = lbl_8037CD28;
    lbl_804CB304 = lbl_8037CCD0;
    lbl_804CB308 = lbl_8037CC78;
    lbl_804CB30C = lbl_8037CC20;
    lbl_804CB310 = lbl_8037CBC8;
    lbl_804CB314 = lbl_8037C858;
    lbl_804CB318 = lbl_8037C648;
    lbl_804CB31C = lbl_8037C8B0;
    lbl_804CB320 = lbl_8037CB70;
    lbl_804CB324 = lbl_8037CB18;
    lbl_804CB328 = lbl_8037CAC0;
    lbl_804CB32C = lbl_8037CA68;
    lbl_804CB330 = lbl_8037CA10;
    lbl_804CB334 = lbl_8037C9B8;
    lbl_804CB338 = lbl_8037C960;
    lbl_804CB33C = lbl_8037C908;
    lbl_804CB340 = lbl_8037D0B0;
    lbl_804CB344 = lbl_8037D04C;
    lbl_804CB350 = lbl_8037CF90;
    lbl_804CB348 = lbl_8037CF90 + 0x58;

    Base(&lbl_803CAA20);
    lbl_803CAA20.script = lbl_8037B268;
    lbl_803CAA20.a = 0;
    lbl_803CAA20.b = 1;
    lbl_803CAA20.vt = lbl_8037BD14;
    Base(&lbl_803CAA2C);
    lbl_803CAA2C.script = lbl_8037B268 + 0x94;
    lbl_803CAA2C.a = 0;
    lbl_803CAA2C.b = 1;
    lbl_803CAA2C.vt = lbl_8037BD14;
    Init(&lbl_803CAA38, lbl_8037B268 + 0xA0, lbl_803804E4);
    lbl_803CAA38.vt = lbl_80380238;

    Base(&lbl_804CB3B0);
    lbl_804CB3B0.script = lbl_8037B268 + 0xF8;
    lbl_804CB3B0.vt = lbl_803804E4;

    Init(&lbl_803CAA44, lbl_804CA0C8, lbl_8037BC80);
    Init(&lbl_803CAA50, lbl_8037B268 + 0xC0, lbl_80380238);
    Init(&lbl_803CAA5C, lbl_8037B268 + 0x110, lbl_80380238);
    Init(&lbl_803CAA68, lbl_8037B268 + 0x130, lbl_80380050);
    lbl_803CAA68.vt = lbl_8037BBEC;
    Init(&lbl_803CAA74, lbl_8037B268 + 0x13C, lbl_8037BB50);
    Init(&lbl_803CAA80, lbl_8037B268 + 0x13C, lbl_8037BAB4);
    Init(&lbl_803CAA8C, lbl_8037B268 + 0x13C, lbl_8037BA18);
    Init(&lbl_803CAA98, lbl_8037B268 + 0x13C, lbl_8037B984);
    Init(&lbl_803CAAA4, lbl_8037B268 + 0x13C, lbl_8037B8F0);
    Init(&lbl_803CAAB0, lbl_8037B268 + 0x13C, lbl_8037B854);
    Init(&lbl_803CAABC, lbl_8037B268 + 0x158, lbl_8037B7C0);
    Init(&lbl_803CAAC8, lbl_8037B268 + 0x178, lbl_8037B72C);
    lbl_804CB358 = lbl_8037CF38;
    lbl_804CB35C = lbl_8037D108;
    lbl_804CB360 = lbl_8037C800;
    lbl_804CB364 = lbl_8037C438;
    lbl_804CB368 = lbl_8037C3E0;
    lbl_804CB36C = lbl_8037C7A8;
    lbl_804CB370 = lbl_8037C750;
    lbl_804CB374 = lbl_8037C6F8;
    lbl_804CB378 = lbl_8037C6A0;
    lbl_804CB37C = lbl_8037C5F0;
    lbl_804CB380 = lbl_8037C598;
    lbl_804CB384 = lbl_8037C540;
    lbl_804CB388 = lbl_8037C4E8;
    lbl_804CB38C = lbl_8037C490;
    lbl_804CB390 = lbl_8037C388;
    lbl_804CB394 = lbl_8037C330;
    lbl_804CB398 = lbl_8037C2D8;
    lbl_804CB39C = lbl_8037C280;
    lbl_804CB3A0 = lbl_8037C228;
    lbl_804CB3A4 = lbl_8037C1D0;
    lbl_804CB3A8 = lbl_8037C178;
    lbl_804CB3AC = lbl_8037C120;
    lbl_804CB3B8 = lbl_8037C0C8;
    lbl_804CB3BC = lbl_8037C070;
    lbl_804CB3C0 = lbl_8037C018;
    lbl_804CB3C4 = lbl_8037BFC0;
    lbl_804CB3C8 = lbl_8037BF68;
    lbl_804CB3CC = lbl_8037BF10;
    lbl_804CB3D0 = lbl_8037BEB8;
    lbl_804CB3D4 = lbl_8037BE60;
    lbl_804CB3DC = lbl_8037BE08;
    lbl_804CB3F0 = lbl_8037BDA8;

    __register_global_object(fn_80111B34(lbl_803CAAE0), (void*)fn_80111C24, &lbl_803CAAD4);

    Init(&lbl_803CAB08, lbl_8037B268 + 0x148, lbl_8037B690);
    Init(&lbl_803CAB14, lbl_8037B268 + 0x198, lbl_8037B5FC);

    p = 0;
    lbl_804CB3E8.p = p;
    lbl_804CB3E8.kind = 2;
    lbl_804CB3E8.flag = 0;
    if (p) {
        lbl_804CB3E8.flag = p[0x20] == 0;
    }

    Init(&lbl_803CAB20, lbl_8037B268 + 0x148, lbl_8037B560);
    Init(&lbl_803CAB2C, lbl_8037B268 + 0x200, lbl_8037B4CC);
}
