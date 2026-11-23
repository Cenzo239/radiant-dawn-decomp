// Near match: 44 bytes, three instruction words differ under --strict-references.
// Volatile reads preserve this candidate's load sequence; the original source
// qualifiers are unknown. This is not a completed matching implementation.
extern "C" {
struct Color {
    unsigned char r, g, b, a;
};

struct Object {
    unsigned char pad[0x78];
    Color color;
};

void fn_80150B20(Object* o, Color* c) {
    unsigned char r, g, b, a;
    r = ((volatile Color*)c)->r;
    g = ((volatile Color*)c)->g;
    b = ((volatile Color*)c)->b;
    a = ((volatile Color*)c)->a;
    o->color.r = r;
    o->color.g = g;
    o->color.b = b;
    o->color.a = a;
    c->a = 255;
}
}
