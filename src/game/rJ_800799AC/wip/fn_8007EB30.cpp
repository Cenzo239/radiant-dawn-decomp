/* Near miss, 12 of 326 words (fragment, needs fn_8007F874.cpp's types). The only
 * difference is at the three culling calls. The original has
 *     cmpwi r30, 0; li r3, 0; li r4, 4; beq L; li r4, 0; L:
 * "li r3, 0" before the branch. "textured ? 0 : 4" becomes a neg/or/srawi/andc mask
 * here, and an if statement puts "li r3, 0" after the label.
 */
void fn_80021C34(int a);
void fn_80021CB4(int a, int b, int c, int d);
void fn_80306054(void* a, void* b);
void fn_80022254(void* tex, int a);
void fn_80021F7C(int a, int b, int c, int d);
u32 fn_80305E0C(void* tex);
u32 fn_80305DF8(void* tex);
int fn_80305E20(void* tex);
void fn_8031292C(f32 a, f32 b, f32 c, void* m);
void fn_80307F10(void* m, int a, int b);
void fn_80021BA4(int a, int b, int c, int d);
void fn_80021EF8(int a, int b);
void fn_80021E20(int a, int b, int c, int d, int e);
void fn_80021D18(int a, int b, int c, int d, int e, int f);
void fn_80021E8C(int a, int b, int c, int d, int e);
void fn_80021D9C(int a, int b, int c, int d, int e, int f);

#define CULL(t)                                                                \
    {                                                                          \
        int id = 0;                                                            \
        int v = 4;                                                             \
        if (t) {                                                               \
            v = 0;                                                             \
        }                                                                      \
        fn_80021EF8(id, v);                                                    \
    }

static inline void texGen(int mtx) {
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, mtx);
    fn_80021CB4(0, 0, 0, 4);
}

static inline void tevStage(int a, int b, int c, int d) {
    fn_80021E20(0, a, b, c, d);
    fn_80021D18(0, 0, 0, 0, 1, 0);
    fn_80021E8C(0, 7, 4, 5, 7);
    fn_80021D9C(0, 0, 0, 0, 1, 0);
}

/* Set GX state for a node's blend flags */
void fn_8007EB30(u16 f, void* tex, void* a, void* b) {
    f32 m[12];
    f32 sy;
    int textured = 1;
    switch (f & 3) {
    case 2:
        textured = 0;
        fn_80021C34(0);
        fn_80021CB4(0, 0xFF, 0xFF, 4);
        break;
    case 0:
        if (f & 0x8000) {
            fn_80306054(a, b);
        }
        fn_80022254(tex, 0);
        texGen(0x3C);
        break;
    case 1:
        if (f & 0x8000) {
            fn_80306054(a, b);
        }
        fn_80022254(tex, 0);
        sy = 1.0f / (f32)(u16)fn_80305E0C(tex);
        fn_8031292C(1.0f / (f32)(u16)fn_80305DF8(tex), sy, 1.0f, m);
        fn_80307F10(m, 0x1E, 1);
        texGen(0x1E);
        break;
    case 3:
        texGen(0x1E);
        break;
    }
    switch (f & 0xF0) {
    case 0x00:
        fn_80021BA4(0, 0, 0, 0);
        CULL(textured);
        break;
    case 0x10:
        fn_80021BA4(1, 4, 5, 0);
        if (textured) {
            switch (fn_80305E20(tex)) {
            case 0:
            case 1:
                tevStage(0xF, 0xF, 0xF, 0xA);
                break;
            default:
                fn_80021EF8(0, 0);
                break;
            }
        } else {
            fn_80021EF8(0, 4);
        }
        break;
    case 0x20:
        fn_80021BA4(1, 4, 1, 0);
        CULL(textured);
        break;
    case 0x30:
        fn_80021BA4(3, 4, 1, 0);
        CULL(textured);
        break;
    case 0x40:
        tevStage(0xF, 0xF, 0xF, 0xA);
        break;
    case 0x50:
        fn_80021BA4(1, 4, 5, 0);
        if (textured) {
            switch (fn_80305E20(tex)) {
            case 0:
            case 1:
                tevStage(0xF, 0xF, 0xF, 0xA);
                break;
            default:
                tevStage(0xF, 0xC, 0xA, 8);
                break;
            }
        } else {
            fn_80021EF8(0, 4);
        }
        break;
    }
}

