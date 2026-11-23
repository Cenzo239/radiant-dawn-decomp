// Update the map position unless either of the two blocking flags is set.
extern "C" {
struct MapObject {
    int pad;
    float x, y;
    unsigned char gap[0x100];
    unsigned int flags;
};
extern unsigned char lbl_803CAB38[0x988];
void fn_800620A8(float x, float y, void* state);
void fn_8012FED4(void);

void fn_800FAFF0(MapObject* object, int refresh) {
    if (!(object->flags & 0x18)) {
        // Load both floats before narrowing them; their order matches the
        // original conversion and stack-store sequence.
        float y = object->y;
        float x = object->x;
        fn_800620A8((int)x, (int)y, lbl_803CAB38);
        if (refresh) {
            fn_8012FED4();
        }
    }
}
}
