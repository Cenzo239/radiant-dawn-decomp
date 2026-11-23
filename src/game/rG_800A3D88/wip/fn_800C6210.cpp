// Near misses, see NOTES.md. Needs declarations from ../fn_800C6210.cpp.
Fc* fn_800C5EA4(int i, const char* name, int x, int y, u32 fl, int z, int par) {
/*P*/
    Fc* f;
    FR* r;
/*E*/
    r = FontGet(name);
    if (lbl_803E50D0[i] != NULL) return NULL;
    if (fl & 0x100) {
        if (par == 0) par = 3;
        f = fn_80081050(lbl_803827A8, par);
        f->m34 = r;
        f->m40 = i;
        f->m38 = x;
        f->m3c = y;
        f->m48 = fl;
        f->m41 = -1;
        f->m42 = 0;
        if (fl & 0x400) {
            f->m48 &= ~0xC00;
            if (f->m34->m24 == 0) f->m48 |= 0x800;
        }
        f->m4c = NULL;
        f->m50 = NULL;
        lbl_803E50D0[i] = f;
        f->m30 = NULL;
    } else {
        if (par == 0) par = 3;
        f = fn_80081050(lbl_803827C0, par);
        f->m34 = r;
        f->m40 = i;
        f->m38 = x;
        f->m3c = y;
        f->m48 = fl;
        f->m41 = -1;
        f->m42 = 0;
        if (fl & 0x400) {
            f->m48 &= ~0xC00;
            if (f->m34->m24 == 0) f->m48 |= 0x800;
        }
        f->m4c = NULL;
        f->m50 = NULL;
        lbl_803E50D0[i] = f;
        if (fn_80291480(name, lbl_80365E0C + 0x44)) f->m48 |= 0x1000;
        if (!(fl & 0x200)) {
            if (r->m20 & 2) f->m4c = fn_80081050(lbl_803827F8, (int)f);
            if (r->m20 & 1) f->m50 = fn_80081050(lbl_80382814, (int)f);
        }
    }
    return f;
}
