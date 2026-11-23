/* fn_8000BC20 (GAnim_Relocate): near miss, 12 of 71 words differ: inside the
 * chunk loop the chunk pointer is r4 instead of r3 (and the temp swapped).
 * Needs the types from ../fn_8000BD3C.c. */
#define RELOC(base, f) if ((base)->f != NULL) { (base)->f = (void*)((u32)(base)->f + (u32)(base)); }

/* GAnim_Relocate */
void fn_8000BC20(GAnim* an) {
    GChunk* c;
    if (an->flags & 8) {
        fn_8001E008(lbl_80360B08, 0x287, lbl_80360B08 + 0x5E);
    }
    RELOC(an, x4);
    RELOC(an, events);
    RELOC(an, x24);
    RELOC(an, x28);
    RELOC(an, x2C);
    if (an->nChunks < 1) {
        an->chunks = NULL;
    }
    if (an->chunks != NULL) {
        c = an->chunks = (GChunk*)((u32)an->chunks + (u32)an);
        while (c != NULL) {
            c->data = (void*)((u32)c->data + (u32)an);
            if ((s32)c->type != 13) {
                ((void**)c->data)[1] = (u8*)c->data + 8;
            }
            if (c->next != NULL) {
                c->next = (GChunk*)((u32)c->next + (u32)an);
            }
            c = c->next;
        }
    }
}

