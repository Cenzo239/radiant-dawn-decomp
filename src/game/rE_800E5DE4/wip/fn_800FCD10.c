/* Near misses from the map-unit effect processes in ../fn_800FCA40.c
 * (UProc/PSlot structs and externs live there).
 * fn_800FCD10: 6-7 of 32 words, FP register choice only (frsp f1,f1; zero in f2).
 * fn_800FCDD8 / fn_800FCEE4: the u32 colour is split into stack bytes with the
 *   shift result reused in one register and interleaved stb (a, r, g, b). The
 *   source form is unknown; a GXColor-writing inline gets within 7 of 66 words
 *   for 800FCEE4, and 800FCDD8 still forwards the bytes (size 0xD0 vs 0xE4).
 * fn_800FD05C: 17 of 28 words, FP register allocation of the bounce formula. */
void fn_800FCD10(UProc* p) {
    f32 s;
    p->s44.f += p->s34.f;
    p->s40.i++;
    s = fn_80295940(p->s44.f);
    SetOff(p->unit, p->s3C.f * s, 0.0f, 0.0f);
    if (p->s40.i >= p->s38.i) {
        fn_80083B78(p);
    }
}

void fn_800FCDD8(UProc* p) {
    void* mdl;
    f32 t;
    u32 v;
    GXColor c;
    p->s44.i++;
    mdl = p->unit->model;
    if (p->s44.i >= p->s40.i) {
        p->s44.i = p->s40.i;
        fn_80083B78(p);
    }
    t = fn_8001EF44(0.0f, 1.0f, p->s40.i, p->s44.i);
    v = fn_80175E7C(p->s34.c, p->s38.c, t);
    ColorFromU32(&c, v);
    fn_80008F10(mdl, c.r, c.g, c.b);
}

void fn_800FCEE4(UProc* p) {
    f32 t;
    u32 v;
    GXColor c;
    p->s40.i++;
    t = fn_8001EF30(0.0f, 1.0f, p->s3C.i, p->s40.i);
    v = fn_80175E7C(p->s34.c, p->s38.c, t);
    ColorFromU32(&c, v);
    fn_800F3EB0(p->unit, c);
    if (p->s40.i >= p->s3C.i) {
        fn_80083B78(p);
    }
}

void fn_800FD05C(UProc* p) {
    f32 t = p->s48.f + 1.0f;
    f32 z;
    p->s48.f = t;
    z = p->unit->z - (p->s40.f - t * (p->s44.f * t));
    if (z > p->s3C.f) {
        z = p->s3C.f;
        p->s48.f = 0.0f;
        p->s40.f = p->s40.f * p->s4C.f;
    }
    p->unit->z = z;
    if (p->s40.f < 0.01f) {
        fn_80083B78(p);
    }
}
