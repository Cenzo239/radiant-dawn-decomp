/* Grows a 32-byte aligned scratch buffer on demand and counts the requests (names guessed). */
extern "C" {
extern int lbl_804CB0A8;  /* buffer */
extern int lbl_804CB0AC;  /* request count */
extern int lbl_804CB0B0;  /* buffer size */
#if TARGET_PC
extern FE10_PROTO void fn_80079978(p32arg);
#else
extern void fn_80079978(int);
#endif
#if TARGET_PC
extern FE10_PROTO p32ret fn_80079940(int, int);
#else
extern int fn_80079940(int, int);
#endif
extern void DCFlushRange(int, int);

void fn_80020E7C(int size)
{
    int a;
    lbl_804CB0AC++;
    a = (size + 0x1F) & ~0x1F;
    if (a > lbl_804CB0B0) {
        if (lbl_804CB0A8 != 0) {
            fn_80079978(lbl_804CB0A8);
        }
        lbl_804CB0B0 = a;
        lbl_804CB0A8 = fn_80079940(a, 0x40);
        DCFlushRange(lbl_804CB0A8, a);
    }
}
}
