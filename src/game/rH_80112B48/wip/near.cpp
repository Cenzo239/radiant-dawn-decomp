/* Near misses in region rH. Not compiled by anything; each comment says what is left.
 * They use the structs in map.h / unit.h and extern lists from their neighbours. */

/* fn_80119BB4: register swap only: count/e/found allocation */
void fn_80119BB4(void* a, void* b, u8 c) {

    int r = 0;
    int i;
    SupEnt* e = lbl_80412C18;
    int n = lbl_804CB80C;

    for (i = 0; i < n; i++, e++) {
        if ((a == e->a && b == e->b) || (a == e->b && b == e->a)) {
            r = 1;
            break;
        }
    }
    if (!r && n < 0x60) {
        e = &lbl_80412C18[n];
        e->a = a;
        e->b = b;
        e->c = c;
        lbl_804CB80C++;
    }
}

/* fn_801197F4: v in r30 across subf; ours splits the live range */
int fn_801197F4(SupData* p, int i) {
    int v = (s8)p->e[i].val;
    u8* a = fn_8010B1D8(p->pid);
    v -= SupGet(a, p->e[i].pid);
    if ((s8)v > 4) {
        v = 4;
    }
    if ((s8)v < 0) {
        v = 0;
    }
    return v;
}

/* fn_80113794: add/lhz register swap only */
void fn_80113794(Map* m, s8 x, s8 y, u32 f) {
    FlagOr(m, x, y, f);
    if (x > 0) {
        FlagOr(m, x - 1, y, f & 0x222);
    }
    if (x < m->w - 1) {
        FlagOr(m, x + 1, y, f & 0x111);
    }
    if (y > 0) {
        FlagOr(m, x, y - 1, f & 0x444);
    }
    if (y < m->h - 1) {
        FlagOr(m, x, y + 1, f & 0x888);
    }
}

/* fn_80113890: add/lhz register swap only */
void fn_80113890(Map* m, s8 x, s8 y, u32 f) {
    FlagClr(m, x, y, f);
    if (x > 0) {
        FlagClr(m, x - 1, y, f & 0x222);
    }
    if (x < m->w - 1) {
        FlagClr(m, x + 1, y, f & 0x111);
    }
    if (y > 0) {
        FlagClr(m, x, y - 1, f & 0x444);
    }
    if (y < m->h - 1) {
        FlagClr(m, x, y + 1, f & 0x888);
    }
}

/* fn_801135C0: second loop registers, row temp */
void fn_801135C0(Map* m) {
    int i;
    int j;
    for (i = m->x0; i < m->x1; i++) {
        m->flags[(s8)i + (m->y0 << 6)] = (m->flags[(s8)i + (m->y0 << 6)] & ~0x808) | 0x80;
        m->flags[(s8)i + ((s8)(m->y1 - 1) << 6)] = (m->flags[(s8)i + ((s8)(m->y1 - 1) << 6)] & ~0x404) | 0x40;
    }
    for (j = m->y0; j < m->y1; j++) {
        int t = (s8)j << 6;
        m->flags[m->x0 + t] = (m->flags[m->x0 + t] & ~0x101) | 0x10;
        m->flags[(s8)(m->x1 - 1) + t] = (m->flags[(s8)(m->x1 - 1) + t] & ~0x202) | 0x20;
    }
}

/* fn_80113BB4: v register (r7, reused from m->w) */
void fn_80113BB4(Map* m) {
    int x;
    int y;
    for (y = 0; y < m->h; y++) {
        for (x = 0; x < m->w; x++) {
            u16 v;
            int a = x == 0 ? 0x10 : 1;
            int b = y == 0 ? 0x80 : 8;
            v = a | b;
            v = v | (x == m->w - 1 ? 0x20 : 2);
            v = v | (y == m->h - 1 ? 0x40 : 4);
            m->flags[(s8)x + ((s8)y << 6)] = v;
        }
    }
    fn_8017F464(m->border, 0xF000F0, 0x80);
}

/* fn_80112F64: second loop e/temp registers swapped */
int fn_80112F64(UnitH* u) {
    int n = 0;
    {
        PairEnt* e;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                n++;
            }
        }
    }
    {
        PairEnt* e = lbl_803EC418;
        int i;
        for (i = 0; i < lbl_804CB800; i++, e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                n++;
            }
        }
    }
    return n;
}

