#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef struct UBits {
    u16 a : 3;
    u16 d : 3;
    u16 b : 3;
    u16 c : 3;
    u16 e : 3;
    u16 f : 1;
} UBits;
typedef struct GF { u32 a; u32 pad : 4; u32 b : 1; } GF;
struct MU2 : MapUnit { u8 pad118[0x14]; u8 skill[4]; };
struct KBase { u8 pad[0x44]; };
class KVt : public KBase {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void draw(int, int, int);
};
extern "C" {
extern u8 lbl_804CB73D;
extern u8 lbl_804CB741;
extern u8 lbl_803CAB38[];
extern u8 lbl_803E7290[];
extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;
extern void* lbl_804CA4D8;
extern void* lbl_804CA4E8;
extern void* lbl_804CA4EC;
extern void* lbl_804CA650;
extern GF* fn_80060728(void*);
extern int fn_8011B77C(void*, void*);
extern s8 fn_801284C4(MapUnit*);
extern u32 fn_8017FA1C(void);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);

void fn_800F8880(MU2* m) {
    if (lbl_804CB73D && fn_80060728(lbl_803CAB38)->b != 1 && (m->flags & 0x40)) {
        s16 list[0x20];
        s16 n = 0;
        Vec p = *(Vec*)&m->f1C;
        if ((u32)m->flags2 & 2) list[n++] = 0x5A;
        if (m->unkF4->unk8 == 1) {
            if (fn_8011B77C(m->skill, lbl_804CA4F8)) list[n++] = 0x5E;
            if (fn_8011B77C(m->skill, lbl_804CA4FC)) list[n++] = 0x5E;
            if (fn_8011B77C(m->skill, lbl_804CA4D8)) list[n++] = 0x5E;
        }
        if (fn_8011B77C(m->skill, lbl_804CA4E8) && !fn_8011B77C(m->skill, lbl_804CA4EC)) {
            if (fn_801284C4((MapUnit*)m) >= 0x1E) {
                list[n++] = 0x5F;
            } else if (fn_8011B77C(m->skill, lbl_804CA650)) {
                list[n++] = 0x60;
            }
        }
        if (((UBits*)m->unk110)->a) list[n++] = 0x1A;
        if (((UBits*)m->unk110)->b) list[n++] = 0x1B;
        if (((UBits*)m->unk110)->c) list[n++] = 0x1C;
        if (((UBits*)m->unk110)->d) list[n++] = 0x1D;
        if (((UBits*)m->unk110)->e) list[n++] = 0x1E;
        if (((UBits*)m->unk110)->f) list[n++] = 0x1F;
        if (n > 0) {
            list[n++] = 0;
            fn_8017FA1C();
            s16 icon = list[(fn_8017FA1C() >> 6) % n];
            if (icon) {
                u8 a = m->unk33 * lbl_804CB741 / 255;
                if (a) {
                    fn_8007E154();
                    fn_8007E4E4(p.x, p.y, 980.0f, 1.0f);
                    fn_8007E7DC(a);
                    fn_8007E164();
                    ((KVt*)lbl_803E7290)->draw(0, -0x14, icon);
                    fn_8007E7F4();
                }
            }
        }
        if ((u32)m->flags2 & 0x800) {
            if ((fn_8017FA1C() & 0x1F) < 0x14) {
                fn_8007E154();
                fn_8007E4E4(p.x, p.y, 980.0f, 1.0f);
                fn_8007E164();
                ((KVt*)lbl_803E7290)->draw(-0xC, -0x18, 0x5C);
            }
        }
    }
}
}
