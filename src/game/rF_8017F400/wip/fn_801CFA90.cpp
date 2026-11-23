/* near misses; take the declarations from ../fn_801CFA90.cpp */
void fn_801CF040(SKW* s) {
    s->x1 = 0;
    switch (s->x6) {
    case 0x28:
        s->x1 = 7;
        break;
    default: {
        void* w = At2((SK*)s, s->x0);
        if (w) {
            s->x1 = 1;
            w = Wpn((EW*)w);
            if (w) {
                if (fn_801116B8(w)[1] & 2) s->x1 = 2;
                if (fn_801116B8(w)[0] & 0x800) s->x1 = 3;
                if (*(u64*)fn_801116B8(w) & 0x800000000000ULL) s->x1 = 2;
                if (fn_801116B8(w)[1] & 0x80) s->x1 = 6;
                if (fn_801116B8(w)[1] & 8) s->x1 = 2;
                if (*(int*)(lbl_803C8E80 + 0x15E8) > 1) {
                    if (fn_801116B8(w)[1] & 0x200) s->x1 = 2;
                    if (fn_801116B8(w)[0] & 0x4000) s->x1 = 4;
                    if (ItT(*(ItemT**)w) == 4) s->x1 = 5;
                }
            }
        }
    }
    }
}

void fn_801CF270(SKV* s) {
    BQ* q;
    s16 save;
    int v;
    s->x9 = 0;
    q = Q;
    save = Q->i;
    v = s->x0;
    if (s->x6 == 0x28) {
        v = v < 0 ? -1 : 1 - v;
    }
    for (;;) {
        switch (q->e[q->i].k) {
        case 0: goto done;
        case 0x24:
            if (Ev6E() != 0x71) {
                switch (Ev25()) {
                case 0x25:
                    if (v == 0) s->x9 = 1;
                    break;
                case 0x26:
                    if (v == 1) s->x9 = 1;
                    break;
                }
                goto done;
            }
            break;
        }
        q->i++;
    }
done:
    Q->i = save;
}
