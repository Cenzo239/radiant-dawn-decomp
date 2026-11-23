/* fn_800D042C (round 17 near miss): 15 of 215 words (was 21). Append to a copy of fn_800CF8BC.cpp inside its extern "C"
 * block with #pragma use_lmw_stmw on. The pv/nx locals fixed the modulo order; left: the loop counter, list base and
 * count rotate among r9/r10/r11 (volatile registers; loop forms and declaration order did not move them). */
static inline void Link(TileList* l, int i) { int n = l->n; l->e[i].left = &l->e[(i + n - 1) % n]; l->e[i].right = &l->e[(i + 1) % n]; }
static inline void Link2(TileList* l, int i, int n) { l->e[i].left = &l->e[(i + n - 1) % n]; l->e[i].right = &l->e[(i + 1) % n]; }
SelProc* fn_800D042C(Menu* m, void* parent) {
/*P*/
    SelProc* p;
    int i;
    int n;
    int pv;
    int nx;
    TileList* l;
/*E*/
    if (parent) {
        p = fn_80081194(lbl_80383AC8, parent);
    } else {
        p = fn_80081050(lbl_80383AC8, 3);
    }
    p->b48 = (int)lbl_803CAB38.f934;
    p->b49 = (int)lbl_803CAB38.f938;
    for (i = 0; i < lbl_803E7320.n; i++) {
        n = lbl_803E7320.n;
        pv = (i + n - 1) % n;
        nx = (i + 1) % n;
        lbl_803E7320.e[i].left = &lbl_803E7320.e[pv];
        lbl_803E7320.e[i].right = &lbl_803E7320.e[nx];
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
