/* fn_800D4864: ['DIFF fn_800D4864: 19 of 107 words differ'] */
void fn_800D4864(MenuDef*, MenuProc* p) {
    s16 y = Cur(p)->y;
    if (p->curY < 0) {
        p->curY = y;
    } else {
        p->curY = (p->curY + y) / 2;
    }
    fn_8007E154();
    fn_8007E4E4(p->x, p->y, p->def->v70() - 1.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    {
        f32 h = (s16)p->def->v5C();
        fn_80080388(0.0f, p->curY, p->w, h);
    }
    fn_80080578(0);
    {
        Color z;
        *(u32*)&z = 0;
        fn_80080940(z, z, k1a, k1b);
    }
    fn_80080308();
}

/* fn_800D5448: ['DIFF fn_800D5448: 1 of 143 words differ'] */
MenuProc* fn_800D5448(MenuDef* m, void* parent, int layer) {
    MenuProc* p = fn_800811E4(lbl_80383ED0, parent);
    if (layer) {
        p->layer = layer;
    }
    fn_800D5798(p, m);
    p->def = m;
    p->x = m->v60();
    p->y = m->v64();
    p->w = m->v50();
    if ((s16)m->v54() != 0) {
        p->h = m->v54();
    } else {
p->h = MenuH(m, p->n);
    }
    p->prev = p->cur;
    p->a38 = -1;
    p->curY = -1;
    p->vis = 1;
    m->v14(p);
    m->v1C(p);
    {
        ItemProc* it = Cur(p);
        Cur(p)->item->v44(p, it);
    }
    p->sleep = m->v68();
    p->state = 1;
    if (m->v74()) {
        fn_80253EE4(m->v74(), 0.0f);
    }
    if (m->v0C()) {
        p->cur = -1;
    }
    return p;
}

/* fn_800D5798: ['DIFF fn_800D5798: 33 of 89 words differ'] */
void fn_800D5798(MenuProc* p, MenuDef* m) {
    int y = 0;
    int i = 0;
    p->n = 0;
    p->cur = -1;
    for (;;) {
        MenuItem* it = m->v44(i);
        int st;
        if (it == 0) {
            break;
        }
        st = it->v28(it, i);
        if ((u8)st != 3) {
            ItemProc* q;
            if ((u8)st == 1) {
                if (p->cur < 0) {
                    p->cur = p->n;
                }
                st = 0;
            }
            q = (ItemProc*)fn_80081050(lbl_80383F10, p);
            q->item = it;
            q->idx = i;
            q->vis = p->n;
            q->state = st;
            q->x = m->v48();
            q->y = y + m->v4C();
            q->o3C = 0;
            y += m->v5C();
            p->items[p->n++] = fn_80085ECC(q);
        }
        i++;
    }
    if (p->cur < 0) {
        p->cur = 0;
    }
}

