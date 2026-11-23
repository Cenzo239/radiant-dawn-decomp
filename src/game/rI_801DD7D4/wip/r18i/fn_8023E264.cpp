/* WIP (round 18): class `other`. Structure and all calls/references are right; what is left is
   scheduling inside the inlined std::vector code on a LOCAL vector:
   - push_back: the original computes `0x3FFFFFFF - cap` twice from the same register (no CSE, no
     reload of cap); ours either reloads cap or keeps the difference in a register;
   - reserve/push_back swap tail: the original reloads buf.cap from the stack after memcpy/memset,
     ours forwards the register (`mr`);
   - fn_8023E264/fn_8023E8EC use all 18 saved registers: the original keeps the lock pointer in r14
     and leaves `lis lbl_80387C78@ha` in the loop; ours hoists the `lis` and rematerialises the lock;
   - ~PVec: original has `size - size` as lwz/subf, ours folds it to li 0.
   Needs fn_XXXX.symbols.json ({"...bss.0": "lbl_80425478"}) for the fn_fe.h statics. */
/* Archive/file entry manager: evict unreferenced entries to make room.
   fn_8023E264 works on the MEM1 list (sA), fn_8023E8EC on the MEM2 list (sB). Candidates are
   collected into a std::vector<FE*> under the lock, then each one is unloaded and freed. */
#include "game/rI_801DD7D4/fn_fe.h"
extern "C" {
extern void* lbl_804CBF90;
extern void* lbl_804CBF94;
extern char lbl_80372758[];
extern char lbl_80387C78[];
extern char lbl_804CAAA8[7];
extern char lbl_80390C64[];
extern char __files[];
u64 OSGetTime(void);
u64 fn_8028C418(u64, u64);
void fn_8029C20C(const char*, int, const char*, ...);
int fn_80290B48(void*, const char*, ...);
void fn_80291BD0(void);
void* fn_80079150(u32);
void fn_80079210(void*);
void* memcpy(void*, const void*, u32);
void* memset(void*, int, u32);
FE* fn_802BC2A4(void*, FE*);
void fn_802BC238(void*, FE*);
void fn_802FAED4(void*);
void fn_80320978(s64);
void fn_8023B894(FE*);
void fn_8023B9D8(FE*);
void fn_80078E24(u32);
void fn_8030E3F4(void*, u32);
void fn_8030EC2C(void*, FE*);
}
class VD { public: virtual void d(int); };
struct NList { void* head; void* tail; u16 num; u16 off; };

