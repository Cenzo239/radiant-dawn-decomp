// fn_800C763C 7/17 (r4/r5/r6 colours). fn_800C7850 size 0x9C vs 0xAC: loop unrolled over per-array base registers r5..r9.
// fn_800C78FC 36/40 and fn_800C79A0 50/59: need stmw and per-array induction pointers; structure right, registers not.
void fn_800C763C(DimP* p) {
    FaceX* f = (FaceX*)lbl_803E50D0[p->idx];
    p->t = 0;
    int v = f->m41;
    p->from = v;
    if (v < p->to) {
        p->mode = 0;
        return;
    }
    p->mode = 4;
}

void* fn_800C7850() {
    FaceCache* c = &lbl_803E7200;
    for (int i = 0; i < 8; i++) {
        c->res[i] = NULL;
        c->key[i] = NULL;
        c->del[i] = 0;
        c->ref[i] = 0;
    }
    return fn_80081050(lbl_80382918, (void*)2);
}

void fn_800C78FC() {
    char buf[0x40];
    FaceCache* c = &lbl_803E7200;
    int z = 0;
    void** r = c->res;
    s16* n = c->ref;
    s16* d = c->del;
    void** k = c->key;
    for (int i = 0; i < 8; i++, n++, d++, k++, r++) {
        if (*r != NULL && *n == 0) {
            if ((*d = *d - 1) == 0) {
                fn_800C3E70(*k, buf);
                fn_80006A2C(r);
                *k = (void*)z;
            }
        }
    }
}

void* fn_800C79A0(void* name) {
    char buf[0x40];
    FaceCache* c = &lbl_803E7200;
    void* k = fn_800C3FD0(name);
    void* r = NULL;
    for (int i = 0; i < 8; i++) {
        if (k == c->key[i]) {
            c->ref[i]++;
            return c->res[i];
        }
    }
    for (int j = 0; j < 8; j++) {
        if (c->res[j] == NULL) {
            fn_800C3E70(k, buf);
            void** pr = &c->res[j];
            fn_800068EC(pr, buf, 0x2080);
            c->ref[j] = 1;
            r = *pr;
            c->key[j] = k;
            break;
        }
    }
    return r;
}

