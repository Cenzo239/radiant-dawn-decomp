#include "game/rF_8017F400/types.h"

extern "C" {

typedef struct TrackOwner {
    u8 pad[0x30];
    Track* tracks; /* 0x30, new Track[8] */
} TrackOwner;

extern u32 lbl_804CB700;
extern void* fn_800791B0(u32 size);  /* operator new[] */
extern void fn_80079474(void* p);    /* operator delete[] */
extern void* fn_8028BE18(void* mem, void* ctor, void* dtor, u32 size, u32 n); /* __construct_new_array */
extern void fn_8017FDC8(Track* t);   /* Track ctor */
extern void fn_801805E0(Track* t);
extern void fn_8017FE30(void* arg);
extern void fn_800106AC(int a, void (*cb)(void*), void* arg);

void fn_80180C90(Track* t, u8 v)
{
    t->unk4 = v;
}

void fn_80180C98(Track* t, const GXColor& c)
{
    t->color = c;
}

void fn_80180CBC(TrackOwner* o)
{
    o->tracks = (Track*)fn_8028BE18(fn_800791B0(sizeof(Track) * 8 + 0x10), (void*)fn_8017FDC8, NULL, sizeof(Track), 8);
}

void fn_80180D0C(TrackOwner* o)
{
    if (o->tracks != NULL) {
        fn_80079474((u8*)o->tracks - 0x10);
    }
}

void fn_80180D24(TrackOwner* o)
{
    int i;
    if (lbl_804CB700 & 0x8001) {
        for (i = 0; i < 8; i++) {
            Track* t = &o->tracks[i];
            t->unk10 = t->unk14 = t->unk18;
        }
    }
    for (i = 0; i < 8; i++) {
        fn_801805E0(&o->tracks[i]);
        fn_800106AC(3, fn_8017FE30, &o->tracks[i]);
    }
}

}
