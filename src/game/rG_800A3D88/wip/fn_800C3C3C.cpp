// fn_800C3C3C registers a script command (name, func, nargs). 12/45, volatile register choice only: i r6, e r7, t r8, base r9, n r10.
BOOL fn_800C3C3C(const char* name, void* func, u8 nargs) {
/*PERM*/
    CmbCmd* e = NULL;
    int i = 0;
    CmbCmd* base = lbl_804CB6B0;
    int n = lbl_804CB6AC;
/*ENDPERM*/
    CmbCmd* t = base;
    for (; i < n; t = (CmbCmd*)((u8*)t + 16), i++) {
        if (t->name == NULL) {
            e = (CmbCmd*)((u8*)base + i * 16);
            break;
        }
    }
    s16 k = ++lbl_804CB6AE;
    if (e == NULL || k > n) {
        lbl_804CB6B8 = 9;
        return 0;
    }
    e->name = name;
    e->name2 = (const char*)func;
    e->file = NULL;
    e->md = nargs;
    e->mc = 0;
    fn_80076D48(name, e);
    return 1;
}

