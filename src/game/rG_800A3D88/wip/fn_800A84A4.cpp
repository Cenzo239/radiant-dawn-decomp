// near miss: 15/74 words, n/e/i register colours and stack slots differ
static inline Entry8* At69C(int i) {
    if (i < 0) {
        return NULL;
    }
    return (Entry8*)Data(lbl_804CB69C) + i;
}

static inline int Index69C(const char* name) {
    if (name == NULL) {
        return 0;
    }
    int n = Count(lbl_804CB69C);
    Entry8* e = (Entry8*)Data(lbl_804CB69C);
    for (int i = 0; i < n; i++, e++) {
        if (fn_80291188(name, e->name) == 0) {
            return i;
        }
    }
    return -1;
}

f32 fn_800A84A4(const char* name) {
    int i = Index69C(name);
    Entry8* p = At69C(i);
    if (p != NULL) {
        return p->v / lbl_804CD2D8;
    }
    return lbl_804CD2C8;
}

