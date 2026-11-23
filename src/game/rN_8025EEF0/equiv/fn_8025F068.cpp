/* r19: self-contained (helpers of fn_8025EEF0.cpp + wip fragment); `sched` level. */
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
void* fn_8025EEF0(u8* self, int del);

void* fn_8025EF50(void* self, int del);


struct Cls1 { void* vt; Vt* obj; };
void* fn_8025EF90(Cls1* self, int del);

void fn_8025F000(u8* p);

u64 fn_8025F00C(u8* p);

void fn_8025F01C(u8* p, f32 v);

void fn_8025F024(u8* p, f32 v);

void fn_8025F02C(u8* p, f32 v);

int fn_8025F034(void);

int fn_8025F03C(void);

int fn_8025F044(void);

int fn_8025F04C(void);

int fn_8025F054(u8* p);

int fn_8025F060(u8* p);

f32 fn_8025F098(u8* p);

f32 fn_8025F0A0(u8* p);

f32 fn_8025F0A8(u8* p);

f32 fn_8025F0B0(u8* p);

f32 fn_8025F0B8(u8* p);

f32 fn_8025F0C0(u8* p);

f32 fn_8025F0C8(u8* p);

f32 fn_8025F0D0(u8* p);

f32 fn_8025F0D8(u8* p);

f32 fn_8025F0E0(u8* p);

void fn_8025F164(u8* p, f32 v);

void fn_8025F16C(u8* p, f32 v);

void fn_8025F174(u8* p, f32 v);

void fn_8025F17C(u8* p, f32 v);

void fn_8025F184(u8* p, f32 v);

void fn_8025F18C(u8* p, f32 v);

void fn_8025F194(u8* p, f32 v);

void fn_8025F19C(u8* p, f32 v);

void fn_8025F1A4(u8* p, f32 v);

f32 fn_8025F1AC(u8* p);

f32 fn_8025F1B4(u8* p);

f32 fn_8025F1BC(u8* p);

void* fn_8025F1C4(void);


#pragma push
#pragma auto_inline off

void* fn_8025F1D4(void* self, int del);


#pragma pop

int fn_8025F22C(void* p, s16 v);

int fn_8025F234(void* p, s16* out);



/* inlined NW4R_ASSERT(mSoundArchive) from SoundArchivePlayer.h */
#define ASSERT_ARCHIVE(p, line) do { if ((p) == 0) fn_8029C20C(lbl_803918F4, line, lbl_803918C4); } while (0)

struct SndHolder { u8 pad[0x10]; void* archive; };

#pragma push
#pragma auto_inline off

int fn_8025F238(SndHolder* self, int a);


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
void* fn_8025F2A0(VDtor* self, int del);


extern u8 lbl_80393CB0[];
void* fn_8025F31C(VDtor* self, int del);


struct Fx5 { int a; int b; f32 x; f32 y; f32 z; };
void fn_8025F398(Fx5* p);

int fn_8025F3B8(u8* p, int a);

int fn_8025F3C0(u8* p, int a, int b, int c, int d);

void* fn_8025F3C8(u8* p, int del);


}

/* ---- from rN_8025EEF0/wip/fn_8025F068.cpp ---- */
extern "C" {
/* fn_8025F068: 4 words, lfd scheduled too early. fn_8025F0E8: 11 words, dur should be r4 and 0x4330 r5. */
static inline int get48(u8* p) { return *(s8*)(p + 0x48); }
f32 fn_8025F068(u8* p) { return get48(p); }
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
