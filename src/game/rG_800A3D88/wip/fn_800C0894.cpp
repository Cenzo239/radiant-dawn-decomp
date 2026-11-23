// size 0xEC vs 0xF4: m46 must be reloaded in both flip branches; ours forwards the tested value.
static inline void EffClr(Eff* e, u16 m) {
    e->m46 &= ~m;
}

static inline void EffSet(Eff* e, u16 m) {
    e->m46 |= m;
}

void fn_800C0894(Eff* e) {
    if (e->m34 != NULL) {
        if ((e->m46 & 2) && e->m38 != NULL) {
            if (e->m46 & 8) {
                EffClr(e, 0xC);
            } else {
                EffSet(e, 4);
            }
            EffClr(e, 2);
            if (((EffD2*)e->m38)->m21 & 4) {
                e->m46 &= ~0x10;
                fn_800C1064(e, 0);
                fn_800829CC(e, lbl_803825A8);
            }
            if (e->m40 != NULL) {
                fn_801780B0(e->m40);
                e->m40 = NULL;
            }
            e->m46 &= ~0x40;
            Mdl* m = e->m3c->mdl;
            if (m != NULL) {
                m->flags &= ~8;
            }
        }
    }
}

