/* Round 12 improvements on functions still listed in the older wip files. They use the
 * declarations of the file named in each comment. _i wrappers rank parameters only. */

/* fn_800D70F4 (fn_800D5B4C.cpp): 2 words: the li of the counter schedules before addi r31 */
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




/* fn_800DA430 (fn_800D7D74.cpp): 8 words: dur and flag swap r29/r30 */
int fn_800DA430(int id, int a, int dur) {
    /*P*/
    int fl;
    int d2;
    Unit* u;
/*E*/
    id = (u8)id;
    if (id) {
        u = &lbl_804CB810[id - 1];
    } else {
        u = 0;
    }
    UNIT_CHECK(u)
    d2 = TurnFrames(u, a, dur);
    fl = 0;
    if (TurnSnap(u)) {
        fl |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || d2 == 0) {
        fn_80102E10(u, 0, fl, 0, a);
    } else {
        fn_80102E10(u, d2, fl, Get30(), a);
    }
    return 1;
}

/* fn_800D9FA8 (fn_800D7D74.cpp): 16 words: unit, dir and flag rotate */
static inline int fn_800D9FA8_i(int id, int dir, int dur) {

    Unit* u = UnitId(id);
    int a;
    UNIT_CHECK(u)
    switch ((u8)dir) {
    case 4:
        a = 0;
        break;
    case 6:
        a = 0x2D;
        break;
    case 2:
        a = 0x5A;
        break;
    case 10:
        a = 0x87;
        break;
    case 8:
        a = 0xB4;
        break;
    case 9:
        a = 0xE1;
        break;
    case 1:
        a = 0x10E;
        break;
    case 5:
        a = 0x13B;
        break;
    default:
        a = 0;
        break;
    }
    dur = TurnFrames(u, a, dur);
    dir = 0;
    if (TurnSnap(u)) {
        dir |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, dir, 0, a);
    } else {
        fn_80102E10(u, dur, dir, Get30(), a);
    }
    return 1;
}
int fn_800D9FA8(int id, int dir, int dur) { return fn_800D9FA8_i(id, dir, dur); }




/* fn_800DA1FC (fn_800D7D74.cpp): 13 words: y and dur swap r28/r30 */
static inline int fn_800DA1FC_i(int id, int x, int dur, int y) {

    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    y = fn_800FB100(u, 0.5f + x, 0.5f + y);
    dur = TurnFrames(u, y, dur);
    x = 0;
    if (TurnSnap(u)) {
        x |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, x, 0, y);
    } else {
        fn_80102E10(u, dur, x, Get30(), y);
    }
    return 1;
}
int fn_800DA1FC(int id, int x, int y, int dur) { return fn_800DA1FC_i(id, x, dur, y); }



