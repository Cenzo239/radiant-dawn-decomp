/* near miss: 13 words; the second Find1 wants r4 for the pointer and r3 for the key. Declarations in ../fn_801CE800.cpp */
void fn_801CEC98(SKC* s) {
    s->x2 = -1;
    s->x4 = 0;
    fn_801CF3E4(s);
    {
    u8* e = (u8*)s + 0x50;
    int i;
    for (i = 0; i < 3; e += 0x20, i++) {
        s16 v = EcI(e, i)->xA;
        EcI(e, i)->x6 = v;
        EcI(e, i)->x8 = v;
        EcI(e, i)->xE = 0;
    }
    }
    {
    BQ* q = Q;
    for (;;) {
        int k = q->e[q->i].k;
        switch (k) {
        case 0: case 0x2A: goto done;
        case 9: {
            s16 v = q->e[q->i].v;
            s->x4 = v;
            s->x50[0].xA += v;
            s->x50[0].xE = v;
            break;
        }
        case 0x14: {
            s16 v = q->e[q->i].v;
            s->x4 = v;
            s->x50[1].xA += v;
            s->x50[1].xE = v;
            break;
        }
        case 0x6E: case 0x6F: case 0x70: s->x2 = k; break;
        }
        q->i++;
    }
    }
done:
    {
    void* v;
    s->x8 = (u32)(v = 0);
    if (s->x50[0].u) v = ((UQ*)s->x50[0].u)->x3F0;
    if (Dead(&s->x50[0], v)) s->x8 = 1;
    }
    if (Dead(&s->x50[1], UVal(&s->x50[1]))) s->x8 = 1;
    s->xA++;
    if (Find1(s) != 0) {
        int t;
        switch (Find1(s)) {
        case 0x42: t = 5; break;
        case 0x44: t = 2; break;
        case 0: t = 0; break;
        default: t = 1; break;
        }
        if (s->xB == t) s->xB = 1;
        else s->xB++;
    } else {
        s->xB = 0;
    }
    s->xB0 = Q->i;
}
