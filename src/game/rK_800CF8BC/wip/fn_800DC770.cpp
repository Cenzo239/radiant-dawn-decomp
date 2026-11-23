/* Near misses from fn_800DC770.cpp. Same declarations as that file.
 * fn_800DC770 (CopyMapCamera): 5 words, f0/f2 colouring of two float loads.
 * fn_800DC824 (PastMapCamera), fn_800DC9D4 (InstantPastMapCamera): the look-at
 *   copy wants `lfs f1; frsp f3,f1; stfs f1,0x44; stfs f3,0x38`. No spelling tried
 *   emits the frsp, so they are 12 bytes short. camSet below is empty on purpose:
 *   its body was being varied by script.
 * fn_800DFD3C: 44 words, only the FIFO base: lis 0xCC01 should be r6 above the
 *   four colour bytes, but it lands in r5 and the alpha byte takes r6. */
#define WGF (*(volatile f32*)0xCC008000)
#define WGB (*(volatile u8*)0xCC008000)

int fn_800DC770() {
    Cam* c = fn_8012FCD0();
    if (c) {
        SavedCam* s = &lbl_803E8F78;
        s->x4 = c->x4;
        s->x8 = c->x8;
        s->xC = c->xC;
        {
            Vec t = c->v38;
            s->v = t;
            s->tx = lbl_803CAB38.x;
            s->ty = lbl_803CAB38.y;
            lbl_803E8F78.valid = 1;
        }
    }
    return 1;
}

static inline void camSet(Cam* c, f32 x, f32 y, f32 z) {} //C
static inline void camLook(Cam* c, const Vec& v) {
    camSet(c, v.x, v.y, v.z);
}

#define RESTORE_A(c, s)                     \
    c->x4 = s->x4;                          \
    c->x10 = c->x4;                         \
    c->x8 = s->x8;                          \
    c->x14 = c->x8;                         \
    fn_8012F580(c, s->xC);                  \
    {                                       \
        Vec t = s->v;                       \
        camLook(c, t);                      \
    }                                       \
    fn_800620A8(&lbl_803CAB38, s->tx, s->ty);

static inline void restoreB(Cam* c, SavedCam* s) {
    c->x4 = s->x4;
    c->x8 = s->x8;
    c->xC = s->xC;
    {
        Vec t = s->v;
        c->v44 = t;
    }
    fn_800620A8(&lbl_803CAB38, s->tx, s->ty);
}

int fn_800DC824() {
    if (lbl_804CB700 & 0x8001) {
        if (lbl_803E8F78.valid) {
            Cam* c = fn_8012FCD0();
            if (c) {
                SavedCam* s = &lbl_803E8F78;
                RESTORE_A(c, s)
            }
        }
    } else {
        if (lbl_803E8F78.valid) {
            Cam* c = fn_8012FCD0();
            if (c) {
                restoreB(c, &lbl_803E8F78);
            }
        }
    }
    return 1;
}

int fn_800DC9D4() {
    if (lbl_803E8F78.valid) {
        Cam* c = fn_8012FCD0();
        if (c) {
            SavedCam* s = &lbl_803E8F78;
            RESTORE_A(c, s)
        }
    }
    return 1;
}

static inline void pos3(f32 x, f32 y, f32 z) {
    WGF = x;
    WGF = y;
    WGF = z;
}
static inline void col4(TileFx* p) {} //C

void fn_800DFD3C(TileFx* p) {
    int k;
    Mtx34 m;
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021EF8(0, 4);
    fn_80021CB4(0, 0xFF, 0xFF, 4);
    fn_80021C34(0);
    fn_80021F7C(0, 1, 4, 0x3C);
    fn_80021B68(0);
    fn_803128AC(&m, 0.0f, 0.0f, -0.02f);
    fn_80312378(fn_8000FB88(), &m, &m);
    fn_80307E48(&m, 0);
    fn_80021784(0);
    fn_80021BA4(1, 4, 1, 0);
    fn_80304314(0x98, 0, 4);
    pos3(p->x, p->y, p->h[0]);
    col4(p);
    pos3(p->x + 1, p->y, p->h[1]);
    col4(p);
    pos3(p->x, p->y + 1, p->h[2]);
    col4(p);
    k = -1;
    pos3(p->x + 1, p->y + 1, p->h[3]);
    col4(p);
    fn_80011838(k);
}

