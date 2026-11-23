/* fn_801DBD98: 6 of 22 words differ */
void fn_801DBD98(int x, int y, int a) {
    f32 fx;
    f32 fy;
    fy = y;
    fx = x;
    fn_801C6D98(a, 0, fx, fy);
}

/* fn_801D2AC0: 18 of 60 words differ */
void fn_801D2AC0(TitleP* p) {
    char buf[0x40];
    switch (*(u8*)((u8*)fn_80060728(lbl_803CAB38) + 0x11)) {
    case 3:
    case 0:
        strcpy(buf, lbl_8038C0EC);
        break;
    case 1:
        strcpy(buf, lbl_8038C0D8);
        break;
    case 2:
        strcpy(buf, lbl_8038C0C4);
        break;
    }
    if (fn_801D5F7C() == 0) return;
    if (fn_8023F880(fn_801D5DC4()) == 0) return;
    if (!fn_8023F880(buf)) goto end;
    goto load;
load:
    fn_801D5DFC();
    p->s44 = fn_80075FB4(fn_801D5DC4(), 0x80);
    p->s48 = fn_80075FB4(buf, 0x80);
    fn_80083B78(p);
end:
    return;
}

