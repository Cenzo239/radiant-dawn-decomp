// 2/69: original builds flags as li r4,0; ori r0,r4,0x204C (also fn_800B2710). Probably a bitfield/enum-typed constant.
void fn_800BEC84(ChrB* c) {
    c->m54 = -1;
    c->m57 = -1;
    c->m55 = -1;
    c->m30 = NULL;
    c->m78 = NULL;
    c->m7c = NULL;
    c->m34 = NULL;
    c->m38 = NULL;
    c->m80 = NULL;
    c->m8c = NewBlend(0);
    c->m90 = NewBlend(0);
    c->m94 = NewBlend(3);
    c->m3c = NULL;
    c->m40 = NULL;
    c->m98 = NULL;
    c->flags = 0x204C;
    fn_800B29D0((Chr*)c);
}

