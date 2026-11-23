/* Round 11 near misses, not compiled. Helpers: Spr3 in fn_8006E278.cpp; GrowOf, PICK, GetD, SetD in fn_8006C2D0.cpp. */

/* 4 to 6 of 88 words differ: in cases 1 and 3 the original has addi x; addi y; li id. The compiler always
   emits li id; addi y; addi x, whatever the statement order, parameter types or inline form. */
void fn_80075714(int x, int y, int k) {
    int id;
    int v = fn_801076D0(k);
    if (v == 2) {
        return;
    }
    switch (v) {
    case 0:
        id = 0x30;
        break;
    case 4:
        id = 0x33;
        break;
    case 1:
        x = x + 4;
        y = y + 4;
        id = 0x31;
        break;
    case 3:
        x = x + 4;
        y = y + 4;
        id = 0x32;
        break;
    case 2:
    default:
        break;
    }
    Spr3(x, y, 1, 0xFF, id, 0);
    //
}

/* Control flow right, 264 position differences from the GrowOf block at the start (one word extra). Same
   unsolved schedule as fn_8006D380: the original delays the sums of 0x123, 0x126, 0x127 and 0x128. */
void fn_8006D790(BU* u, u8* d) {
    fn_8006D380(u, d);
    Grow t = GrowOf(u);
    u8 a0 = t.v[0];
    u8 a1 = t.v[1];
    u8 a2 = t.v[2];
    u8 a3 = t.v[3];
    u8 a4 = t.v[4];
    u8 a5 = t.v[5];
    u8 a6 = t.v[6];
    u8 a7 = t.v[7];
    int n = 0;
    int i;
    for (i = 0; i < 8; i++) {
        if ((s8)GetD(d, i)) {
            n++;
        }
    }
    if (n > 3) {
        for (; n > 3; n--) {
            int best = 0x7F;
            int idx = -1;
            for (int j = 0; j < 8; j++) {
                if ((s8)GetD(d, j)) {
                    int i = j;
                    if (PICK < best) {
                        best = PICK;
                        idx = j;
                    }
                }
            }
            SetD(d, idx, 0);
        }
    } else if (n < 3) {
        for (; n < 3; n++) {
            int best = -0x80;
            int idx = -1;
            for (int j = 0; j < 8; j++) {
                if (!(s8)GetD(d, j)) {
                    int i = j;
                    if (best < PICK && (s16)fn_80122E8C(u, j) < (s16)fn_80122F14(u, j)) {
                        best = PICK;
                        idx = j;
                    }
                }
            }
            if (idx < 0) {
                break;
            }
            SetD(d, idx, 1);
        }
    }
}