/* fn_80112FFC: second loop e/temp registers swapped */
void* fn_80112FFC(UnitH* u, int k) {
    int n = 0;
    {
        PairEnt* e;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                if (k == n++) {
                    if (u->ec == e->a) {
                        return e->b;
                    }
                    return e->a;
                }
            }
        }
    }
    {
        PairEnt* e = lbl_803EC418;
        int i;
        for (i = 0; i < lbl_804CB800; i++, e++) {
            if (e->c == 1 && (u->ec == e->a || u->ec == e->b)) {
                if (k == n++) {
                    if (u->ec == e->a) {
                        return e->b;
                    }
                    return e->a;
                }
            }
        }
    }
    return 0;
}

/* fn_801130D4: second loop e/temp registers swapped */
void fn_801130D4(void* a, void* b, u32 c, u8 d) {
    int n;
    int found = 0;
    {
        PairEnt* e;
        for (e = lbl_804CB7E4; e->a; e++) {
            if (e->c == c) {
                if ((a == e->a && b == e->b) || (a == e->b && b == e->a)) {
                    found = 1;
                    break;
                }
            }
        }
    }
    n = lbl_804CB800;
    {
        PairEnt* e = lbl_803EC418;
        int i;
        for (i = 0; !found && i < n; i++, e++) {
            if (e->c == c) {
                if ((a == e->a && b == e->b) || (a == e->b && b == e->a)) {
                    found = 1;
                    break;
                }
            }
        }
    }
    if (!found && n < 0x60) {
        PairEnt* e = &lbl_803EC418[n];
        e->a = a;
        e->b = b;
        e->c = c;
        e->d = d;
        lbl_804CB800++;
    }
}

/* fn_801161B0: register colouring only; same instructions */
void fn_801161B0(Map* m, u32 dir, int dx, int dy) {
    int t = (dir & 0xf) << 4;
    MapNode* n = m->head;
    u8 y0 = n->y;
    u8 x0 = n->x;
    int ny = dy + y0;
    int nx = dx + x0;
    int i = (s8)x0 + ((s8)y0 << 6);
    u16 f = m->flags[i];
    u16 c;
    int j;
    if (t & f) {
        return;
    }
    if (!(dir & f)) {
        return;
    }
    j = (s8)nx + ((s8)ny << 6);
    c = *(s16*)&m->cur[i] + 1;
    if (c >= m->cur[j]) {
        return;
    }
    if (c > m->limit) {
        return;
    }
    m->tail->x = nx;
    m->tail->y = ny;
    m->tail->dir = dir;
    m->tail->cost = c;
    m->tail++;
    m->count++;
    m->cur[j] = c;
    if (c >= m->unk2623C) {
        m->g4[j] = 1;
    }
}

/* fn_80126B0C: TeamIs || chain is 3 words off; ours folds the contiguous compares */
u8 fn_80126B0C(Unit* u) {
    if (*(u32*)fn_80060728(lbl_803CAB38) & 3) {
        return 0xff;
    }
    if (u->team[8] == 1 || u->team[8] == 2 || u->team[8] == 3) {
        return 0xff;
    }
    return u->ff;
}

/* fn_80126C28: add into r3 then addi back to r31; ours adds in place */
u8 fn_80126C28(Unit* u) {
    int r = u->gauge;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        s8 v = u->gauge;
        if (v >= 30) {
            r += fn_8010ECA0();
        } else {
            BOOL m = 0;
            if (v >= 15 && v < 30) {
                m = 1;
            }
            if (m) {
                r += fn_8010EC08();
            }
        }
    } else if (fn_8011B77C(u->skills, lbl_804CA4E4)) {
        int t = fn_8010ECA0();
        r = t + r + 0x28;
    } else if (fn_8011B77C(u->skills, lbl_804CA4E0)) {
        int t = fn_8010EC08();
        r = t + r + 0x14;
    }
    if (r > 0xff) {
        r = 0xff;
    }
    if (r < 0) {
        r = 0;
    }
    return r;
}

/* fn_80126F34: abs: register order */
u8 fn_80126F34(Unit* a, Unit* b) {
    int dy = __abs(a->y - b->y);
    int dx = __abs(a->x - b->x);
    return dx + dy;
}

