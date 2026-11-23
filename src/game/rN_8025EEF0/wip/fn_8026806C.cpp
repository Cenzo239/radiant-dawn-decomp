/* fn_8026806C: lha scheduled above stwu in the original */
u32 fn_8026806C(SlotMenu* m) {
    int x;
    int y;
    s16 pos[2];
    switch (m->grp) {
    case 0: x = 0x23; y = 0x4C; break;
    case 1: x = 0xE3; y = 0x4C; break;
    case 2: x = 0x1A3; y = 0x4C; break;
    }
    pos[0] = x + (m->idx % 4) * 0x28;
    pos[1] = y + (m->idx / 4) * 0x30;
    return *(u32*)pos;
}

