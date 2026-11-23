/* fn_80044284: set the default map sound levels unless a flag is set (context copied from rT_80026898/fn_80044284.cpp; flagGet takes the name as const char* const&). */
#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
typedef struct FlagTable {
    u8 pad0[0x11];
    u8 b11;             /* 0x11 */
    u8 pad12[0x9a - 0x12];
    s8 s9a;
    s8 s9b;
    u8 pad9c[0x144 - 0x9c];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;
extern "C" {
extern FlagTable lbl_803CAB38;
extern char lbl_80361684[0xbc];
extern char lbl_80379FA8[];
extern char lbl_80379F58[];
extern char lbl_8037A1B0[];
extern char lbl_8037A1E8[];
extern u8 lbl_803CB770[];
extern u8 lbl_803EC898[];
extern void* lbl_804CA5B8;
u32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
void fn_802512C4(f32);
void fn_80250D64(int, f32, f32);
void fn_80250E38(int, f32, f32);
void fn_8025095C(f32, f32);
void fn_80250A08(f32, f32);
void fn_80114D00(void*);
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int);
#endif
void* fn_80083B84(void*);
void fn_80083DC4(void*, u8);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_800CD4A4(int);
void fn_80062380(void*, void*);
void fn_8024BCAC(void);
void fn_800620A8(void*, f32, f32);
void fn_8012FF30(void);
void fn_80062454(void*);
void fn_8012D620(void);
void fn_8012D908(void);
u8* fn_8006074C(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_800680D0(void*);
#else
void* fn_800680D0(void*);
#endif
void fn_80257340(void*, int);
void fn_800785FC(const char*, int);
void fn_80092A00(u8);
int fn_8023F9F4(const char*);
void fn_80075FB4(const char*, int);
void fn_8023F1A4(const char*, int);
void fn_800F35AC(void);
int fn_8007857C(void);
void fn_80078C2C(const char*);
void fn_8012D58C(void);
void fn_8012FA44(void);
int fn_80257628(void*);
void fn_80320978(s64);
void fn_80062598(void*, void*);
char* strcpy(char*, const char*);
void fn_80291110(char*, const char*);
int fn_80060960(void*);
int fn_80060988(void*);
int fn_800609B0(void*);
void fn_8009E554(char*, void*);
void fn_8012D78C(void);
void* fn_800811E4(void*, void*);
void fn_80103D50(Unit*, int);
Slot* fn_8012759C(Unit*);
#if TARGET_PC
FE10_PROTO char * fn_80110F08(Slot*);
FE10_PROTO void fn_800310E4(p32arg, int, int, int);
#else
int fn_80110F08(Slot*);
void fn_800310E4(int, int, int, int);
#endif
void* fn_80066130(void*, int, int, int);
Slot* fn_80066D18(void*);
Slot* fn_80044FD0(CmdState*);
void fn_8011196C(Unit*, void*, void*);
u8 fn_8012408C(Unit*);
void fn_8017F44C(void*, int, int);
int fn_8011B77C(void*, void*);
Slot* fn_80127648(Unit*);
u32* fn_801116B8(Slot*);
int fn_80109348(void*);
void fn_80126EB0(Unit*, int, int);
void fn_800F39DC(Unit*);

static inline int flagFind(FlagTable* t, const char* name) {
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}
static inline bool flagTestBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return t->bits[i >> 3] & (1 << (i & 7));
}
static inline bool flagGetBit(FlagTable* t, int i) {
    if (i < 0 || i >= 0x80) {
        return false;
    }
    return flagTestBit(t, i);
}
static inline bool flagGet(FlagTable* t, const char* const& name) {
    if (name[0] == 0) {
        return false;
    }
    return flagGetBit(t, flagFind(t, name));
}




struct Scripts { char a[0x34]; char b[0x1c]; char c[4]; };


static inline void scale(FlagTable* t) {
    fn_800620A8(t, t->s9a, t->s9b);
}





















#pragma use_lmw_stmw on
void fn_80044284(void) {
    if (!flagGet(&lbl_803CAB38, lbl_80361684 + 0x4d)) {
        fn_802512C4(500.0f);
        fn_80250D64(0, 1.0f, 500.0f);
        fn_80250E38(0, 1.0f, 500.0f);
        fn_8025095C(0.0f, 500.0f);
        fn_80250A08(0.0f, 500.0f);
        fn_80250D64(6, 1.0f, 250.0f);
        fn_80250E38(6, 1.0f, 250.0f);
    }
}

}
