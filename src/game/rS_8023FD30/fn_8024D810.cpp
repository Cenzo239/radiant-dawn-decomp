#include "game/rS_8023FD30/audio.h"

extern "C" {

int fn_8031F6BC(void*);
void fn_8031FF98(void*);
void fn_802B24A8(void);
void fn_802B15D8(void*);
void* fn_8029C7D8(void);
void fn_8029CF8C(void*, s32);
int fn_8029D084(void*);
void fn_8029D870(void*);
void fn_802B2524(void);
extern u8 lbl_804CBFF0;
#if TARGET_PC
FE10_PROTO void fn_8030E3F4(ptr32<const void>, void*);
#else
void fn_8030E3F4(void*, void*);
#endif
extern void* lbl_804CBFDC;
extern char lbl_803916C0[];
extern char lbl_80391540[];
extern char lbl_803913C0[];
extern char lbl_80391240[];
extern char lbl_80391780[];

class SndBase {
public:
    virtual void v08();
    virtual void stop();     /* +0x0C */
    virtual void v10();
    virtual void shutdown(); /* +0x14 */
};

/* Destructors of the four sound player classes. The vtable is stored by hand. */
#define PLAYER_DTOR(addr, vtbl) \
    SndBase* fn_##addr(SndBase* self, s32 del) { \
        if (self != 0) { \
            *(void**)self = vtbl; \
            self->stop(); \
            if ((u8*)self + 0x5c != 0) { \
                fn_802B15D8((u8*)self + 0x5c); \
            } \
            if (self != 0) { \
                *(void**)self = lbl_80391780; \
                self->shutdown(); \
            } \
            if (del > 0) { \
                SndLock l(lbl_8042E798); \
                fn_8030E3F4(lbl_804CBFDC, self); \
            } \
        } \
        return self; \
    }

void fn_8024D810(void) {
    SndLock l(lbl_8042E798);
    if (fn_8031F6BC(lbl_8042F1B0) == 0) {
        fn_8031FF98(lbl_8042F1B0);
    }
    fn_802B24A8();
}

void fn_8024D974(u8* p) {
    SndLock l(lbl_8042E798);
    fn_802B15D8(p + 0x5c);
}

PLAYER_DTOR(8024D898, lbl_803916C0)
PLAYER_DTOR(8024D9F0, lbl_80391540)
void fn_8024DACC(u8* p) {
    SndLock l(lbl_8042E798);
    fn_802B15D8(p + 0x5c);
}
PLAYER_DTOR(8024DB48, lbl_803913C0)
void fn_8024DC24(u8* p) {
    SndLock l(lbl_8042E798);
    fn_802B15D8(p + 0x5c);
}
PLAYER_DTOR(8024DCA0, lbl_80391240)
void fn_8024DD7C(u8* p) {
    SndLock l(lbl_8042E798);
    fn_802B15D8(p + 0x5c);
}

void fn_8024DDF8(s32 a) {
    SndLock l(lbl_8042E798);
    fn_8029CF8C(fn_8029C7D8(), a);
}

int fn_8024DE78(void) {
    SndLock l(lbl_8042E798);
    return fn_8029D084(fn_8029C7D8());
}

void fn_8024F2F4(void) {
    SndLock l(lbl_8042E798);
    fn_8029D870(fn_8029C7D8());
    lbl_804CBFF0 = 1;
}

void fn_8024F364(void) {
    SndLock l(lbl_8042E798);
    fn_802B2524();
}

}
