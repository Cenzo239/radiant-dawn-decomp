/* fn_801C8300 (set unit flag): 3/6 words differ, only because the original loads the unit into r4 rather than r3. */
void fn_801C8300(void) {
    ActState* g = &lbl_803CA870;
    u8* u = g->unit;
    *(u32*)(u + 0x108) |= 1;
}

