// fn_800A6DE4: 13/84 words differ (buf at 0x18 not 0x14, colours). fn_800A75E8: 77/98, colours in the two Find154 inlines.
static inline RandSet* Get684(s8** t, int j) {
    int id = (*t)[j];
    if (id < 0) {
        return NULL;
    }
    return (RandSet*)(Data(lbl_804CB684) + id * 0x14);
}

static inline Named4* Get680(RandSet* s, int j) {
    int v = s->ids[j];
    if (v < 0) {
        return NULL;
    }
    return (Named4*)(Data(lbl_804CB680) + v * 0xC);
}

#pragma push
#pragma use_lmw_stmw on
void fn_800A6DE4(Lookups2* l, int i) {
    char buf[0x40];
    int n;
    TBL_COUNT(n, lbl_804CB67C);
    for (int c = 0; c < n; c++) {
        RandSet* s = Get684(&l->t[i], c);
        if (s != NULL) {
            int m = s->n;
            for (int j = 0; j < m; j++) {
                Named4* e = Get680(s, j);
                if (e != NULL) {
                    if (MakePath(e, buf) != NULL) {
                        fn_8023F1A0(buf, 0x40);
                    }
                }
            }
        }
    }
}
#pragma pop

void* fn_800F416C(void*);
struct Rule {
    u8 pad[0xC];
    const char* a;
    const char* b;
};
Rule* fn_800A7770(void*, void*, void*);

struct UnitChr {
    u8 pad[0xEC];
    void** ec;
    void** f0;
};

static inline Entry154* Find154(const char* name) {
    if (name == NULL) {
        return NULL;
    }
    int n;
    Entry154* e;
    int i;
    TBL_COUNT(n, lbl_804CB650);
    TBL_DATA(e, Entry154, lbl_804CB650);
    for (i = 0; i < n; i++, e++) {
        if (fn_80291188(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

Entry154* fn_800A75E8(UnitChr* u, int flag) {
    void* x = *u->ec;
    void* y = *u->f0;
    Rule* r = fn_800A7770(y, x, fn_800F416C(u));
    if (r == NULL) {
        return NULL;
    }
    if (flag) {
        return Find154(r->b);
    }
    return Find154(r->a);
}
