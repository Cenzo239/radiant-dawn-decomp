/* Near misses from fn_80077360.cpp (fragments; SEEK is the macro there).
 * fn_80077A58: 16 of 98: font pointer should be r5 and the u16 key r4, swapped here.
 * fn_800776F8: 3 of 108: lbz r30,1(r3) then lbz r3,0(r3); here the first byte loads first into r6.
 * fn_80077D44: 3 of 27: wants srwi r4; addi r0,r4,1; add r3,r3,r0, but ptr + flag + 1 is always
 * reassociated (about 20 spellings tried).
 */
int fn_80077A58(const u8* s) {
/*P*/
    Font* f;
    int half2;
    Glyph* b;
    Glyph* e;
    Glyph* first;
    Glyph* mid;
    Glyph* first2;
    Glyph* mid2;
    int len;
    int code;
    int len0;
    int half;
    int key2;
    FontHdr* d;
/*E*/
    f = lbl_804CB598;
    if (isSjis(s)) {
        code = (((u8*)s)[0] << 8) | ((u8*)s)[1];
    } else {
        code = ((u8*)s)[0];
    }
    SEEK(f, code)
    return f->cur->adv;
}

u8* fn_800776F8(const u8* s, int* adv) {
/*P*/
    Font* f;
    int half2;
    Glyph* b;
    Glyph* e;
    Glyph* first2;
    u8* n;
    Glyph* first;
    int half;
    Glyph* mid;
    int len;
    Glyph* mid2;
    int code;
    int key2;
    u16 key;
    int len0;
/*E*/
    f = lbl_804CB598;
    if (isSjis(s)) {
        code = ((u8*)s)[1] | (((u8*)s)[0] << 8);
        n = (u8*)s + 2;
    } else {
        code = ((u8*)s)[0];
        n = (u8*)s + 1;
    }
    SEEK(f, code)
    *adv = f->cur->adv;
    return n;
}


const u8* fn_80077D44(const u8* s) {
    return s + ((isSjis(s) != 0) + 1);
}
