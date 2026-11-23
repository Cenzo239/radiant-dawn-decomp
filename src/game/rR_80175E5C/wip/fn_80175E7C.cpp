/* fn_80176B0C: 5 of 18 words differ */
f32 fn_80176B0C(f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dy = y1 - y0;
    f32 dx = x1 - x0;
    f32 d = dx * dx + dy * dy;
    if (0.0f == d) return 0.0f;
    return (f32)fn_80295CF0(d);
}

/* fn_80177418: 2 of 17 words differ */
void fn_80177418(u8* o, void* parent) {
    F(fn_80081050(lbl_80387A40, parent), u8*, 0x30) = o;
    int* q = &F(o, int, 0x30);
    int v = *q;
    *q = v + 1;
}

/* fn_80179660: 16 of 44 words differ */
u8* fn_80179660(u8* p) {
    F(p, void*, 0x28) = lbl_80387C60;
    F(p, void*, 0) = fn_8001D3EC(lbl_8036B4C8, 0x80);
    F(p, s16, 0x12) = 0;
    F(p, s16, 0x14) = 0;
    F(p, s16, 0x16) = 0;
    F(p, s16, 0x18) = 0;
    F(p, f32, 4) = 0.0f;
    F(p, f32, 8) = 0.0f;
    F(p, f32, 0xC) = 0.0f;
    F(p, int, 0x20) = 0;
    F(p, int, 0x24) = 0;
    p[0x1A] = 0xFF;
    Color c(lbl_804CA7C0, lbl_804CA7C1, lbl_804CA7C2, lbl_804CA7C3);
    SetCol(p, c);
    return p;
}

/* fn_8017948C: 84 of 87 words differ */
u8* fn_8017948C(u8* p, s8 kind) {
    F(p, int, 0x4C) = 0;
    F(p, int, 0x50) = 0;
    F(p, int, 0x34) = 0;
    F(p, int, 0x54) = 0;
    p[0x5D] = 1;
    p[0x5C] = 1;
    F(p, int, 0x58) = 0x30;
    F(p, f32, 0x3C) = 0.0f;
    F(p, f32, 0x40) = 0.0f;
    F(p, f32, 0x44) = 0.0f;
    F(p, f32, 0x48) = 1.0f;
    Color c(lbl_804CE4B8[0], lbl_804CE4B8[1], lbl_804CE4B8[2], lbl_804CE4B8[3]);
    p[0x5E] = c.r;
    p[0x5F] = c.g;
    p[0x60] = c.b;
    p[0x61] = c.a;
    p[0x39] = 0xFF;
    p[0x38] = kind;
    switch (kind) {
    case 0:
        F(p, void*, 0x30) = fn_800E4060(lbl_8036B4C8 + 0x2F, 4);
        F(p, f32, 0x48) = 0.05f;
        break;
    case 1:
        F(p, void*, 0x30) = fn_800E4060(lbl_8036B4C8 + 0x2F, 4);
        F(p, f32, 0x48) = 0.025f;
        break;
    case 2:
        F(p, void*, 0x30) = fn_800E4060(lbl_8036B4C8 + 0x3A, 4);
        F(p, f32, 0x48) = 0.05f;
        break;
    default:
        F(p, void*, 0x30) = NULL;
        break;
    }
    u8* o = F(p, u8*, 0x30);
    if (o != NULL) {
        u8* q = F(o, u8*, 0x30);
        F(q, int, 0x18) |= 0x101C;
    }
    return p;
}

/* fn_8017E30C: 5 of 41 words differ */
void fn_8017E30C(u8* p) {
    u8* a = F(p, u8*, 0x64);
    if (a != NULL && F(p, int, 0x68) != 0) {
        fn_80010F94(a);
        if ((int)p[0x54] != 0) {
            u8* q = F(p, u8*, 0x64);
            q[2] = p[0x59];
            q[3] = p[0x5A];
            q[4] = p[0x5B];
            q[5] = p[0x5C];
            u8* r = F(p, u8*, 0x6C);
            if (r != NULL) {
                r[4] = p[0x5D];
                r[5] = p[0x5E];
                r[6] = p[0x5F];
                r[7] = p[0x60];
            }
        }
    }
}