/* fn_80120F50: r3/r4 swap in the inlined gauge check */
int fn_80120F50(Unit* u) {
    if (!fn_80120CAC_i(u)) {
        return -1;
    }
    return HeroId(u, 0x42, 0x44, 0x43, 0x44);
}

/* fn_80121080: r3/r4 swap in the inlined gauge check */
int fn_80121080(Unit* u) {
    if (!fn_80120CAC_i(u)) {
        return -1;
    }
    return HeroId(u, 0x45, 0x47, 0x46, 0x47);
}

/* fn_80127650: only u (r29 vs r28) and promo swapped; u is reused as r */
BOOL fn_80127650(Unit* u, void* x) {
    u8* promo;
    promo = 0;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        promo = (u8*)u->job->promoted;
    }
    switch ((u8)fn_8010B260(x)) {
    case 1: {
        Person* p = u->person;
        return p == fn_8010B1D8(x);
    }
    case 2: {
        Job* j = u->job;
        BOOL r = 1;
        if (j != fn_8010B200(x)) {
            BOOL t = 0;
            if (promo && promo == fn_8010B200(x)) {
                t = 1;
            }
            if (!t) {
                r = 0;
            }
        }
        return r;
    }
    case 3: {
        u8 tbl[0x18];
        int i;
        if (fn_801059B0() && fn_8010536C(fn_801059B0(), x) >= 0) {
            return 1;
        }
        fn_8010E41C(tbl, 4);
        for (i = 1; i <= 0xfe; i++) {
            Unit* v = UnitGet(i);
            if (v->person && tbl[v->team[8]]) {
                if ((s8)fn_8012C9BC(v, fn_8010B228(x)) >= 0) {
                    return 1;
                }
            }
        }
        return 0;
    }
    case 9:
        return fn_8011B77C(u->skills, x);
    case 10: {
        BOOL r = 0;
        if (fn_801109B8((u8*)u->job + 0xee, x) || (promo && fn_801109B8(promo + 0xee, x))) {
            r = 1;
        }
        return r;
    }
    }
    return 0;
}

/* fn_80127B68: loop index / flags registers swapped */
Unit* fn_80127B68(Unit* u) {
    u8 tbl[5];
    u32 f;
    int i;
    fn_8010E41C(tbl, 5);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person) {
            u8* t = v->team;
            if (tbl[t[8]]) {
                f = v->flags10C;
                if ((f & 0x100) && !(f & 8) && t == u->team && u->fd == v->fd) {
                    return v;
                }
            }
        }
    }
    return 0;
}

/* fn_80127CA0: loop index / flags registers swapped */
Unit* fn_80127CA0(Unit* u) {
    u8 tbl[5];
    u32 f;
    int i;
    if (u->u117 == 0) {
        return 0;
    }
    fn_8010E41C(tbl, 0);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person) {
            u8* t = v->team;
            if (tbl[t[8]]) {
                f = v->flags10C;
                if ((f & 0x4000000) && !(f & 8) && t == u->team && u->u117 == v->u117) {
                    return v;
                }
            }
        }
    }
    return 0;
}

/* fn_8011D17C: hash char register order */
void fn_8011D17C(void) {
    u8* t = fn_8010B240(0);
    u32* d = lbl_80413098;
    int i;
    for (i = 0; i < 0xc7; i++) {
        *d = StrHash(*(char**)t);
        d++;
        t += 0x10;
    }
}

/* fn_8011D1E4: hash char register order */
u8 fn_8011D1E4(const char* s) {
    return TerrainId(StrHash(s));
}

/* fn_8011EFC8: less-than idiom operands */
BOOL fn_8011EFC8(Unit* a, Unit* b) {
    int y = fn_80123BF0(b);
    int x = fn_80123BF0(a);
    return y > x;
}

/* fn_8011F428: name / table walker registers swapped (7 words) */
BOOL fn_8011F428(Unit* u) {
    u8* cfg = fn_8006074C(&lbl_803CAB38);
    const char* name = lbl_80369010 + 0xa;
    if (flagGet(&lbl_803CAB38, name)) {
        return 0;
    }
    {
        BOOL r;
        switch (u->b380) {
        case 5:
        case 7:
        case 8:
        case 9:
        case 10:
            r = 1;
            break;
        default:
            r = 0;
            break;
        }
        if (r) {
            return 1;
        }
    }
    if (fn_8011B77C(u->skills, lbl_804CA598)) {
        return 1;
    }
    return (((u8*)u->person)[0xe0] & (cfg[0x8e] & 0x1f)) != 0;
}

