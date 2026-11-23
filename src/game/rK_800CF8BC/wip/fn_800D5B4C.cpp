/* fn_800D5C44: ['DIFF fn_800D5C44: 33 of 46 words differ'] */
Vec fn_800D5C44(Sel* s) {
    Vec v = {0.0f, 0.0f, 0.0f};
    Actor* a = SelActor(s);
    if (a) {
        v = fn_800F7790(a);
    } else {
        v = fn_800D5B4C(s);
    }
    return v;
}

/* fn_800D5DC4: ['DIFF fn_800D5DC4: 33 of 56 words differ'] */
Vec fn_800D5DC4(Sel* s) {
    Vec r = fn_800D5C44(s);
    fn_80011B90(0, &r, &r);
    return r;
}

/* fn_800D68C0: ['DIFF fn_800D68C0: 7 of 36 words differ'] */
void fn_800D68C0(CamProc* p) {
    Cam* c = fn_8012FCD0();
    c->f8 = p->f30;
    fn_8012F5CC(c, p->o60);
    c->f68 = 3.0f;
    {
        Vec a = {0.0f, 0.0f, 0.0f};
        CamV(c, a);
    }
    fn_8012FCC0();
    lbl_804CB742 = 0x10;
}

/* fn_800D6D10: ['DIFF fn_800D6D10: 65 of 90 words differ'] */
void fn_800D6D10(RingProc* p) {
    int y;
    fn_8013E7FC();
    fn_80021BA4(1, 4, 5, 0);
    {
        Color c = p->col;
        c.a = fn_8001EF44(p->d, p->t, 0.0f, p->col.a);
        for (y = p->cy - p->r; y <= p->cy + p->r; y++) {
            int x;
            for (x = p->cx - p->r; x <= p->cx + p->r; x++) {
                if (fn_8028DB44(y - p->cy) + fn_8028DB44(x - p->cx) <= p->r) {
                    if (fn_80117A0C(&lbl_803EC898, (s8)x, (s8)y) == 0) {
                        if (!(fn_801181E8(&lbl_803EC898, (s8)x, (s8)y)[2][7] & 1)) {
                            fn_8013EE5C(x, y, c);
                        }
                    }
                }
            }
        }
    }
    fn_80011838(-1);
}

/* fn_800D70F4: ['DIFF fn_800D70F4: 8 of 86 words differ'] */
int fn_800D70F4(void* p) {
    Glob* g = (Glob*)lbl_803C8E80;
    u32 u[4];
    int i;
    if (!(g->fl & 0x1000)) {
        return 0;
    }
    u[0] = g->u3F0;
    u[1] = g->u15F0;
    u[2] = g->u15F4;
    u[3] = g->u890;
    if (u[0] == 0) {
        return 0;
    }
    if (u[1] == 0) {
        return 0;
    }
    if (u[2] == 0) {
        return 0;
    }
    if (u[3] == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        void* q;
        fn_8010301C(u[i], u[3], 0x18, 0, p);
        q = fn_800E3A10(lbl_8036651C + 0x3A, p);
        if (q) {
            fn_800E5884(q, u[i], u[3]);
        }
    }
    ChatMsg((Glob*)lbl_803C8E80, fn_800D0864(lbl_8036651C + 0x47));
    fn_8009F630(p);
    return 1;
}

