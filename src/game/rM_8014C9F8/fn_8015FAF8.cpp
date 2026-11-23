// Set one bit in the current unit's 64-bit flags.
extern "C" {
struct UnitFlags {
    unsigned char pad[0x108];
    unsigned long long flags;
};
struct UnitContext {
    UnitFlags* unit;
    unsigned char pad[0x12C];
};
extern UnitContext lbl_803CA870;

void fn_8015FAF8(void) {
    lbl_803CA870.unit->flags |= 1ULL;
}
}
