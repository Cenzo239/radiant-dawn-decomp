#include "game/rC2_8005259C/base.h"
struct ChapD { u8 pad[0x8b]; u8 b8b; };
struct GS { u8 pad[0x10]; u8 b10; };
struct Cls { u8 pad[0xee]; u16 hee; };
struct CK { u8 pad[8]; u8 b8; };
struct MU { u8 pad[0xf0]; Cls* f0; CK* f4; u8 p[0x34]; u8 a12c[1]; };
extern "C" {
extern void* lbl_804CA4EC;
ChapD* fn_8010B094(u8);
int fn_801D3DEC(void);
int fn_8011B77C(void*, void*);
}

extern "C" int fn_80060828(GS* g, MU* u) {
    Cls* c;
    int r = 0;
    if (fn_8010B094(g->b10) == 0) {
        return 0;
    }
    c = u->f0;
    if (fn_801D3DEC() == 0) {
        switch (u->f4->b8) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (c->hee & 0x20) {
                if (c->hee & 0x86) {
                    r = (s8)fn_8010B094(g->b10)->b8b;
                }
            } else if ((c->hee & 0x10) && (c->hee & 0x80)) {
                if (fn_8011B77C(u->a12c, lbl_804CA4EC)) {
                    r = (s8)fn_8010B094(g->b10)->b8b;
                }
            }
            break;
        }
    }
    return r;
}
