/* fn_80023360: near miss, 69 of 150 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
void fn_80023360(SallyM* p) {
    char buf[0x88];
    int n;
    char* q;
    int i;
    Sub2C* c;
    lbl_804CB140 = 0;
    lbl_804CB700 &= ~1;
    n = fn_8010CF20(!p->s.isLong ? (char*)&p->s + 1 : p->s.ptr, buf);
    fn_800CFB34(lbl_803E7320);
    q = buf;
    for (i = 0; i < n; i++) {
        fn_800CFC50(lbl_803E7320, (s8)q[0], (s8)q[1], 0, 0);
        q += 2;
    }
    c = (Sub2C*)fn_80081050(lbl_80378968, p);
    p->p50 = c;
    c->b2C |= 8;
    mnuAdd((Mnu*)p);
    ((Fld*)fn_80060728(lbl_803CAB38))->b21 = 0;
    ((Fld*)fn_80060728(lbl_803CAB38))->b22 = 0;
    ((Fld*)fn_80060728(lbl_803CAB38))->w28 = 0;
    lbl_804CB700 |= 0x10000;
    fn_8012FC90();
}
