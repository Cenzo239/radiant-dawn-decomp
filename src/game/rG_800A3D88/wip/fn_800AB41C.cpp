// Near misses, see NOTES.md. Needs declarations from ../fn_800ABFB8.cpp.
// 200 vs 198 words: two registers too many; the rest of the shape is right.
int fn_800AB41C(Bat* b) {
    for (int i = 0; i < 2; i++) {
        Ch* c = At(b, i);
        int k = fn_801D0674(b->m88, i);
        c->m55 = k;
        UP* p = fn_801D0784(b->m88, k);
        if (p != NULL && UnitOf(p) != NULL) {
            void* d;
            if (IsR(b)) d = fn_800A75E8(UnitOf(p), 1);
            else d = fn_800A75E8(UnitOf(p), 0);
            if (d == NULL) return 0;
            c->data = d;
            fn_800B1120(c);
            fn_800B1628(c, p->u);
            fn_800B4574(c, fn_801CE474(p), 0);
            for (int j = 0; j < 2; j++) {
                if (lbl_803C8E80.m15f0[j != 0] != NULL) {
                    b->m8c[j] = fn_800A75E8((Un*)lbl_803C8E80.m15f0[j != 0], 0);
                }
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        Ch* c = At(b, i);
        if (fn_800BD280(c)) {
            Un* u = fn_801D0784(b->m88, c->m55)->u;
            fn_800B540C(c, u);
            c->m57 = b->m78;
            fn_800B54DC(c, -1);
            if (fn_800A7460(c->data, STR(0x1D)) != NULL) {
                b->m82 = 1;
                b->m85 = 0;
            }
            if (fn_8011B77C((u8*)u + 300, lbl_804CA5A0)) fn_800BEBD4(c);
            if (fn_8011B77C((u8*)u + 300, lbl_804CA5AC)) {
                fn_800BEBD4(c);
                if (fn_800A8008(STR(0x2A))) fn_800B4744(c, fn_800A67EC(), 0);
            }
        }
    }
    b->m70 = fn_800A93B8(b, fn_801D035C(b->m88));
    b->m74 = fn_800A93B8(b, fn_801D0374(b->m88));
    if (b->m81 != 0) {
        if (fn_800B196C(b->m70, STR(0x3B)) == 0) b->m81 = 0;
        if (b->m82 != 0) b->m81 = 0;
        if (b->m88->mC != 0) b->m81 = 0;
    }
    return 1;
}
