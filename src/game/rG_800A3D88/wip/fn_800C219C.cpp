// fn_800C219C, fn_800C31EC: 2/64 each. Address temp gets r0, want r4; the bytes constant is absent here so r0 is free. Needs TWEEN_X from fn_800C1220.cpp.
void fn_800C219C(Title* t) {
    int z = 0;
    int n = 0xE;
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = z;
    u8* a = &t->m36;
    p->p = a;
    p->from = t->m36;
    p->to = z;
    p->t = z;
    p->n = n;
    switch (t->m37) {
    case 0:
        TWEEN_X(t, -0x5E, z, n);
        break;
    case 1:
        TWEEN_X(t, 0x1D4, z, n);
        break;
    }
}

void fn_800C31EC(Title3* t) {
    int z = 0;
    int n = 0xE;
    TweenB* p = (TweenB*)fn_80081194(lbl_80382778, t);
    p->mode = z;
    u8* a = &t->m36;
    p->p = a;
    p->from = t->m36;
    p->to = z;
    p->t = z;
    p->n = n;
    switch (t->m37) {
    case 0:
        TWEEN_X(t, -0x54, z, n);
        break;
    case 1:
        TWEEN_X(t, 0x1EC, z, n);
        break;
    }
}

