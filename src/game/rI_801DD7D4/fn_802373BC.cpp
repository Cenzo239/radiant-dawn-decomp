/* THP player control, from the DolphinSDK THPPlayer sample shape. Names in comments are guesses. */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off

extern "C" {

void fn_80303CB4(void);
#if TARGET_PC
FE10_PROTO void fn_80238170(ptr32<const void>);
#else
void fn_80238170(void*);
#endif
extern int lbl_804CBF50;
extern u8 lbl_80420680[];

static inline void* popUsed(void) {
    void* msg;
    if (fn_8031D34C(lbl_80420680, &msg, 0) == 1) {
        return msg;
    }
    return NULL;
}
/* THPPlayerDrawDone */
void fn_802373BC(void) {
    fn_80303CB4();
    if (lbl_804CBF50 != 0) {
        for (;;) {
            void* t = popUsed();
            if (t == NULL) break;
            fn_80238170(t);
        }
    }
}

#if TARGET_PC
FE10_PROTO ptr32<THPAudioBuf> fn_802359BC(int);
#else
THPAudioBuf* fn_802359BC(int);
#endif
void fn_802359A8(THPAudioBuf*);
extern u16 lbl_80390B58[];
/* MixAudio */
void fn_80237590(s16* dst, s16* src, u32 n) {
    u32 req2;
    s16* d2;
    u32 req;
    s16* d;
    s16* s;
    u8 mono = lbl_80420420.f8 == 0;
    u32 num, i;
    s16* cur;
    int mix;
    u16 vol;
    if (src != NULL) {
        if (lbl_80420420.a0 != 0 && lbl_80420420.a5 == 2 && lbl_80420420.a7 != 0) {
            req = n;
            d = dst;
            s = src;
            for (;;) {
                if (lbl_80420420.buf == NULL) {
                    if ((lbl_80420420.buf = fn_802359BC(0)) == NULL) {
                        memcpy(d, s, req << 2);
                        break;
                    }
                    lbl_80420420.f4++;
                }
                if (lbl_80420420.buf->valid != 0) {
                    num = lbl_80420420.buf->valid;
                    if (num >= req) num = req;
                    cur = lbl_80420420.buf->cur;
                    for (i = 0; i < num; i++) {
                        if (lbl_80420420.e8 != 0) {
                            lbl_80420420.e8--;
                            lbl_80420420.dc += lbl_80420420.e4;
                        } else {
                            lbl_80420420.dc = lbl_80420420.e0;
                        }
                        vol = lbl_80390B58[(int)lbl_80420420.dc];
                        mix = s[0] + ((vol * cur[0]) >> 15);
                        if (mix < -0x8000) mix = -0x8000;
                        if (mix > 0x7fff) mix = 0x7fff;
                        d[0] = mix;
                        mix = s[1] + ((vol * cur[1]) >> 15);
                        if (mix < -0x8000) mix = -0x8000;
                        if (mix > 0x7fff) mix = 0x7fff;
                        d[1] = mix;
                        d += 2;
                        s += 2;
                        cur += 2;
                        if (mono) {
                            /* volatile only stops the load being hoisted out of the loop; not likely original */
                            vol = *(volatile u16*)&lbl_80390B58[100];
                            mix = (vol * (d[-1] + d[-2])) >> 15;
                            if (mix < -0x8000) mix = -0x8000;
                            if (mix > 0x7fff) mix = 0x7fff;
                            d[-2] = mix;
                            d[-1] = mix;
                        }
                    }
                    req -= num;
                    lbl_80420420.buf->valid -= num;
                    lbl_80420420.buf->cur = cur;
                    if (lbl_80420420.buf->valid == 0) {
                        fn_802359A8(lbl_80420420.buf);
                        lbl_80420420.buf = NULL;
                    }
                    if (req != 0) continue;
                    break;
                }
            }
        }
        else memcpy(dst, src, n << 2);
    } else {
        if (lbl_80420420.a0 != 0 && lbl_80420420.a5 == 2 && lbl_80420420.a7 != 0) {
            req2 = n;
            d2 = dst;
            for (;;) {
                if (lbl_80420420.buf == NULL) {
                    if ((lbl_80420420.buf = fn_802359BC(0)) == NULL) {
                        memset(d2, 0, req2 << 2);
                        break;
                    }
                    lbl_80420420.f4++;
                }
                if (lbl_80420420.buf->valid != 0) {
                    num = lbl_80420420.buf->valid;
                    if (num >= req2) num = req2;
                    cur = lbl_80420420.buf->cur;
                    for (i = 0; i < num; i++) {
                        if (lbl_80420420.e8 != 0) {
                            lbl_80420420.e8--;
                            lbl_80420420.dc += lbl_80420420.e4;
                        } else {
                            lbl_80420420.dc = lbl_80420420.e0;
                        }
                        vol = lbl_80390B58[(int)lbl_80420420.dc];
                        mix = (vol * cur[0]) >> 15;
                        if (mix < -0x8000) mix = -0x8000;
                        if (mix > 0x7fff) mix = 0x7fff;
                        d2[0] = mix;
                        mix = (vol * cur[1]) >> 15;
                        if (mix < -0x8000) mix = -0x8000;
                        if (mix > 0x7fff) mix = 0x7fff;
                        d2[1] = mix;
                        d2 += 2;
                        cur += 2;
                    }
                    req2 -= num;
                    lbl_80420420.buf->valid -= num;
                    lbl_80420420.buf->cur = cur;
                    if (lbl_80420420.buf->valid == 0) {
                        fn_802359A8(lbl_80420420.buf);
                        lbl_80420420.buf = NULL;
                    }
                    if (req2 != 0) continue;
                    break;
                }
            }
        }
        else memset(dst, 0, n << 2);
    }
}

int fn_802BCE64(void);
/* THPPlayerSetVolume */
int fn_80237958(int vol, int time) {
    int s;
    int old;
    if (lbl_80420420.a0 != 0 && lbl_80420420.a7 != 0) {
        if (fn_802BCE64() == 0) {
            s = 0x20;
        } else {
            s = 0x30;
        }
        if (vol > 0x7f) vol = 0x7f;
        if (vol < 0) vol = 0;
        if (time > 60000) time = 60000;
        if (time < 0) time = 0;
        old = OSDisableInterrupts();
        lbl_80420420.e0 = vol;
        if (time != 0) {
            lbl_80420420.e8 = s * time;
            lbl_80420420.e4 = (lbl_80420420.e0 - lbl_80420420.dc) / lbl_80420420.e8;
        } else {
            lbl_80420420.e8 = 0;
            lbl_80420420.dc = lbl_80420420.e0;
        }
        OSRestoreInterrupts(old);
        return 1;
    }
    return 0;
}
int fn_80236CDC(void) {
    if (lbl_80420420.a0 != 0 && (lbl_80420420.a4 == 1 || lbl_80420420.a4 == 4)) {
        lbl_80420420.a4 = 2;
        lbl_80420420.d0 = 0;
        lbl_80420420.d4 = 0;
        lbl_80420420.c8 = -1;
        return 1;
    }
    return 0;
}
#define AL(x) (((x) + 0x1f) & ~0x1f)
u32 fn_80236680(void) {
    u32 sz;
    u32 y;
    if (lbl_80420420.a0 != 0) {
        if (lbl_80420420.b0 != 0) {
            sz = AL(lbl_80420420.a58);
        } else {
            sz = AL(lbl_80420420.a44) * 10;
        }
        y = lbl_80420420.a80 * lbl_80420420.a84;
        sz += AL(y) * 3;
        sz += AL(y >> 2) * 3;
        sz += AL(y >> 2) * 3;
        if (lbl_80420420.a7 != 0) {
            sz += AL(lbl_80420420.a48 * 4) * 6;
        }
        return sz + 0x1000;
    }
    return 0;
}
u32 fn_8033119C(void);
u32 VIGetTvFormat(void);
s64 fn_8028C418(s64, s64);
int fn_802370F4(void) {
    if (lbl_80420420.a88 & 1) {
        if (fn_8033119C() == 0) return 1;
    } else if (lbl_80420420.a88 & 2) {
        if (fn_8033119C() == 1) return 1;
    } else {
        int t = 100.0f * lbl_80420420.a4c;
        if (VIGetTvFormat() == 1) {
            lbl_80420420.d4 = fn_8028C418(lbl_80420420.c8 * t, 0x1388);
        } else {
            lbl_80420420.d4 = fn_8028C418(lbl_80420420.c8 * t, 0x176a);
        }
        if (lbl_80420420.d0 != (int)lbl_80420420.d4) {
            lbl_80420420.d0 = lbl_80420420.d4;
            return 1;
        }
    }
    return 0;
}
}
