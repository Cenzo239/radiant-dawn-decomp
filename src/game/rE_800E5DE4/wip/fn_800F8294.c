/* fn_800F8294: only the instruction order after the fn_801142F0 call
 * differs (1 extra word). The original stores p.z with `stfs f1` first and
 * passes `frsp f3, f0` (a copy) to fn_803128AC; MWCC here rounds first and
 * stores the rounded value. Tried: double local, assignment inside the call,
 * Vec* helper inlines, explicit cast. GX helpers/WGPipe are in
 * ../fn_800F3360.c. */
void fn_800F8294(f32 r) {
    Vec p = {0};
    Mtx a;
    Mtx b;
    p.x = *(f32*)(lbl_803CAB38 + 0x944);
    p.y = *(f32*)(lbl_803CAB38 + 0x948);
    p.z = fn_801142F0(lbl_803EC898, p.x, p.y);
    fn_803128AC(a, p.x, p.y, p.z);
    fn_80312444(fn_8000FB88(), b);
    fn_80312378(a, b, b);
    fn_80312378(fn_8000FB88(), b, b);
    fn_80307E48(b, 0);
    fn_80021784(0);
    fn_80304314(0x98, 0, 4);
    GXPosition3f32(-r, -r, 0.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(r, -r, 0.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-r, r, 0.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(r, r, 0.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXTexCoord2f32(1.0f, 1.0f);
}

