#include "game/rG_800A3D88/types.h"

// Attached effect: (re)load its model files named by the data entry.
extern "C" {
struct EData { u8 p[8]; const char* m8; u8 pc[0x21 - 0xC]; u8 m21; };
struct EffL { u8 p[0x30]; void* m30; void* m34; EData* m38; u8 p3c[0x46 - 0x3C]; u16 m46; };
extern u8 lbl_803825A8[];
extern char lbl_80365B64[];
#define S(a) (lbl_80365B64 + ((a) - 0x80365B64))
void fn_800829CC(void*, void*);
void fn_80011CBC(void*, void*);
void fn_80006EE0(void*);
#if TARGET_PC
FE10_PROTO void fn_8023F1A8(ptr32<const void>);
#else
void fn_8023F1A8(void*);
#endif
int fn_80290DDC(char*, const char*, ...);
#if TARGET_PC
FE10_PROTO const char* fn_8017F37C(const char*, const char*, p32arg);
#else
const char* fn_8017F37C(const char*, const char*, int);
#endif
int fn_8023F9F4(const char*);
void* fn_8023F1A4(const char*, int);
void* fn_80006E1C();
void fn_80009214(void*, const char*, int);
void fn_80009274(void*, const char*, int);
void fn_800092D4(void*, const char*, int);
void fn_80009150(void*, const char*, int);
void fn_80006F20(void*);
void fn_80009C7C(void*, int);
void fn_80008F54(void*, int);
void fn_80008F5C(void*, int);
void fn_800C0F44(EffL*, int);
void fn_800C1064(EffL*, int);
void fn_80008F64(void*, int);
void* fn_80007F3C(void*);
#if TARGET_PC
FE10_PROTO void fn_80014E24(void*, const char*, void*, p32arg);
#else
void fn_80014E24(void*, const char*, void*, int);
#endif
void fn_800B053C(void*, void*);
void fn_800B0554(void*, void*);
#pragma use_lmw_stmw on
void fn_800BF148(EffL* e) {
    char buf[0x40];
    if (e->m38 == NULL) return;
    if (e->m34 != NULL) {
        fn_800829CC(e, lbl_803825A8);
        fn_80011CBC(fn_80006EE0, e->m34);
        if (e->m30 != NULL) fn_80011CBC(fn_8023F1A8, e->m30);
        e->m34 = NULL;
        e->m30 = NULL;
        e->m46 = 0;
    }
    if (e->m38->m8 == NULL) return;
    fn_80290DDC(buf, lbl_80365B64, e->m38->m8, e->m38->m8);
    if (fn_8023F9F4(fn_8017F37C(buf, S(0x80365B6E), 0)) == 0x40000) return;
    e->m30 = fn_8023F1A4(fn_8017F37C(buf, S(0x80365B6E), 0), e->m46 & 0x80 ? 0x20 : 0x40);
    e->m34 = fn_80006E1C();
    fn_80009214(e->m34, fn_8017F37C(buf, S(0x80365B73), 0), e->m46 & 0x80 ? 0x20 : 0x40);
    fn_80009274(e->m34, fn_8017F37C(buf, S(0x80365B77), 0), e->m46 & 0x80 ? 0x20 : 0x40);
    fn_800092D4(e->m34, fn_8017F37C(buf, S(0x80365B7A), 0), e->m46 & 0x80 ? 0x20 : 0x40);
    if (fn_8023F9F4(fn_8017F37C(buf, S(0x80365B7F), 0)) != 0x40000) {
        fn_80009150(e->m34, fn_8017F37C(buf, S(0x80365B7F), 0), e->m46 & 0x80 ? 0x20 : 0x40);
    }
    fn_80006F20(e->m34);
    fn_80009C7C(e->m34, 0x100);
    fn_80008F54(e->m34, 0x87);
    fn_80008F5C(e->m34, 2);
    if (e->m38 != NULL) {
        if (e->m38->m21 & 2) {
            e->m46 &= ~0x10;
            fn_800C1064(e, 0);
            fn_800829CC(e, lbl_803825A8);
        } else {
            e->m46 |= 0x10;
            fn_800C0F44(e, -1);
        }
    }
    fn_80008F64(e->m34, 0xF0);
    fn_80014E24(fn_80007F3C(e->m34), 0, fn_800B053C, 2);
    fn_80014E24(fn_80007F3C(e->m34), 0, fn_800B0554, 4);
}
}
