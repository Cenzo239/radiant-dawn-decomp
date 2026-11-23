/*
 * fn_80092E10: 2 of 10 words differ. The original schedules `lwz r3, 0x90(r3)` before `stw r0,
 * 0x14(r1)`. Tried every installed compiler, other -O and -proc flags, an inline wrapper, bool
 * and int callee returns. The callee returns wider than u8: declare int fn_801194FC(void*).
 * Uses struct Obj90 { u8 pad[0x90]; void* p90; }.
 */
u8 fn_80092E10(Obj90* p)
{
    return fn_801194FC(p->p90);
}

/*
 * fn_80092F74: 8 of 68 words differ, all a swap of r4/r5 (want counter r4, slot pointer r5).
 * Same flag helpers as fn_80092E38 in ../fn_80092D04.cpp.
 */
int fn_80092F74(char* name)
{
    int i;
    if (flagFind(&lbl_803CAB38, name) < 0) {
        for (i = 0x7f; i >= 0; i--) {
            if (!flagSlotUsed(&lbl_803CAB38, i)) {
                lbl_803CAB38.names[i] = name;
                lbl_803CAB38.hashes[i] = fn_80076D18(name);
                break;
            }
        }
    }
    return 1;
}

/*
 * fn_80093084: 7 of 62 words differ. The original loads name[0] after the register saves; ours
 * loads it right after stw r0. Tried a flagGet inline. Needs flagFind and flagGetBit from
 * ../fn_80092D04.cpp.
 */
BOOL fn_80093084(const char* name)
{
    if (*name == '\0') {
        return 0;
    }
    return flagGetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, name));
}

