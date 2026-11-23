/* fn_8026FC38: 25 words. Clamp of a copied rect; x clamp should run through r0 and the final subtractions come in another order. */
struct Rect16 { s16 x, y, w, h; };

void fn_8026FC38(void*, Rect16* r) {
    Rect16 c = *r;
    int v = c.x;
    if (v < 0) {
        v = 0;
    } else if (v > 0x7FF) {
        v = 0x7FF;
    }
    c.x = v;
    c.y = c.y < 0 ? 0 : (c.y > 0x7FF ? 0x7FF : c.y);
    c.w = c.w < 0 ? 0 : (c.w > 0x7FF ? 0x7FF : c.w);
    c.h = c.h < 0 ? 0 : (c.h > 0x7FF ? 0x7FF : c.h);
    s16 W = c.w - c.x;
    s16 H = c.h - c.y;
    fn_803080DC(c.x, c.y, W, H);
}

