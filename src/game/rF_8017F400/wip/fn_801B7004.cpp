/* near miss (not tuned): fn_801B7004, 12 words short; switch needs cases 1, 2 and a range; the mode 2 test has the same `srawi r0,r25,31; or.` shape as wip/fn_801B6B18.cpp. Declarations in ../fn_801B7644.cpp */
void fn_801B7004(LView* p) {
/*P*/
    int y;
    LEnt* e;
    int i;
    f32 x0;
/*E*/
    e = p->ents;
    x0 = 72.0f;
    y = 0x68;
    for (i = 0; i < p->n; i++, y += 0x20, e++) {
        u8* u = e->u;
        f32 fy = (f32)(y - p->x6A);
        if (Vis(p, i)) {
            int col = 1;
            switch (p->x6C) {
            case 1: {
                u32 f = *(u32*)(u + 0x10C);
                if (f & 0x200000) col = 3;
                else if (f & 0x10) col = 0;
                else if (f & 0x10000) col = 0x3F;
                break;
            }
            case 2:
                if (*(u32*)(u + 0x10C) & 0x200000) col = 3;
                else if ((*(u32*)(u + 0x10C) & 0x400000) == 0) col = 0;
                break;
            default:
                if (*(u32*)(u + 0x10C) & 0x200000) col = 3;
                else if (*(u32*)(u + 0x10C) & 0x10000) col = 0x3F;
                break;
            }
            fn_801B5EB4(1, col, fn_80118C44(*(void**)(u + 0xEC)), x0, fy);
        }
    }
    fn_8007E154();
    fn_8007E4E4(526.0f, 32.0f, 300.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E7B4();
    fn_8007E7DC(0xFF);
    fn_8007E164();
    fn_801B6EBC(0, 0, 2, lbl_8036DEB0 + 0x6A, p->x63 + 1);
    fn_801B6EBC(0xC, 0, 2, lbl_8036DEB0 + 0x6D);
    fn_801B6EBC(0x18, 0, 2, lbl_8036DEB0 + 0x6A, p->x6D);
    if (p->x67 < 0) fn_801791D8(p->x48, 4);
    else fn_801791D8(p->x48, 8);
}
