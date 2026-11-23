/* fn_802643B8: 10 words. st should be r30, the page-match flag r29; increments come y, then ofs. */
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_800CB3A8(s16 x, s16 y, u8 a, int b, int c, f32 s, f32 t, const char* f, ...);
void fn_80072ACC(int x, int y, int w, int h, int a, int b, int c);
void fn_800712E8(int x, int y, int a);
const char* fn_80118C44(void* p);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_801C6DA0(f32 x, f32 y, int a, const char* s);

static inline u8 pageSel(DictState* st, int i) { return st->page - i == 0; }

#pragma push
#pragma use_lmw_stmw off
void fn_802643B8(int x, int y) {
    DictState* st = lbl_804CC004;
    int ofs;
    int i;
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    i = 0;
    ofs = 0;
    do {
        int sel = i == st->page;
        fn_800CB3A8(x, y, (u8)sel, 1, 0, 1.0f, 0.0f, fn_800D0864(*(const char**)((u8*)lbl_804306E8.t0 + ofs)));
        i++;
        y += 0x18;
        ofs += 8;
    } while (i < 2);
    if (lbl_804CC004->mode == 0) {
        fn_801BCA5C(-1.0f);
        fn_80072ACC(st->m1A + 0x2E, st->m1C + 0xC, 0xB4, 0x17, 0x19, 0x4B, 1);
        fn_801BCA5C(-1.0f);
        fn_800712E8(st->m1A, st->m1C, 1);
        fn_801BCA5C(2.0f);
    }
    fn_801BCA5C(1.0f);
}
#pragma pop

