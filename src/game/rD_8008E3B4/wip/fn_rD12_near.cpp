/* Near misses from round 12. Fragments: each needs the declarations of the file named. */

/* fn_8009AB90 (from ../fn_8009A720.cpp): 1 of 19 words: want fmuls f0,f1,f0 (same open puzzle as fn_8009A3D8). Needs fn_8017FA1C. */
int fn_8009AB90(void)
{
    return (int)(16.666666f * fn_8017FA1C());
}

/* fn_8009EEEC (from ../fn_8009E900.cpp): 22 of 175 words: volatile registers in the unit loop only (want unit r8, table r9, id r10). Uses clearUnitFlags and evAny from ../fn_8009E900.cpp history below. */
int fn_8009EEEC(void* parent)
{
    if (!evAny(1)) {
        return 0;
    }
    if (flagGet(&lbl_803CAB38, lbl_80364B30 + 0x23)) {
        return 0;
    }
    fn_8013F204();
    fn_801856F4();
    clearUnitFlags();
    fn_80114D00(lbl_803EC898);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x134, 0);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x13c, 3);
    fn_8008D75C();
    return evRun(parent, 1, fn_8009EDEC);
}

/* fn_8009F1A8 (from ../fn_8009E900.cpp): 22 of 122 words: same unit loop as fn_8009EEEC. */
int fn_8009F1A8(void* parent)
{
    if (!evAny(2)) {
        return 0;
    }
    fn_8013F204();
    fn_801856F4();
    clearUnitFlags();
    fn_80114D00(lbl_803EC898);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x134, 0);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x13c, 3);
    return evRun(parent, 2, fn_8009EDEC);
}

/* fn_800A0998 (from ../fn_800A04C8.cpp): 3 of 97 words: counter wants r29, ours r28. Inputs from ../fn_800A04C8.cpp. */
void fn_800A0998(int n, void* parent)
{
    /*P*/
    u8* p;
    void* proc;
    u32 h;
    const char* name;
    int i;
    FlagTable* q;
/*E*/
    p = evNth(n);
    lbl_803E50B0.e = 0;
    proc = fn_80081194(lbl_80381B80, parent);
    flagClrBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, lbl_80364B30));
    lbl_804CB700 &= ~1;
    ((RunBits*)&lbl_804CB700)->b4 = 0;
    *(void**)(fn_800C3558() + 0x20) = proc;
    fn_801D0D58(fn_800C3558(), p);
    fn_801D0E18(fn_800C3558());
    if (fn_800C357C() == 0) {
        u8* c = fn_800C3558();
        u8 z = 0;
        *(int*)(c + 0x20) = z;
        lbl_803C8DA0[0xa1] = z;
        fn_80081A90(proc);
    }
}

/* fn_800A15F4 (from ../fn_800A04C8.cpp): 2 of 149 words: id wants r28, ours r27. */
int fn_800A15F4(u8* p)
{
    void* id;
    char* name = fn_8009D948(p, *(u16*)(p + 0x1a));
    if (name != NULL && *name != 0) {
        if (flagHas(&lbl_803CAB38, (const char*)name)) {
            if (flagGet(&lbl_803CAB38, (const char*)name)) {
                return 0;
            }
        } else if (fn_80076F54(name)) {
            fn_801D0C48(fn_800C3558(), lbl_803E50B0.a);
            fn_801D0C48(fn_800C3558(), lbl_803E50B0.b);
            if (!fn_801D0C88(fn_800C3558(), name)) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    if (*(s16*)(p + 0x16) >= 0 && lbl_803E50B0.a != *(s16*)(p + 0x16)) {
        return 0;
    }
    if (*(s16*)(p + 0x18) >= 0 && lbl_803E50B0.b != *(s16*)(p + 0x18)) {
        return 0;
    }
    id = *(void**)(lbl_803CA870.a + 0xec);
    if (id != fn_8010B1D8(fn_8009D948(p, *(u16*)(p + 0x14)))) {
        return 0;
    }
    return 1;
}

/* fn_800A1848 (from ../fn_800A04C8.cpp): 6 of 67 words: volatile registers for the first three stores (want s8 value r6, base r7, zero r9). */
int fn_800A1848(void* parent, int a, int b)
{
    EvProc* q;
    evSet13(a, b);
    if (!evAny13()) {
        return 0;
    }
    evSet13x(a, b);
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = 0x13;
    q->cond = fn_800A15F4;
    return 1;
}

/* fn_8008A070 (from ../fn_80089AA8.cpp): 6 of 32 words: volatile registers around the -(b == a) mask. */
void fn_8008A070(void)
{
    int a = lbl_804CB5B8->v1C();
    int b = lbl_804CB5B8->v24();
    lbl_804CB5E0 = -(b == a) & (lbl_804CB5E0 + 1);
    if ((int)lbl_804CB5E0 >= 0x3c) {
        lbl_804CA3C8 = 0;
    }
}

/* fn_8008A22C (from ../fn_80089AA8.cpp): 59 of 60 words, size 0xFC vs 0xF0: the u64 sum shape is not found yet (original starts addc rN,zero,zero). */
s64 fn_8008A22C(MemStream* s)
{
    s64 a = (s64)sGet(s) << 56;
    a += (s64)sGet(s) << 48;
    a += (s64)sGet(s) << 40;
    a += (s64)sGet(s) << 32;
    a += (s64)sGet(s) << 24;
    a += (s64)sGet(s) << 16;
    a += (s64)sGet(s) << 8;
    return a + sGet(s);
}

/* fn_8008A37C (from ../fn_80089AA8.cpp): 2 instructions: want blt L; b M; L: for the n < 0 test, ours bge M. */
char* fn_8008A37C(MemStream* s, int n)
{
    char* r = (char*)s->cur;
    if (n >= 0) {
    } else {
        n = strlen(r) + 1;
    }
    s->cur += n;
    return r;
}

/* fn_8008AEE4 (from ../fn_80089AA8.cpp): 8 to 13 of 106 words: glyph table wants r8 and mid r4. */
int fn_8008AEE4(const char* s)
{
    /*P*/
    SysFont* f;
    int max;
    int cur;
    const char* p;
    int d;
    int n;
    Glyph* tbl;
    int half;
    Glyph* first;
    Glyph* end;
    u32 code;
/*E*/
    max = 0;
    cur = 0;
    f = &lbl_804CB5E8;
    p = s;
    while (*p != 0) {
        if (*p == 10) {
            if (max < cur) {
                max = cur;
            }
            cur = 0;
            p++;
            continue;
        }
        if ((u16)fn_8031C044() != 1) {
            code = *(u8*)p;
            p++;
        } else {
            d = 0;
            if ((u16)fn_8031C044() == 1) {
                d = isDbcs((u8*)p);
            }
            if (d == 0) {
                code = *(u8*)p;
                p++;
            } else {
                code = *(u16*)p;
                p += 2;
            }
        }
        tbl = lbl_804CB5E8.glyphs;
        end = tbl + f->count;
        first = tbl;
        n = end - first;
        while (n > 0) {
            half = n / 2;
            Glyph* mid = first + half;
            if (mid->code < code) {
                first = mid + 1;
                n -= half + 1;
            } else {
                n = half;
            }
        }
        if (end == first || first->code != code) {
            first = tbl;
        }
        cur += first->width;
    }
    if (max < cur) {
        max = cur;
    }
    return max;
}

