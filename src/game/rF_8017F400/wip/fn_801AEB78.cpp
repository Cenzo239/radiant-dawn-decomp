/* fn_801AEB78 and fn_801AEDC4 (mode title sprintf): all but the register of the string base match.
   The original keeps lbl_8036D68C in r26 and the fn_800D0864 results in r27..r31; ours always gives the base r31,
   whichever declaration order or inline is used. */
void fn_801AEDC4(CProc* p) {
    const char* e;
    int c;
    const char* b;
    int a;
    const char* t;
    CData* d = p->d;
    d->x88 = 1;
    d->x5 = 0;
    d->x16 = 1;
    d->x17 = 1;
    d->x18 = 0;
    d->x1A = 0x1C2;
    d->x1C = 0x3D;
    fn_801ADE00(d);
    fn_80253EE4(lbl_8036D68C + 0x15A, 0.0f);
    t = fn_800D0864(lbl_8036D68C + 0x173);
    a = fn_800CEC24(t);
    b = fn_800D0864(lbl_8036D68C + 0x108);
    c = fn_800CEB4C(b);
    e = fn_800D0864(lbl_8036D68C + 0xFD);
    fn_80290DDC(d->title, lbl_8036D68C + 0xEE, fn_800CF470(e), e, c, b, a, t);
}

