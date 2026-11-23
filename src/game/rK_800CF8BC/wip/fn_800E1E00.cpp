/* Near misses from fn_800E1E00.cpp. Same declarations as that file.
 * fn_800E24F8: 17 words with the body written in place (see below it is the
 *   wrapper form, 31 words). Only m/mode/snd/base registers rotate: m should sit
 *   in r29 below the lis base (r31), but always lands in r31.
 * fn_800E28E4: 11 words in plain form, 19 with this wrapper. Outer h should be
 *   r30 and the inlined quakeOf h r29; they come out swapped. Writing quakeOf in
 *   place fixes the registers but mirrors the stack slots. */
static inline int openFile(const char* path, int mode) {
    if (fn_8023F9F4(path) == 0x40000) {
        return 0;
    }
    fn_8023F1A0(path, mode);
    return 1;
}

static inline void loadChain(ModelDef* m) {
    /*P*/
    SndLoad* l;
    WaitProc* w;
    void* snd;
    int mode;
/*E*/
    char name[0x40];
    char path[0x40];
    fn_80290DDC(path, "%s%s.cmp", "yme/", fn_800E22F8(m, name));
    mode = 0;
    {
        u16 fl = m->flags;
        if (fl & 0x400) mode = 0x2040;
        if (fl & 0x200) mode = 0x2080;
        if (fl & 0x800) mode |= 0x200;
    }
    if (openFile(path, mode)) {
        snd = m->snd;
        if (snd) {
            l = fn_8013B9A8();
            if (l && l->parent) {
                if (fn_802578F0() >= 0x18) {
                    fn_800846BC(lbl_80384218);
                }
                w = fn_80083B84(lbl_80384218);
                if (!w) {
                    w = (WaitProc*)fn_80081050(lbl_80384218, l->parent);
                }
                if (!fn_80257520(snd)) {
                    fn_80257340(snd, 0x10000);
                    w->n34++;
                }
                w->n30++;
                w->t38 = 0;
            }
            {
                WaitProc* w2 = fn_80083B84(lbl_80384218);
                if (w2) {
                    w2->n30--;
                    w2->t38 = 0;
                }
            }
        }
        if (subName(m->sub10)) {
            fn_800E24F8(subName(m->sub10));
        }
        if (subName(m->sub12)) {
            fn_800E24F8(subName(m->sub12));
        }
    }
}

#pragma use_lmw_stmw on
#pragma push
#pragma auto_inline off
void fn_800E24F8(const char* s) {
    if (s) {
        ModelDef* m = fn_80076F54(s);
        if (m) {
            loadChain(m);
        }
    }
}
#pragma pop
#pragma use_lmw_stmw off

static inline Vec quakeOf(ModelProc* p) {
    Vec r = {0.0f, 0.0f, 0.0f};
    AnimHost* h = p->d->h;
    if (h) {
        int i = fn_80007630(h, "quake");
        if (i >= 0) {
            Vec a;
            Vec b;
            fn_800078E4(h, i)->flags |= 0x08000000;
            a = fn_800076E8(h, i);
            fn_8001E9E4(&h->o10, &b);
            fn_80313484(&a, &b, &r);
        }
    }
    return r;
}

static inline void quakeTick(ModelProc* p, AnimHost* h) {
    if (h) {
        Vec v = quakeOf(p);
        if (fn_80313508(&v) > 0.0f) {
            CamH* c = fn_8012FCD0();
            if (c) {
                Vec t = v;
                c->v08(&t);
            }
        }
        if (fn_80008EB4(h)) {
            if (fn_80008C98(h, 0xF)) {
                fn_8012F5CC(fn_8012FCD0(), 0);
            }
            if (fn_80008C98(h, 0x10)) {
                fn_8012F5CC(fn_8012FCD0(), 2);
            }
        }
    }
}

void fn_800E28E4(ModelProc* p) {
    quakeTick(p, p->d->h);
}

