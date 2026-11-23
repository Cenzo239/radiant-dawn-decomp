// 11/63: original has li r0,0; ori r0,r0,0x204C at the end (one extra word); no spelling found.
void fn_800B2710(Chr* c) {
    if (c->mdl != NULL) {
        fn_80011CBC(fn_80006EE0, c->mdl);
        if (c->m34 != NULL) {
            fn_80011CBC(fn_8023F1A8, c->m34);
        }
        if (c->m38 != NULL) {
            fn_80011CBC(fn_8023F1A8, c->m38);
            c->m38 = NULL;
        }
        c->mdl = NULL;
        c->m7c = NULL;
        c->m34 = NULL;
        for (int i = 0; i < 2; i++) {
            if (c->m3c[i] != NULL) {
                fn_80081A90(c->m3c[i]);
                c->m3c[i] = NULL;
            }
        }
        fn_800829CC(c, lbl_80382550);
        if (c->m98 != NULL) {
            fn_80081A90(c->m98);
            c->m98 = NULL;
        }
        c->flags = 0x204C;
    }
}
