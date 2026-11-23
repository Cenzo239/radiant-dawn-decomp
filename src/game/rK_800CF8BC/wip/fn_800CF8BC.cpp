/* fn_800D042C: ['DIFF fn_800D042C: 21 of 215 words differ'] */
SelProc* fn_800D042C(Menu* m, void* parent) {
    SelProc* p;
    int i;
    if (parent) {
        p = fn_80081194(lbl_80383AC8, parent);
    } else {
        p = fn_80081050(lbl_80383AC8, 3);
    }
    p->b48 = (int)lbl_803CAB38.f934;
    p->b49 = (int)lbl_803CAB38.f938;
    for (i = 0; i < lbl_803E7320.n; i++) {
        int n = lbl_803E7320.n;
        lbl_803E7320.e[i].left = &lbl_803E7320.e[(i + n - 1) % n];
        lbl_803E7320.e[i].right = &lbl_803E7320.e[(i + 1) % n];
    }
    p->menu = m;
    {
        TileEntry* e = First();
        p->e40 = e;
        if (e) {
            p->e44 = e;
        }
    }
    {
        TileEntry* a = First();
        TileEntry* b = First();
        s8 ix = a->x;
        s8 iy = b->y;
        SetPos(p, 0.5f + ix, 0.5f + iy);
    }
    fn_800620A8(&lbl_803CAB38, First()->x, First()->y);
    m->v0C(p);
    m->count = 0;
    m->v1C(p);
    lbl_803CAB38.b92C = 0x10;
    return p;
}

/* fn_800D0BFC: ['DIFF fn_800D0BFC: 2 of 112 words differ'] */
char* fn_800D0BFC(const char* s) {
    int len = fn_800D0998(s);
    char* p = lbl_804CA480;
    if ((u32)(0x800 - (p - lbl_803E8528)) <= len) {
        p = lbl_803E8528;
        lbl_804CA480 = p;
    }
    char* start = p;
    while (*s) {
        if (*s == '@') {
            s++;
            switch (*s) {
            case '@':
                *p++ = '@';
                s++;
                continue;
            case '{': {
                s8 i = s[1];
                s += 3;
                MsgVar* e = &lbl_803E8D28[i - '0'];
                strcpy(p, e->str);
                p += e->len;
                continue;
            }
            case '[': {
                int i = s[1];
                s += 3;
                strcpy(p, fn_800D0B90(i));
                p += strlen(fn_800D0B90(i));
                continue;
            }
            default:
                *p++ = '@';
                break;
            }
        }
        if (IsSjis((const u8*)s)) {
            u8 a = s[0];
            u8 b = s[1];
            s += 2;
            p[0] = a;
            p[1] = b;
            p += 2;
        } else {
            *p++ = *s++;
        }
    }
    *p++ = 0;
    lbl_804CA480 = p;
    return start;
}

