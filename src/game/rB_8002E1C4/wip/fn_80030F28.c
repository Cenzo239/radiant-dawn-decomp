/* fn_80030F28: 9 of 84 words differ - float register choice for the u8->float
 * conversion constant and load order of from/to vs mode differ. Needs Tween from fn_800300B4.c.
void fn_80030F28(Tween* w)
{
    if (w->t <= w->dur) {
        w->cur[0] = fn_8017F68C(w->from[0], w->to[0], w->t, w->dur, w->mode);
        w->cur[1] = fn_8017F68C(w->from[1], w->to[1], w->t, w->dur, w->mode);
        w->cur[2] = fn_8017F68C(w->from[2], w->to[2], w->t, w->dur, 0);
        w->t++;
    }
    if (w->x5b != 0 || fn_80068D74() != 0) {
        fn_80072488(w->cur[0], w->cur[1], w->cur[2], w->x8b, w->x3c, w->x5c);
        fn_8007E7F4();
    }
}

*/
