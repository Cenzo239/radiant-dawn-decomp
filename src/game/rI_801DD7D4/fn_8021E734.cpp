#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
int fn_800CB0FC(f32, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801E2204(void*, void*, void*);
void fn_801E2104(void* p, void* arg);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void (*)(void*, void*), void*);
#endif
void fn_8007E7B4(void);
const char* fn_8011A100(void*);
char* strcpy(char*, const char*);
unsigned long strlen(const char*);
char* fn_8029135C(char*, const char*);
extern char lbl_80371B80[];
struct XY { s16 x, y; };
struct OE { void* vt; int rc; s16 id; s16 pa; u8 pc[6]; s16 a12, a14, a16, a18; u8 p1a[4]; s16 a1e, a20; u8 p22[0x16]; u32 flags; u8 p3c[4]; void* a40; XY a44; XY a48; };
static inline void setR(OE* o, s16 a, s16 b, s16 c, s16 d) { o->a44.x = a; o->a44.y = b; o->a48.x = c; o->a48.y = d; }
void fn_8021E734(OE* o) {
    /*P*/
    char* p;
    const char* src;
    int ty;
    char* buf;
    int y;
/*E*/
    ((VO0N*)o)->v18();
    y = (s16)(o->a1e - 6);
    ty = (0x1a - fn_800CB0FC(1.0f, -1)) >> 1;
    setR(o, y - 4, 0x31, (s16)(o->a16 - o->a12) - o->a1e + 10, (s16)(o->a18 - o->a14) - o->a20 - 4);
    fn_801E2204(o, &o->a44, &o->a44);
    fn_801E2204(o, &o->a48, &o->a48);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->a44);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    src = fn_8011A100(o->a40);
    buf = (char*)__alloca(strlen(src) + 1);
    strcpy(buf, src);
    p = fn_8029135C(buf, lbl_80371B80 + 0xae);
    ty += 0x31;
    while (p != NULL) {
        fn_800CB278(y, (s16)ty, 1, p);
        ty += 0x1a;
        p = fn_8029135C(NULL, lbl_80371B80 + 0xae);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
}
