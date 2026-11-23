/* fn_8026A864: 13 words, r30/r31 swap between the switch result and the proc lookup */
void fn_8026A864(void*, void*, UnitAnimCmd* c) {
    u16 v;
    void* obj;
    u16 old;
    void* m;
    u8* u;
    switch ((s8)fn_80244D88()) {
    case 0: v = 0; break;
    case 1: v = 2; break;
    case 2: v = 3; break;
    case 3: v = 4; break;
    case 4: v = 5; break;
    case 5: v = 6; break;
    case 6: v = 7; break;
    default: v = 2; break;
    }
    obj = unitOf();
    u = c->u;
    if (obj != 0 && u != 0) {
        m = fn_80011F0C();
        old = *(u16*)(u + 4);
        *(u16*)(u + 4) = v;
        fn_80022254(fn_80012308(obj, u), m);
        *(u16*)(u + 4) = old;
    }
}

