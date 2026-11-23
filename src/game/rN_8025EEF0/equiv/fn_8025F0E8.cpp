/* functionally equal (regs). Helpers from ../fn_8025EEF0.cpp, body from wip/fn_8025F068.cpp */
/* Sound-player glue, sitting right after the game's
 * sound code. The classes use NW4R's snd headers (LinkList.h, SoundArchivePlayer.h
 * assert strings) but are compiled with the game's compiler. */
#include "game/rN_8025EEF0/types.h"

extern "C" {

void fn_802BC2C4(void* p, int del);
void fn_80079210(void* p);
void fn_802AF300(void* p, int del);
int fn_802AA470(void* p, int v);
int fn_802AA410(void* p, s16* out);
void fn_8029C20C(const char* file, int line, const char* msg, ...);
int fn_802AD3B0(void* p, int a);
int fn_802B00B0(void* p, int a, int b, int c, int d);
void* fn_8031447C(void* p);
void fn_8031F324(void* q);

extern u8 lbl_80391888[];
extern u8 lbl_80393CD8[];
extern char lbl_803918F4[];
extern char lbl_803918C4[];
extern const f64 lbl_804D0050;

struct Vt { virtual void v8(); virtual void vC(); virtual void v10(); };





struct Cls1 { void* vt; Vt* obj; };









































#pragma push
#pragma auto_inline off


#pragma pop




/* inlined NW4R_ASSERT(mSoundArchive) from SoundArchivePlayer.h */
#define ASSERT_ARCHIVE(p, line) do { if ((p) == 0) fn_8029C20C(lbl_803918F4, line, lbl_803918C4); } while (0)

struct SndHolder { u8 pad[0x10]; void* archive; };

#pragma push
#pragma auto_inline off


#pragma pop
class VDtor {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
};
struct VtPtr { u8* vt; };



extern u8 lbl_80393CB0[];


struct Fx5 { int a; int b; f32 x; f32 y; f32 z; };








static inline int get48(u8* p) { return *(s8*)(p + 0x48); }

struct Fader {
    u8 pad[0x10];
    int t;     /* 0x10 */
    int dur;   /* 0x14 */
    f32 cur;   /* 0x18 */
    f32 from;  /* 0x1C */
    f32 to;    /* 0x20 */
};

f32 fn_8025F0E8(Fader* f) {
    int dur = f->dur;
    int t = f->t;
    if (t < dur) {
        f->t = t + 1;
        f->cur = (f->to - f->from) * ((f32)t / (f32)dur) + f->from;
    } else {
        f->cur = f->to;
    }
    return f->cur;
}


}