/* fn_80117F74: while(1) keeps a dead blr at the end; all other words equal */
void fn_80117F74(const char* s, u8* d) {
    while (1) {
        switch (*s) {
        case 0:
            *d = 0x40;
            return;
        case '4':
            *d = 1;
            break;
        case '8':
            *d = 8;
            break;
        case '6':
            *d = 2;
            break;
        case '2':
            *d = 4;
            break;
        }
        s++;
        d++;
    }
}

/* fn_80116CFC: loop index registers; hand abs for dy, __abs for dx */
void fn_80116CFC(Map* m, s8 cx, s8 cy, s8 r) {
    int y;
    int x;
    for (y = 0; (s8)y < m->h; y++) {
        int dy = (s8)y - cy;
        for (x = 0; (s8)x < m->w; x++) {
            int a = dy < 0 ? -dy : dy;
            if (__abs((s8)x - cx) + a <= r) {
                m->ter[2][x + (y << 6)] = 1;
            }
        }
    }
}

/* fn_8012A850: second loop registers, first loop uses add of an offset */
void fn_8012A850(Unit* u) {
    Inv t[7];
    fn_80111B34(&t[0]);
    fn_80111B34(&t[1]);
    fn_80111B34(&t[2]);
    fn_80111B34(&t[3]);
    fn_80111B34(&t[4]);
    fn_80111B34(&t[5]);
    fn_80111B34(&t[6]);
    {
        int n = 0;
        Inv* it = u->inv;
        int i;
        for (i = 0; i < 7; i++) {
            if (it->item) {
                fn_80111C78(&t[n], it);
                n++;
                fn_80110D38(it);
            }
            it++;
        }
    }
    {
        Inv* it = t;
        int i;
        for (i = 0; i < 7; i++) {
            if (it->item == 0) {
                break;
            }
            fn_801116B8(it);
            fn_80111C78(&u->inv[(u8)i], it);
            it++;
        }
    }
    fn_80111C24(&t[6], -1);
    fn_80111C24(&t[5], -1);
    fn_80111C24(&t[4], -1);
    fn_80111C24(&t[3], -1);
    fn_80111C24(&t[2], -1);
    fn_80111C24(&t[1], -1);
    fn_80111C24(&t[0], -1);
}

/* fn_8012A9A4: needs lwzu: the source walks a pointer */
BOOL fn_8012A9A4(Unit* u) {
    Inv* it;
    if (u->inv[0].item && u->inv[0].bit40) {
        return 1;
    }
    it = &u->inv[1];
    if (it[0].item && it[0].bit40) {
        return 1;
    }
    if (it[1].item && it[1].bit40) {
        return 1;
    }
    if (it[2].item && it[2].bit40) {
        return 1;
    }
    if (it[3].item && it[3].bit40) {
        return 1;
    }
    if (it[4].item && it[4].bit40) {
        return 1;
    }
    if (it[5].item && it[5].bit40) {
        return 1;
    }
    return 0;
}

/* fn_8012C398: uses index*2 temp; needs mr r0,r3 argument copy */
BOOL fn_8012C398(Unit* u, u8 i) {
    s16 old = fn_8012C0A8(u, i, u->s2D4[i]);
    s16 now = fn_8012C0A8(u, i, (s16)fn_80111488(old));
    int a;
    int b;
    u->s2D4[i] = now;
    a = (s16)fn_80111230(old);
    b = (s16)fn_80111230(now);
    return a != b;
}