static inline u32 const& Max(u32 const& a, u32 const& b) { return a < b ? b : a; }
typedef FE* T;
struct SplitBuffer {
    T* first;
    u32 size;
    u32 cap;
    void* alloc;
    u32 start;
    SplitBuffer(u32 z, void* a) { first = (T*)z; size = z; cap = z; alloc = a; start = z; }
    ~SplitBuffer() { if (first) { size = 0; fn_80079210(first); } }
};
struct Buf3 {
    T* first;
    u32 size;
    u32 cap;
    Buf3(u32 z) { first = (T*)z; size = z; cap = z; }
    ~Buf3() { if (first) { size = 0; fn_80079210(first); } }
};
#pragma pool_strings on
/* The original strings of this file's pool (lbl_80372758), in order. */
void StringPool(const char** p) {
    p[0] = ".cmp";
    p[1] = ".pak";
    p[2] = ".cms";
}
static inline void msgOut(const char* m, void* f) {
    fn_80290B48(f, m);
    fn_80291BD0();
}
static inline void lengthError() {
    msgOut("vector length error", __files + 0xa0);
}
struct PVec {
    T* data;
    u32 size;
    u32 cap;
    PVec() { data = 0; size = 0; cap = 0; }
    void shrink(u32 n) { size -= n; }
    ~PVec() { if (data) { shrink(size); fn_80079210(data); } }
    T* begin() { return data; }
    T* end() { return data + size; }
    static u32 dist(T* const& a, T* const& b) { return b - a; }
};
static inline void reserve(PVec* v, u32 n) {
    if (n > v->cap) {
        Buf3 buf(0);
        if (n > 0x3FFFFFFF) {
            lengthError();
        }
        T* mem = (T*)fn_80079150(n * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = n;
        n = PVec::dist(v->begin(), v->end());
        T* old = v->begin();
        memcpy(buf.first + buf.size, old, n * sizeof(T));
        memset(old, 0, n * sizeof(T));
        buf.size += n;
        v->size = 0;
        u32 oc = v->cap;
        v->cap = buf.cap;
        buf.cap = oc;
        T* od = v->data;
        v->data = buf.first;
        buf.first = od;
        v->size = buf.size;
        buf.size = 0;
    }
}
static inline void push_back(PVec* v, T const& x) {
    u32 nc;
    u32 cc;
    u32 s;
    u32 c;
    u32 ns;
    u32 n;
    T* mem;
    u32 cnt;
    T* old;
    u32 oc;
    T* od;
    s = v->size;
    c = v->cap;
    if (s < c) {
        ns = s + 1;
        v->size = ns;
        v->data[ns - 1] = x;
    } else {
        if (0x3FFFFFFF - c < 1) {
            lengthError();
        }
        SplitBuffer buf(0, &v->cap); n = v->size + 1 - c;
        cc = c;
        if (n > 0x3FFFFFFF - cc) {
            lengthError();
        }
        u32 t2; u32 t1;
        if (cc < 0x15555555) {
            t1 = (cc + 1) * 3 / 5;
            nc = cc + Max(t1, n);
        } else if (cc < 0x2AAAAAAA) {
            t2 = (cc + 1) / 2;
            nc = cc + Max(t2, n);
        } else {
            nc = 0x3FFFFFFF;
        }
        if (nc > 0x3FFFFFFF) {
            lengthError();
        }
        mem = (T*)fn_80079150(nc * sizeof(T));
        if (mem == 0) {
            fn_80290B48(__files + 0xa0, lbl_80387C78);
            fn_80291BD0();
        }
        buf.first = mem;
        buf.cap = nc;
        buf.start = v->size;
        (buf.first + buf.start)[buf.size] = x;
        buf.size++;
        cnt = PVec::dist(v->begin(), v->end());
        old = v->begin();
        buf.start -= cnt;
        nc = cnt * sizeof(T);
        memcpy(buf.first + buf.start, old, nc);
        memset(old, 0, nc);
        buf.size += cnt;
        v->size = 0;
        oc = v->cap;
        v->cap = buf.cap;
        buf.cap = oc;
        od = v->data;
        v->data = buf.first;
        buf.first = od;
        v->size = buf.size;
        buf.size = 0;
    }
}
static inline u32 listSize(NList* l) {
    if (!(l != NULL)) fn_8029C20C(lbl_804CAAA8, 0xcf, lbl_80390C64);
    return l->num;
}
static inline int flg(FE* e, int m) { return e->flags & m; }
static inline void waitDone(FE* c) {
    fn_802FAED4(c->task);
    while (!(c->flags & 0x00230000)) {
        fn_80320978((s64)5 * ((*(u32*)0x800000F8 >> 2) / 1000));
        if (c->name[0] == 0) break;
    }
}
static inline void freeData(u32 p) {
    if ((p & 0xF0000000) != 0x90000000) {
        u32 q = p;
        if (p != 0) q = p;
        fn_80078E24(q);
    } else {
        u32 q = p;
        if (p != 0) q = p;
        fn_8030E3F4(lbl_804CBF90, q);
    }
}
static inline void freeE(FE* c) {
    if (c->name[0] != 0) {
        VO0N* k;
        if (flg(c, 0x00200000)) {
            fn_8023B894(c);
            fn_8023B9D8(c);
        }
        freeData(c->data);
        k = (VO0N*)sLock;
        k->v08();
        if ((c->data & 0xF0000000) != 0x90000000) {
            fn_802BC238(sA, c);
        } else {
            fn_802BC238(sB, c);
        }
        k->v10();
        ((VD*)c)->d(-1);
        fn_8030EC2C(lbl_804CBF94, c);
    }
}
static inline void drop(FE* e) {
    if (e->name[0] == 0) return;
    if (flg(e, 0x10000000)) return;
    waitDone(e);
    freeE(e);
}
struct Guard {
    VO0N* m;
    Guard(VO0N* l) : m(l) { m->v08(); }
    ~Guard() { m->v10(); }
};
#define EVICT(LIST) \
    PVec v; \
    FE* e; \
    T* it; \
    T* end; \
    u32 now; \
    { \
        Guard g((VO0N*)sLock); \
        now = fn_8028C418(OSGetTime(), *(u32*)0x800000F8 >> 2); \
        reserve(&v, listSize((NList*)LIST)); \
        for (e = fn_802BC2A4(LIST, NULL); e != NULL; e = fn_802BC2A4(LIST, e)) { \
            if (e->name[0] == 0) continue; \
            if (e->rc != 0) continue; \
            if (h >= 0 && h != e->a4b) continue; \
            if (e->data == 0) continue; \
            if (!flg(e, 0x30000) && !flg(e, 0x200000)) continue; \
            if (flg(e, 0x10000000)) continue; \
            switch (mode) { \
            case 0: \
                if (!flg(e, 0x1000)) break; \
                continue; \
            case 0x2000: \
                if (!flg(e, 0x2000)) continue; \
                break; \
            case 0x1000: \
                break; \
            } \
            if (flg(e, 0x80000) && now < e->a58 + 1) continue; \
            push_back(&v, e); \
        } \
    } \
    end = v.end(); \
    for (it = v.begin(); it != end; ++it) { \
        drop(*it); \
    }
extern "C" {
#pragma push
#pragma use_lmw_stmw on
void fn_8023E264(s8 h, int mode) {
    EVICT(sA)
}
void fn_8023E8EC(s8 h, int mode) {
    EVICT(sB)
}
#pragma pop
}
