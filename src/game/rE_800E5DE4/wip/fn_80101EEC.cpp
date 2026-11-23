/* fn_80101EEC, fn_80102030: 1 word differs in each. Structs and helpers are in ../fn_80100760.cpp.
 * The original has `li r0,0x10; srawi r28,r0,1` (same as fn_800FD65C with 0xC). Half(const int&) with a
 * literal gets everything right except it loads the constant with `lwz r0,@sda21` instead of `li`.
 * Every other form tried folds to `li r28,8` or gives `srawi r28,r28,1`: see NOTES.md. */
static inline int Half(const int& x) { return x >> 1; }
void fn_80101EEC(Task2* t) {
    R2438* o = ((Ctl*)t->ctl)->owner;
    int n = 0x10;
    if (Boost(o)) n = Half(0x10);
    Fade(o->u, 3, n, o);
}
void fn_80102030(Task2* t) {
    Ctl* c = (Ctl*)t->ctl;
    R2438* o = c->owner;
    MapUnit* m = c->m;
    int n = 0x10;
    fn_800088A0(m, 2.0f);
    if (Boost(o)) {
        fn_800088A0(m, 4.0f);
        n = Half(0x10);
    }
    if (fn_80008C98(m, 0)) {
        o->u->flags |= 4;
        fn_800F74D0(o->u, 0);
        o->u->flags &= ~4;
        Fade(o->u, 0, n, o);
        o->b35 = 1;
    }
}
