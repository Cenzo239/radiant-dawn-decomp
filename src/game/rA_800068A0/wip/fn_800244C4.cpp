/* fn_800244C4: near miss, 3 of 82 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
NameProc* fn_800244C4(const char* name, void* parent) {
    NameProc* p;
    u32 size;
    if (fn_8010E2F4(&lbl_804CB814->l3c) == 0) {
        return 0;
    }
    if (parent != 0) {
        p = (NameProc*)fn_80081194(lbl_803789A0, parent);
    } else {
        p = (NameProc*)fn_80081050(lbl_803789A0, parent);
    }
    if (p != 0) {
        fn_801E4094(p);
        *(u32*)&p->s = 0;
        p->s.l.len = 0;
        p->s.l.ptr = 0;
        size = strlen(lbl_804CA05C);
        fn_80024EFC(&p->s, size);
        fn_800250B0(&p->s, 0, 0, lbl_804CA05C, lbl_804CA05C + size, E());
        p->a4c = 0;
    }
    size = !p->s.l.lng ? p->s.s.len : p->s.l.len;
    fn_800250B0(&p->s, 0, size, name, name + strlen(name), E());
    return p;
}
