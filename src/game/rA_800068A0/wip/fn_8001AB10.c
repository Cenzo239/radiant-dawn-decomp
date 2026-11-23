/* fn_8001AB10: near miss, 8 of 72 words differ. Depends on types and helpers from ../fn_80017D6C.c; goes there in address order. */
int fn_8001AB10(void) {
    u8* buf = fn_80020E74();
    u8* p = buf + fn_8030585C(0x130, 0xE0, 6, 0, 0);
    if (buf == 0) {
        return 0;
    }
    {
        int sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        sz += fn_8030585C(0x260, 0x1C0, 6, 0, 0);
        if (sz > fn_80020EFC()) {
            return 0;
        }
    }
    {
        u32 z = 0;
        fn_80304C74((GColor*)&z, 0xFFFFFF);
    }
    fn_8001F4D8(0, 0, 0x260, 0x1C0, -1, -1, p, 6, 1);
    setClear(fn_8002177C());
    return 1;
}
