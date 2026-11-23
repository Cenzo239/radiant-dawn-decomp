/* fn_80021EF8: near miss, 26 of 27 words differ. Depends on types and helpers from ../fn_80021754.c; goes there in address order. */
void fn_80021EF8(int i, u32 key) {
    GXCache* g = &lbl_803B7878;
    u32* k = g->a8040;
    if (key != k[i]) {
        u32* b = g->a8080;
        u32* c = g->a80C0;
        u32* d = g->a8100;
        u32* e = g->a8140;
        b[i] = -1;
        c[i] = -1;
        d[i] = -1;
        e[i] = -1;
        fn_80306C18(i, key);
        k[i] = key;
    }
}
