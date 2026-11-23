/* near misses; take the declarations from ../fn_801BA664.cpp */
int fn_801BB334(void* self, Row* e, int col) {
    int r = 0;
    U* u = e->u;
    switch (col) {
    case 0:
        return SortKey(u);
    case 1: {
Slot* s; int i; SkillD* d;
        for (i = 0, s = u->x12C; i < 18; i++, s++) { if (s && (d = s->p) && d->x1F) r++; }
        return r; }
    case 2:
        return Aff(u);
    case 3: {
        U* o = fn_8012E3A4(u);
        if (o) return fn_8012E8A0(o, fn_8012E9B4(o, u));
    }
    }
    return 0;
}

void fn_801BB530(void* self, Row* e, int r5, f32 x, f32 y) {
    Slot* out[6];
    U* o;
    int k;
    Slot* s;
    int i2;
    SkillD* d;
    int n;
    U* u;
    int i;

    fn_8007E154();
    fn_8007E4E4(x, y, 300.0f, 1.0f);
    fn_8007E74C((void*)fn_801B5E3C, 0);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    u = e->u;
    {
        n = 0;
        for (i = 0, s = u->x12C; i < 18; s++, i++) { if (s && (d = s->p) && d->x1F && n < 6) out[n++] = s; }
        if (n > 0) {
            for (i2 = n - 1; i2 >= 0; i2--) {
                int xp = 0xEA + i2 * 20; ICONS2->v4(xp, 0, out[i2]->p->x1F);
            }
        }
    }
    ICONS->v4(0x174, 0, fn_801196F0((u8)Aff(u)));
    o = fn_8012E3A4(u);
    k = 0x1A6;
    if (o) {
        ICONS->v4(k, 0, fn_801196F0((u8)Aff(o)));
        fn_801B5EB4(2, r5, (void*)fn_80118C44(o->ec), 32.0f + (x + (f32)k), y);
    } else {
        fn_801B5EB4(2, r5, lbl_80389CD8, 32.0f + (x + (f32)k), y);
    }
}