/* fn_8012D3EC: loop index / off register order, g vs r */
void fn_8012D3EC(void* r) {
    u8* g = fn_8024BCA0();
    int n;
    {
        int off = 0;
        int i;
        for (i = 0; i < 0xb; i++) {
            fn_8010DF10((u8*)lbl_804CB814 + off, (u8)i);
            off += 0xc;
        }
    }
    {
        int off = 0;
        int i;
        for (i = 0; i < 0xfe; i++) {
            fn_801221E8((Unit*)((u8*)lbl_804CB810 + off), i + 1);
            fn_8010E168(&lbl_804CB814[4], (Unit*)((u8*)lbl_804CB810 + off));
            off += 0x3f0;
        }
    }
    n = 0xfe;
    if (*(u32*)(g + 0xc) < 0xb) {
        n = 0x9f;
    }
    {
        int i;
        for (i = 0; i < n; i++) {
            fn_8010E27C(&lbl_804CB814[4], &lbl_804CB810[i]);
            if (!fn_80121A28(&lbl_804CB810[i], r)) {
                fn_8010E168(&lbl_804CB814[4], &lbl_804CB810[i]);
            }
        }
    }
    {
        int i;
        for (i = 0; i < 0xb; i++) {
            if (i != 4) {
                fn_8010DF24(&lbl_804CB814[i]);
            }
        }
    }
    {
        int i;
        for (i = 0; i < n; i++) {
            Unit* u = &lbl_804CB810[i];
            if (u->prev == 0 && u->next == 0) {
                fn_8010E168(&lbl_804CB814[u->team[8]], u);
            }
        }
    }
}

/* fn_8012CC80: only register order around the second loop */
void fn_8012CC80(void) {
    Unit* u = lbl_804CB814[0].tail;
    int i;
    int off;
    while (u) {
        Unit* p = u->prev;
        fn_8011FDD8(u, 5);
        u = p;
    }
    off = 0;
    for (i = 0; i < 0xfe; i++) {
        Unit* v = (Unit*)((u8*)lbl_804CB810 + off);
        if (v->person) {
            switch (v->team[8]) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
                fn_8010E27C(&lbl_804CB814[v->team[8]], v);
                fn_801221E8(v, -1);
                fn_8010E168(&lbl_804CB814[4], v);
            }
        }
        off += 0x3f0;
    }
    {
        u8 a[] = {5, 7, 8, 9, 10, 0xff};
        u8 tbl[0xb];
        memset(tbl, (u8)lbl_804CA710, 0xb);
        SideSet(tbl, a);
        for (i = 1; i <= 0xfe; i++) {
            Unit* v = UnitGet(i);
            if (v->person && tbl[v->team[8]]) {
                fn_80126EB0(v, 0, 0);
            }
        }
    }
    fn_8010DF10(&lbl_804CB814[0], 0);
    fn_8010DF10(&lbl_804CB814[1], 1);
    fn_8010DF10(&lbl_804CB814[2], 2);
    fn_8010DF10(&lbl_804CB814[3], 3);
}

/* fn_8012E944: person->dc reloaded in the loop by the original; ours hoists it */
s8 fn_8012E944(Unit* u, void* pid) {
    Person* p = u->person;
    int r = -1;
    int i;
    for (i = 0; i < SupCount(p); i++) {
        if (SupAt(p, i) == pid) {
            return (s8)i;
        }
    }
    return r;
}

/* fn_8012E9B4: person->dc reloaded in the loop by the original; ours hoists it */
s8 fn_8012E9B4(Unit* a, Unit* b) {
    return SupIdx(a->person, b->person);
}

/* fn_8012EA2C: registers and return layout of the inlined support check */
BOOL fn_8012EA2C(Unit* u, int i) {
    SupCfg* c;
    SupData* d;
    SupItem* e;
    u8 v;
    if (i < 0) {
        return 0;
    }
    d = SupOf(u->person);
    if (d == 0) {
        return 0;
    }
    c = lbl_804CB808;
    e = &d->e[i];
    if (e == 0) {
        return 0;
    }
    v = SupVal(u, i);
    if (v == c->lv[0] || v == c->lv[1] || v == c->lv[2]) {
        return 1;
    }
    return 0;
}

/* fn_8012E854: all words equal; ours has a dead blr after the tail call */
Unit* fn_8012E854(Unit* u, int i) {
    if (i < 0) {
        return 0;
    }
    return fn_8012CECC(SupPid(u, i));
}

/* fn_8012F5CC: clrlwi r4,r4 in place */
void fn_8012F5CC(Cam* c, int m) {
    c->mode = m = m & 3;
    c->a.z = c->v4();
}

