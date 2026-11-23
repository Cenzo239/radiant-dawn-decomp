/* fn_8000FD20: 7-8 words differ (float register allocation of the
 * fovy*0.5 / 0.9*far prologue). It sits in GCamera (fn_8000F48C.cpp) right
 * after fn_8000FBA0, which matches with the same shape using 1.1f * near and
 * `c->fovy / 2.0f`. Paste it back there to test. */
/* GCamera_GetFarPlaneMtx: same as fn_8000FBA0 but at 0.9 * far. */
Mtx* fn_8000FD20(GCamera* c, Mtx out) {
    Mtx tmp;
    Mtx scale;
    Mtx inv;
    Mtx trans;
    Vec eye;
    Vec at;
    Vec dir;
    f32 dist;
    f32 aspect;
    f32 h;
    f32 sx;
    f32 sy;
    if (c == NULL) {
        c = lbl_804CB080;
    }
    dist = 0.9f * c->far;
    aspect = c->aspect;
    h = dist * (f32)fn_80295A18(0.017453292f * (c->fovy / 2.0f));
    if (c->flags & 4) {
        aspect *= 1.3333333f;
    }
    sx = 0.5f * (h * aspect);
    sy = 0.6666667f * h;
    fn_80313460(&c->pos, &c->offset, &eye);
    fn_80313460(&c->at, &c->offset, &at);
    fn_80313484(&at, &eye, &dir);
    fn_803134C4(&dir, &dir);
    fn_803134A8(&dir, &dir, dist);
    fn_80313460(&eye, &dir, &dir);
    fn_8031292C(scale, sx, sy, 1.0f);
    fn_803128AC(trans, dir.x, dir.y, dir.z);
    fn_80312444(lbl_804CB080->view, inv);
    fn_80312378(inv, scale, tmp);
    fn_80312378(trans, tmp, out);
    return (Mtx*)out;
}
