/*
 * fn_80094130: size 0x60, want 0x6C; 22 of 24 words differ. The original has an unreachable
 * `b; stb r0, 0x15(r1)` after the ctor stores, probably a folded conditional in an inlined
 * Ref constructor. Three constructor shapes tried, none reproduces it.
 */
struct Ref {
    void* p;
    u8 kind;
    u8 flag;
    Ref() { p = 0; kind = 2; flag = 0; }
};

void fn_8004B03C(void* u, Ref r, void* proc);

void fn_80094130(UnitProc* proc)
{
    Ref r;
    r.p = proc->data;
    r.flag = proc->data[0x20] == 0;
    fn_8004B03C(proc->unit, r, proc);
}