/* fn_80120378: second switch comparison order (8 words) */
int fn_80120378(Unit* u) {
    switch (*(u32*)fn_80060728(&lbl_803CAB38) & 3) {
    case 1:
        return 0;
    case 2:
        return 0x64;
    }
    if (u->hp == 0) {
        return 0;
    }
    switch (u->team[8]) {
    case 0:
        break;
    case 1:
        return 0;
    case 2:
    case 3:
        return 0x64;
    case 4:
        break;
    }
    if (fn_80126B0C(u) == 0xff) {
        return 0;
    }
    {
        s8 g;
        int m = (u->job->fb - 1) * 100;
        int v;
        if (CanPromote(u)) {
            m += 100;
        }
        {
            int e;
            g = u->gauge;
            e = fn_80126B0C(u);
            v = m - (e + (g - 1) * 100);
        }
        if (v < 0) {
            v = 0;
        }
        return v;
    }
}

/* fn_80124BC0: abs sum operand order, same as fn_80126F34 */
int fn_80124BC0(Unit* u, Unit** out) {
    u8 tbl[0xb];
    Unit* v;
    Unit** w = out;
    int n = 0;
    int i;
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        v = UnitGet(i);
        if (v->person && tbl[v->team[8]]) {
            u8 d = __abs(u->y - v->y) + __abs(u->x - v->x);
            if (d <= 3 && d >= 1 && HAS(v, lbl_804CA6B8) && fn_8010E398(u->team, v->team) == 1) {
                if (out) {
                    *w = v;
                }
                w++;
                n++;
            }
        }
    }
    return n;
}

/* fn_801246A4: pool r31 / person r30 registers swapped; instructions otherwise equal */
char* fn_801246A4(Unit* u) {
    char* pool;
    char* r;
    Person* p;
    pool = lbl_80369088;
    r = 0;
    p = u->person;
    if (p == fn_8010B1D8(pool + 0xa)) {
        if (HAS(u, lbl_804CA4E4)) {
            r = pool + 0x12;
        } else if (HAS(u, lbl_804CA4E0)) {
            r = *(char**)((u8*)u->person + 0x10);
        }
    } else {
        p = u->person;
        if (p == fn_8010B1D8(pool + 0x1b)) {
            if (HAS(u, lbl_804CA4E4)) {
                r = pool + 0x27;
            } else if (HAS(u, lbl_804CA4E0)) {
                r = pool + 0x34;
            } else {
                r = *(char**)((u8*)u->person + 0x10);
            }
        } else {
            p = u->person;
            if (p == fn_8010B1D8(pool + 0x41)) {
                if (HAS(u, lbl_804CA4E4)) {
                    r = pool + 0x4b;
                } else if (HAS(u, lbl_804CA4E0)) {
                    r = *(char**)((u8*)u->person + 0x10);
                }
            } else {
                p = u->person;
                if (p == fn_8010B1D8(pool + 0x56)) {
                    if (HAS(u, lbl_804CA5A8)) {
                        r = pool + 0x62;
                    } else {
                        r = *(char**)((u8*)u->person + 0x10);
                    }
                } else {
                    p = u->person;
                    if (p == fn_8010B1D8(pool + 0x6f)) {
                        if (HAS(u, lbl_804CA5A8)) {
                            r = pool + 0x77;
                        } else {
                            r = *(char**)((u8*)u->person + 0x10);
                        }
                    } else {
                        r = *(char**)((u8*)u->person + 0x10);
                    }
                }
            }
        }
    }
    return r;
}

/* fn_80113794: add/lhz register swap only (5 places); statement forms tried: 7 */
void fn_80113794(Map* m, s8 x, s8 y, u32 f) {
    FlagOr(m, x, y, f);
    if (x > 0) {
        FlagOr(m, x - 1, y, f & 0x222);
    }
    if (x < m->w - 1) {
        FlagOr(m, x + 1, y, f & 0x111);
    }
    if (y > 0) {
        FlagOr(m, x, y - 1, f & 0x444);
    }
    if (y < m->h - 1) {
        FlagOr(m, x, y + 1, f & 0x888);
    }
}

/* fn_80113890: add/lhz register swap only (5 places); statement forms tried: 7 */
void fn_80113890(Map* m, s8 x, s8 y, u32 f) {
    FlagClr(m, x, y, f);
    if (x > 0) {
        FlagClr(m, x - 1, y, f & 0x222);
    }
    if (x < m->w - 1) {
        FlagClr(m, x + 1, y, f & 0x111);
    }
    if (y > 0) {
        FlagClr(m, x, y - 1, f & 0x444);
    }
    if (y < m->h - 1) {
        FlagClr(m, x, y + 1, f & 0x888);
    }
}

