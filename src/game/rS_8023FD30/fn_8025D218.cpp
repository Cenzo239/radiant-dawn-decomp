#include "game/rS_8023FD30/audio.h"

/* Methods of the four sound player classes. Their shared fields: +0x49 a countdown,
   +0x5C the low-level handle. */
class PlayerBase {
public:
    virtual void v08();
    virtual void stop();     /* +0x0C */
    virtual void v10();
    virtual void shutdown(); /* +0x14 */
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual int remaining(); /* +0x98 */
    u8 pad04[0x49 - 4];
    s8 countdown;            /* +0x49 */
    u8 pad4A[0x5C - 0x4A];
    void* handle;            /* +0x5C */
};

struct HandleLock {
    void* h;
    u8 pad[4];
};

typedef void (*PlayerCb)(PlayerBase*);

extern "C" {

void fn_802AA628(HandleLock*, void*);
void fn_802AA734(HandleLock*);
int fn_802AA444(void*, s32, s32);
int fn_802AA3C0(void*, s32, s32);
#if TARGET_PC
FE10_PROTO int fn_8025F22C(p32arg, s32);
FE10_PROTO int fn_8025F234(p32arg, p32arg);
#else
int fn_8025F22C(s32, s32);
int fn_8025F234(s32, s32);
#endif
void fn_802A22B4(void*, s32);
void fn_802A1E30(void*);
void fn_802A1E48(void*, s32);
void fn_802A2030(void*, s32, s32);
extern u8 lbl_804CBFF0;
extern PlayerCb lbl_804CBFF4;
extern char lbl_803916C0[];
extern char lbl_80391540[];
extern char lbl_803913C0[];
extern char lbl_80391240[];
extern char lbl_80391780[];
extern void* lbl_804CBFDC;
#if TARGET_PC
FE10_PROTO void fn_8030E3F4(ptr32<const void>, void*);
#else
void fn_8030E3F4(void*, void*);
#endif
void fn_802B15D8(void*);
void fn_802ABA74(void*, s32);

int fn_8025D218(PlayerBase* self, s32 a, s32 b) {
    SndLock l(lbl_8042E798);
    HandleLock h;
    fn_802AA628(&h, &self->handle);
    int r = fn_8025F22C(a, b);
    fn_802AA734(&h);
    return r;
}

BOOL fn_8025D2CC(PlayerBase* self, s32 a, s32 b) {
    SndLock l(lbl_8042E798);
    HandleLock h;
    fn_802AA628(&h, &self->handle);
    BOOL r = FALSE;
    if (h.h != 0 && fn_802AA444(h.h, a, b) != 0) {
        r = TRUE;
    }
    fn_802AA734(&h);
    return r;
}

int fn_8025D398(PlayerBase* self, s32 a, s32 b) {
    SndLock l(lbl_8042E798);
    HandleLock h;
    fn_802AA628(&h, &self->handle);
    int r = fn_8025F234(a, b);
    fn_802AA734(&h);
    return r;
}

BOOL fn_8025D44C(PlayerBase* self, s32 a, s32 b) {
    SndLock l(lbl_8042E798);
    HandleLock h;
    fn_802AA628(&h, &self->handle);
    BOOL r = FALSE;
    if (h.h != 0 && fn_802AA3C0(h.h, a, b) != 0) {
        r = TRUE;
    }
    fn_802AA734(&h);
    return r;
}

#define PLAYER_METHODS(update, resume, step, reset, volptr) \
    void fn_##update(PlayerBase* self, s32 ms) { \
        SndLock l(lbl_8042E798); \
        if (self->handle != 0) { \
            fn_802A22B4(self->handle, (f32)ms / 16.666666f); \
        } \
        if (self->remaining() <= 0 && lbl_804CBFF0 == 0) { \
            { \
                SndMutex& m = lbl_8042E798; \
                SndLock l2(m); \
                PlayerCb cb; \
                m.lock(); \
                cb = lbl_804CBFF4; \
                m.unlock(); \
                if (cb != 0) { \
                    m.lock(); \
                    cb = lbl_804CBFF4; \
                    m.unlock(); \
                    cb(self); \
                } \
            } \
            if (self->handle != 0) { \
                fn_802A1E30(self->handle); \
            } \
        } \
    } \
    void fn_##resume(PlayerBase* self, s32 ms) { \
        SndLock l(lbl_8042E798); \
        if (self->handle != 0) { \
            fn_802A1E48(self->handle, (f32)ms / 16.666666f); \
        } \
    } \
    void fn_##step(PlayerBase* self, s32 ms) { \
        SndLock l(lbl_8042E798); \
        if (self->countdown == 0 || --self->countdown > 0) { \
            return; \
        } \
        if (self->handle != 0) { \
            fn_802A2030(self->handle, 0, (f32)ms / 16.666666f); \
        } \
    } \
    void fn_##reset(PlayerBase* self, s32 ms) { \
        SndLock l(lbl_8042E798); \
        self->countdown = 0; \
        if (self->handle != 0) { \
            fn_802A2030(self->handle, 0, (f32)ms / 16.666666f); \
        } \
    } \
    void* fn_##volptr(PlayerBase* self) { \
        void* r; \
        SndMutex& m = lbl_8042E798; \
        m.lock(); \
        if (self->handle != 0) { \
            r = (u8*)self->handle + 0x30; \
        } else { \
            r = 0; \
        } \
        m.unlock(); \
        return r; \
    }

PLAYER_METHODS(8025D520, 8025D6DC, 8025D79C, 8025D8A0, 8025D96C)
PLAYER_METHODS(8025D9F0, 8025DBAC, 8025DC6C, 8025DD70, 8025DE3C)
PLAYER_METHODS(8025DEC0, 8025E07C, 8025E13C, 8025E240, 8025E30C)
PLAYER_METHODS(8025E390, 8025E54C, 8025E60C, 8025E710, 8025E7DC)

#define PLAYER_DTOR2(addr, vtbl) \
    PlayerBase* fn_##addr(PlayerBase* self, s32 del) { \
        if (self != 0) { \
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
            } \
            if (del > 0) { \
                SndLock l(lbl_8042E798); \
                fn_8030E3F4(lbl_804CBFDC, self); \
            } \
        } \
        return self; \
    }

PLAYER_DTOR2(8025E858, lbl_803916C0)
PLAYER_DTOR2(8025E938, lbl_80391540)
PLAYER_DTOR2(8025EA18, lbl_803913C0)

PlayerBase* fn_8025EAF8(PlayerBase* self, s32 del) {
    if (self != 0) {
        fn_802ABA74((u8*)self + 0x60, -1);
        if (self != 0) {
            *(void**)self = lbl_80391240;
            self->stop();
            if ((u8*)self + 0x5c != 0) {
                fn_802B15D8((u8*)self + 0x5c);
            }
            if (self != 0) {
                *(void**)self = lbl_80391780;
                self->shutdown();
            }
        }
        if (del > 0) {
            SndLock l(lbl_8042E798);
            fn_8030E3F4(lbl_804CBFDC, self);
        }
    }
    return self;
}

}
