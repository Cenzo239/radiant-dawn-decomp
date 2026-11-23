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

void* fn_8025EEF0(u8* self, int del) {
    if (self != 0) {
        void* m = self + 0xC;
        if (m != 0) {
            fn_802BC2C4(m, 0);
        }
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

void* fn_8025EF50(void* self, int del) {
    if (self != 0) {
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

struct Cls1 { void* vt; Vt* obj; };
void* fn_8025EF90(Cls1* self, int del) {
    if (self != 0) {
        self->vt = lbl_80391888;
        self->obj->v10();
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

void fn_8025F000(u8* p) { *(int*)(p + 0xC) = 0; }

u64 fn_8025F00C(u8* p) { return *(u64*)(p + 0x50); }

void fn_8025F01C(u8* p, f32 v) { *(f32*)(p + 0xE0) = v; }
void fn_8025F024(u8* p, f32 v) { *(f32*)(p + 0xE4) = v; }
void fn_8025F02C(u8* p, f32 v) { *(f32*)(p + 0xE8) = v; }
int fn_8025F034(void) { return 0; }
int fn_8025F03C(void) { return 0; }
int fn_8025F044(void) { return 0; }
int fn_8025F04C(void) { return 0; }
int fn_8025F054(u8* p) { return *(s8*)(p + 0x49); }
int fn_8025F060(u8* p) { return *(int*)(p + 0x58); }
f32 fn_8025F098(u8* p) { return *(f32*)(p + 0x44); }
f32 fn_8025F0A0(u8* p) { return *(f32*)(p + 0x40); }
f32 fn_8025F0A8(u8* p) { return *(f32*)(p + 0x3C); }
f32 fn_8025F0B0(u8* p) { return *(f32*)(p + 0x38); }
f32 fn_8025F0B8(u8* p) { return *(f32*)(p + 0x34); }
f32 fn_8025F0C0(u8* p) { return *(f32*)(p + 0x30); }
f32 fn_8025F0C8(u8* p) { return *(f32*)(p + 0x2C); }
f32 fn_8025F0D0(u8* p) { return *(f32*)(p + 0x28); }
f32 fn_8025F0D8(u8* p) { return *(f32*)(p + 0x24); }
f32 fn_8025F0E0(u8* p) { return *(f32*)(p + 0x18); }

void fn_8025F164(u8* p, f32 v) { *(f32*)(p + 0x44) = v; }
void fn_8025F16C(u8* p, f32 v) { *(f32*)(p + 0x40) = v; }
void fn_8025F174(u8* p, f32 v) { *(f32*)(p + 0x3C) = v; }
void fn_8025F17C(u8* p, f32 v) { *(f32*)(p + 0x38) = v; }
void fn_8025F184(u8* p, f32 v) { *(f32*)(p + 0x34) = v; }
void fn_8025F18C(u8* p, f32 v) { *(f32*)(p + 0x30) = v; }
void fn_8025F194(u8* p, f32 v) { *(f32*)(p + 0x2C) = v; }
void fn_8025F19C(u8* p, f32 v) { *(f32*)(p + 0x28) = v; }
void fn_8025F1A4(u8* p, f32 v) { *(f32*)(p + 0x24) = v; }
f32 fn_8025F1AC(u8* p) { return *(f32*)(p + 0xE0); }
f32 fn_8025F1B4(u8* p) { return *(f32*)(p + 0xE4); }
f32 fn_8025F1BC(u8* p) { return *(f32*)(p + 0xE8); }

void* fn_8025F1C4(void) { char buf[0x18]; return buf; }

#pragma push
#pragma auto_inline off
void* fn_8025F1D4(void* self, int del) {
    if (self != 0) {
        fn_802AF300(self, 0);
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

#pragma pop
int fn_8025F22C(void* p, s16 v) { return fn_802AA470(p, v); }
int fn_8025F234(void* p, s16* out) { return fn_802AA410(p, out); }


/* inlined NW4R_ASSERT(mSoundArchive) from SoundArchivePlayer.h */
#define ASSERT_ARCHIVE(p, line) do { if ((p) == 0) fn_8029C20C(lbl_803918F4, line, lbl_803918C4); } while (0)

struct SndHolder { u8 pad[0x10]; void* archive; };

#pragma push
#pragma auto_inline off
int fn_8025F238(SndHolder* self, int a) {
    ASSERT_ARCHIVE(self->archive, 0xB4);
    return fn_802AD3B0(self->archive, a);
}

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

void* fn_8025F2A0(VDtor* self, int del) {
    if (self != 0) {
        ((VtPtr*)self)->vt = lbl_80393CD8;
        self->v10();
        self->v20();
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

extern u8 lbl_80393CB0[];
void* fn_8025F31C(VDtor* self, int del) {
    if (self != 0) {
        ((VtPtr*)self)->vt = lbl_80393CB0;
        self->v10();
        self->v20();
        if (del > 0) {
            fn_80079210(self);
        }
    }
    return self;
}

struct Fx5 { int a; int b; f32 x; f32 y; f32 z; };
void fn_8025F398(Fx5* p) {
    p->a = 0;
    p->b = 0;
    p->x = 0.0f;
    p->y = 0.0f;
    p->z = 0.0f;
}

int fn_8025F3B8(u8* p, int a) { return fn_8025F238((SndHolder*)(p - 0xC), a); }
int fn_8025F3C0(u8* p, int a, int b, int c, int d) { return fn_802B00B0(p - 0xC, a, b, c, d); }
void* fn_8025F3C8(u8* p, int del) { return fn_8025F1D4(p - 0xC, del); }

}
