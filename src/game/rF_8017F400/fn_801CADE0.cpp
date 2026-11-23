typedef unsigned char u8;

struct C4 {
    u8 r, g, b, a;

    C4(const C4& other) {
        // Preserve the original temporary's four byte stores. Without these
        // volatile accesses, the compiler eliminates the stack copy.
        *(volatile u8*)&r = other.r;
        *(volatile u8*)&g = other.g;
        *(volatile u8*)&b = other.b;
        *(volatile u8*)&a = other.a;
    }

    C4& operator=(const C4& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }
};

struct M { u8 pad[0x1c]; C4 color; };
struct P { u8 pad[0x30]; M* m; int timer; int p38; C4 color; };

extern "C" void fn_801CADE0(P* p) {
    C4 color(p->m->color);
    p->color = color;
    p->timer = 0;
}
