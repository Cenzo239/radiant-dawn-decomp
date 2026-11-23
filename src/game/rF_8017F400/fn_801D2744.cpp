/* fn_801D2744: base (camp) screen setup. Copies the background name of the current chapter data into
   lbl_8041EEE0 (with the "-wide" suffix in widescreen), loads it, builds the help bar (0x68 widget,
   id -0x1000) and the 0x40 widget kept at +0x54, and starts the BGM unless bit 4 of the global flags is set.
   Exact (check_func.py --symbol-map fn_801D2744.symbols.json --strict-references). */
#include "game/rF_8017F400/types.h"
#include "game/helpbar.h"

/* Plain 0x40 widget with its own vtable (lbl_8038BD90) directly over HbWidget. */
class HbPanel : public HbWidget {
public:
    virtual void v0();
    HbPanel() : HbWidget(0x1ae, 0x24, 0x260, 0x38, 0xb2, 0x14, 0x320, 0x10) {}
};

struct Scn { u8 pad0[0x40]; const char* bg; u8 pad44[0x10]; HbWidget* x54; };
struct Chap { u8 pad0[0x94]; const char* bgName; };
extern "C" {
extern u32 lbl_804CB700;
extern u8 lbl_8038C10C[], lbl_8038C100[];
extern u8 lbl_803CAB38[];
extern char lbl_8041EEE0[0x80];
extern char lbl_804CA928[8]; /* "-wide" in Shift-JIS */
extern char lbl_804CA920[8]; /* "" */
extern char lbl_8036EA88[];
Chap* fn_8006074C(void*);
#if TARGET_PC
FE10_PROTO ptr32<void> fn_80068528(Chap*);
#else
void* fn_80068528(Chap*);
#endif
char* fn_802910CC(char*, const char*, u32); /* strncpy */
char* fn_80291110(char*, const char*);      /* strcat */
int fn_801D09F0(void);
void fn_800D42A0(const char*);
void* fn_800D4188(const char*, void*);
void fn_800D3D00(f32, void*, int);
HbHelpBar* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_80084F0C(void*);
void fn_80250E38(f32, f32, int);
s8 fn_8024F7EC(void* bgm);
void fn_80251838(f32, int, void*);
void fn_801D2744(Scn* s);
}
static inline void LoadBg(Scn* s, const char* name) {
    if (name != 0) {
        s->bg = name;
        void* r = fn_800D4188(name, s);
        fn_800D3D00(90.0f, r, 2);
        fn_800D3D00(89.9f, fn_800D4188(lbl_8036EA88, r), 2);
    }
}

void fn_801D2744(Scn* s) {
    fn_802910CC(lbl_8041EEE0, fn_8006074C(lbl_803CAB38)->bgName, 0x7f);
    lbl_8041EEE0[0x7f] = 0;
    if (fn_801D09F0()) {
        fn_80291110(lbl_8041EEE0, lbl_804CA928);
    }
    if (s->bg != 0) {
        fn_800D42A0(s->bg);
    }
    LoadBg(s, lbl_8041EEE0);
    HbHelpBar* b = new HbHelpBar;
    b->id = -0x1000;
    b->s.w[3] = 1;
    b->a64 = lbl_804CA920;
    b->flags |= 0x10;
    b->a60 = 0;
    b->a28 = 8;
    fn_801E5448(s, b);
    HbHelpBar* h = fn_801E5640(s, -0x1000, 0);
    if (h != 0) {
        h->a64 = (const char*)lbl_8038C10C;
    }
    lbl_804CB700 &= ~1;
    fn_80084F0C(lbl_8038C100);
    HbPanel* p = new HbPanel;
    s->x54 = p;
    if (p != 0) {
        p->rc++;
    }
    s->x54->id = 0;
    s->x54->a28 = 0;
    fn_801E5448(s, s->x54);
    if (!(lbl_804CB700 & 0x10)) {
        fn_80250E38(0.0f, 0.0f, 6);
        void* m = fn_80068528(fn_8006074C(lbl_803CAB38));
        if (fn_8024F7EC(m)) {
            fn_80251838(0.0f, 0, m);
        }
    }
    lbl_804CB700 |= 0xF0000;
}
