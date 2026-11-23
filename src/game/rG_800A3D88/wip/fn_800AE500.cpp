// fn_800AE500: 8/35, r30/r31 swap between i and p. fn_800AE774: 5/70, first d gets r31, want r30.
BOOL fn_800AE500(Battle* p) {
    int i;
    Battle* b = p;
    for (i = 0; i < 2; i++) {
        if (fn_800BD280(ChGet(p, i)) != 0) {
            Queue* q = p->q[i];
            if (q != NULL && q->head != q->tail) {
                return 1;
            }
        }
    }
    return 0;
}

void fn_800AE774(void* p) {
    void* a;
    UnitD* d;
    fn_8002BCC4(&lbl_803C8E80);
    UnitH* u = fn_8002C590(&lbl_803C8E80);
    if (u != NULL) {
        d = u->m3f0;
        if (d != NULL && fn_8011F428(d) == 0) {
            d->flags |= 0x10;
        }
    }
    a = lbl_803C8E80.m3f0;
    void* b = lbl_803C8E80.m890;
    if (a != NULL && b != NULL) {
        fn_8010301C(a, b, 0, 0, 0);
        fn_8010301C(b, a, 0, 0, 0);
    }
    u = fn_8002C738(&lbl_803C8E80);
    if (u != NULL) {
        d = u->m3f0;
        if (d != NULL) {
            fn_80134E30();
            fn_801868E8(d, p);
        }
    }
    if (lbl_803C8E80.flags & 0x00200000) {
        fn_80081A90(p);
    }
}

