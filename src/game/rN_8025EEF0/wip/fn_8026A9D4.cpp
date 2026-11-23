/* fn_8026A9D4 and fn_8026AB7C: 10-16 words. Registers want base r31, id r30, n r29, i r28, ofs r27. Inline return gives the right branch shape. */
static inline int introFind(int i, int id) {
    int n;
    int ofs;
    void* h;
    u8* t;
    h = fn_80077064(INTRO_NAME);
    n = (s16)fn_80109A2C(&h);
    ofs = i * 0x40;
    for (; i < n; ofs += 0x40, i++) {
        t = fn_80077064(INTRO_NAME) + 4;
        if (id == t[ofs]) {
            return i;
        }
    }
    return -1;
}

#pragma push
#pragma use_lmw_stmw off
void fn_8026A9D4(u8* q) {
    IntroProc* p = (IntroProc*)q;
    int m;
    int id;
    int i;
    fn_800A8660();
    fn_80075D78(lbl_8037307C + 0x19);
    p->m6C = fn_8001D3B4(lbl_8037307C + 0x27);
    p->m78 = fn_80075D78(fn_800D0DBC(lbl_8037307C + 0x37));
    p->skip = 0;
    *(void**)(q + 0x7C) = fn_80177260(p);
    fn_800CD4A4(4);
    fn_80250E38(0, 0.0f, 0.0f);
    fn_80250F0C(0, 0.7f, 0.0f);
    id = lbl_804CC038;
    *(u16*)(q + 0x5C) = id;
    *(s16*)(q + 0x5E) = introFind(0, id);
    fn_80109744(fn_80060728(lbl_803CAB38));
    m = 2;
    ((GameCfg*)fn_80060728(lbl_803CAB38))->mode = m;
    fn_801097FC(fn_80060728(lbl_803CAB38));
}
#pragma pop

void fn_8026AB7C(u8* q) {
    int id;
    int i;
    i = *(s16*)(q + 0x5E) + 1;
    id = *(u16*)(q + 0x5C);
    i = introFind(i, id);
    *(s16*)(q + 0x5E) = i;
    if ((s16)i < 0) {
        fn_80083DC4(q, 4);
    }
}

