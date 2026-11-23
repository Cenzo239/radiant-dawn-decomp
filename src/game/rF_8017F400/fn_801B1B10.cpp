#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* picture list: open the selected picture, and mark it seen */
struct PInfo { s8 id; u8 pad[0xF]; const char* x10; const char* x14; };
struct LNode { LNode* prev; LNode* next; PInfo* val; };
struct PList { u32 x0; LNode s; };
typedef struct LData { u8 pad[0x18]; PList* list; u8 p1C[8]; int x24; u8 p28[4]; int x2C; u8 p30[8]; int x38; } LData;
extern LData* lbl_804CB9BC;
extern void* lbl_804CB9B8;
extern int lbl_804CB9C0, lbl_804CB9C4, lbl_804CB9C8;
extern u8 lbl_803CAB38[];
extern char lbl_8036DCE0[];
extern void fn_80083DC4(void*, int);
extern void fn_80253EE4(const char*, f32);
extern void* fn_800C3558(void);
#if TARGET_PC
extern FE10_PROTO void fn_801D0C68(void*, ptr32<const void>);
#else
extern void fn_801D0C68(void*, const char*);
#endif
extern void fn_801D0C88(void*, const char*);
extern void fn_8009E554(const char*, void*);

static inline LNode* Adv(LNode* it, int n) {
    if (n >= 0) {
        for (int k = n; k > 0; k--) it = it->next;
    } else {
        for (int k = n; k < 0; k++) it = it->prev;
    }
    return it;
}
static inline u32 Lk(u32* w, u32 k) {
    while (k >= 32) { k -= 32; w++; }
    return *w & (1 << k);
}
void fn_801B1B10(void) {
    LNode* it = Adv(lbl_804CB9BC->list->s.next, lbl_804CB9BC->x2C);
    if (Lk((u32*)(lbl_803CAB38 + 0xDC), it->val->id) == 0) {
        fn_80083DC4(lbl_804CB9B8, 1);
        fn_80253EE4(lbl_8036DCE0 + 0xAB, 0.0f);
    } else if (it->val->x10 == 0 || it->val->x14 == 0) {
        fn_80083DC4(lbl_804CB9B8, 1);
        fn_80253EE4(lbl_8036DCE0 + 0xAB, 0.0f);
    } else {
        lbl_804CB9C0 = lbl_804CB9BC->x24;
        lbl_804CB9C4 = lbl_804CB9BC->x2C;
        lbl_804CB9C8 = lbl_804CB9BC->x38;
        fn_80253EE4(lbl_8036DCE0 + 0xB9, 0.0f);
    }
}
static inline void Bit(u32* w, u32 k) {
    while (k >= 32) { k -= 32; w++; }
    *w |= 1 << k;
}
void fn_801B1EE4(void) {
    LNode* it = Adv(lbl_804CB9BC->list->s.next, lbl_804CB9BC->x2C);
    Bit((u32*)(lbl_803CAB38 + 0xF0), it->val->id);
    fn_801D0C68(fn_800C3558(), it->val->x10);
    fn_801D0C68(fn_800C3558(), it->val->x14);
    fn_801D0C88(fn_800C3558(), lbl_8036DCE0 + 0x103);
    fn_8009E554(lbl_8036DCE0 + 0x112, lbl_804CB9B8);
}
}
