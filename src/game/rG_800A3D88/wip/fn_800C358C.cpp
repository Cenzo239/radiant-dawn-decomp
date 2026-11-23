// 1 word short: original has an unreachable `b end` after the first infinite loop. Everything else matches. Needs Swap32/Swap16 from fn_800C358C.cpp.
void fn_800C358C(CmbFile* f, int swapped) {
    if (swapped) {
        for (int i = 0;; i++) {
            CmbCmd* c = f->cmds[i];
            if (c == NULL) {
                return;
            }
            if (c->name != NULL) {
                fn_80076D48(c->name, c);
            }
            continue;
            return;
        }
    } else {
        if (f->m24 != 0) {
            f->m24 += (u32)f;
        }
        if (f->cmds != NULL) {
            f->cmds = (CmbCmd**)((u32)f->cmds + (u32)f);
        }
        f->m20 = lbl_804CB6A6;
        lbl_804CB6A6 += f->m22;
        if (lbl_804CB6A6 > lbl_804CB6A4) {
            lbl_804CB6B8 = 8;
            return;
        }
        for (int i = 0;; i++) {
            if (f->cmds[i] == NULL) {
                return;
            }
            Swap32(&f->cmds[i]);
            f->cmds[i] = (CmbCmd*)((u32)f + (u32)f->cmds[i]);
            CmbCmd* c = f->cmds[i];
            Swap32(&c->name);
            Swap32(&c->name2);
            Swap16(&c->m12);
            Swap16(&c->m10);
            if (c->mc != 0) {
                u16* a = c->args;
                for (int j = 0; j < c->me; j++, a++) {
                    Swap16(a);
                }
            }
            c->file = f;
            if (c->name != NULL) {
                c->name += (u32)f;
                fn_80076D48(c->name, c);
            }
            if (c->name2 != NULL) {
                c->name2 += (u32)f;
            }
        }
    }
}

