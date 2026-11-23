/* Uses the MapUnit struct and externs from ../fn_800F3360.c. */
/* fn_800FAE08: 13 of 36 words differ: FP load order / fcmpu operand order. The original loads offX before x and reuses one 0x8 conversion slot; a TileCenter(s8) inline fixes the stack slot but not the order. */
BOOL fn_800FAE08(MapUnit* m) {
    if (0.5f + (f32)m->mapX != m->x + m->offX) {
        return 1;
    }
    return 0.5f + (f32)m->mapY != m->y + m->offY;
}


/* fn_800FAFF0: 4 of 39 words differ: the original loads m->y before m->x (lfs f0,8 / lfs f1,4) and schedules lis 0x4330 between. `int y = m->y; int x = m->x;` locals get closest. */
void fn_800FAFF0(MapUnit* m, int k) {
    if (!(m->flags2 & 0x18)) {
        void* r = fn_800620A8(lbl_803CAB38, (int)m->x, (int)m->y);
        if (k) {
            fn_8012FED4(r);
        }
    }
}

/* fn_800FC5AC: all 10 words match but the original has a dead `blr`
 * after the tail call (size 0x2C vs 0x28). Tried a bare return, a switch,
 * a nested block and a ternary. */
void fn_800FC5AC(MUProc* q) {
    u32 k = q->unk18;
    if (k == 3) {
        k = 0;
    }
    fn_80102928(q->unit, q->unk34, q->unk38, q->flags40, k);
}
