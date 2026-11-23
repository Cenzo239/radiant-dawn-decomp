/* fn_800D70F4: 2 words: li of the counter schedules after addi r31; see fn_800D6EE4.cpp for declarations. */
static inline int fn_800D70F4_i(void* p) {
    Glob* g = (Glob*)lbl_803C8E80;
    u32 u[4];
    /*P*/
    u32 u3;
    int i;
    const char* s;
    u32* q;
/*E*/
    if (!(g->fl & 0x1000)) {
        return 0;
    }
    u[0] = g->u3F0;
    u[1] = g->u15F0;
    u[2] = g->u15F4;
    u3 = g->u890;
    u[3] = u3;
    if (u[0] == 0) {
        return 0;
    }
    if (u[1] == 0) {
        return 0;
    }
    if (u[2] == 0) {
        return 0;
    }
    if (u3 == 0) {
        return 0;
    }
    for (i = 0, q = u; i < 3; i++, q++) {
        void* m;
        fn_8010301C(*q, u3, 0x18, 0, p);
        m = fn_800E3A10(lbl_8036651C + 0x3A, p);
        if (m) {
            fn_800E5884(m, *q, u3);
        }
    }
    s = fn_800D0864(lbl_8036651C + 0x47);
    ChatMsg((Glob*)lbl_803C8E80, s);
    fn_8009F630(p);
    return 1;
}
int fn_800D70F4(void* p) { return fn_800D70F4_i(p); }
