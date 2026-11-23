#pragma use_lmw_stmw on
#include "game/rS_8023FD30/types.h"
/* Bit sets kept in the save data. */
static inline void bitSet(u32* w, u32 n) {
    u32 q = n;
    u32* p = w;
    while (q >= 32) {
        q -= 32;
        p++;
    }
    *p |= (1 << q);
}
static inline u32 bitTest(const u32* w, u32 n) {
    const u32* p = w;
    u32 q = n;
    while (q >= 32) {
        q -= 32;
        p++;
    }
    return (*p & (1 << q)) != 0;
}
struct SaveItem {
    u8 pad[0x1C];
    u16 id;
};
struct SaveData {
    u8 pad00[0x2C];
    u32 bits2C[4];
    u8 pad3C[0x18A0 - 0x3C];
    u32 bits18A0[4];
};
struct LogEntry {
    u64 id;
    s8 type;
    u8 sub;
    u16 v;
    u32 a;
    u64 x;
};
struct SaveLog {
    u8 pad00[0x20];
    u32 flags;
    u8 pad24[0x18F8 - 0x24];
    LogEntry e[30];
};
struct SaveNames {
    u8 pad00[0x3C];
    const char* names[0x300];
    u32 hashes[0x300];
    u8 bits[0x60];
};
extern "C" {
s32 fn_80076D18(const char*);
int fn_80291188(const char*, const char*);
}
static inline int findName(SaveNames* s, const char* name) {
    u32 h = fn_80076D18(name);
    SaveNames* q = s;
    for (int i = 0; i < 0x300; i++) {
        if (h == *(u32*)((u8*)q + 0xC3C) && fn_80291188(*(const char**)((u8*)q + 0x3C), name) == 0) {
            return i;
        }
        q = (SaveNames*)((u8*)q + 4);
    }
    return -1;
}
static inline BOOL isUsed(SaveNames* s, int i) {
    return i >= 0 && i < 0x300 && s->names[i] != 0;
}
static inline void bitOff(SaveNames* s, int i) {
    if (i >= 0 && i < 0x300) {
        s->bits[i >> 3] &= ~(1 << (i & 7));
    }
}
extern "C" {
void fn_80245104(SaveData* s, SaveItem* it) {
    int id = it->id;
    if (id >= 0x80) return;
    bitSet(s->bits2C, id);
}
void fn_8024542C(SaveData* s, int i) {
    if (i < 0) return;
    if (i >= 0x80) return;
    bitSet(s->bits18A0, i);
}
u32 fn_802454C8(SaveData* s, int i) {
    u32 r = 0;
    if (i >= 0 && i < 0x80) {
        r = bitTest(s->bits18A0, i);
    }
    return r;
}
void fn_80245574(SaveData* s) {
    for (int i = 0; i < 0x80; i++) {
        bitSet(s->bits18A0, i);
    }
}

void fn_8024519C(SaveNames* s, const char* name) {
    int i = findName(s, name);
    if (i < 0) {
        for (i = 0; i < 0x300; i++) {
            if (!isUsed(s, i)) {
                s->names[i] = name;
                s->hashes[i] = fn_80076D18(name);
                bitOff(s, i);
                return;
            }
        }
    }
}
void fn_802452B4(SaveNames* s, const char* name) {
    int i = findName(s, name);
    if (i >= 0) {
        if (i >= 0 && i < 0x300) {
            if (i >= 0 && i < 0x300) {
                s->bits[i >> 3] |= 1 << (i & 7);
            }
        }
    }
}
u32 fn_80245368(SaveNames* s, const char* name) {
    int i = findName(s, name);
    if (i < 0) return 0;
    if (i < 0 || i >= 0x300) return 0;
    return (s->bits[i >> 3] & (1 << (i & 7))) != 0;
}

void* memmove(void*, const void*, u32);
void fn_80245614(SaveLog* s, u64 id, int type, int sub, u16 v, u32 a, u64 x) {
    SaveLog* q = s;
    int i;
    for (i = 0; i < 30; q = (SaveLog*)((u8*)q + 0x18), i++) {
        if (q->e[0].type < 0) break;
        if (id == q->e[0].id && sub == q->e[0].sub) break;
    }
    if (i == 30) {
        memmove(&s->e[0], &s->e[1], 0x2B8);
        i = 29;
    }
    LogEntry* e = &s->e[i];
    e->id = id;
    e->type = type;
    e->sub = sub;
    e->v = v;
    e->a = a;
    e->x = x;
    switch ((s8)type) {
    case 2:
        s->flags |= 8;
        break;
    case 1:
        s->flags |= 4;
        break;
    case 0:
        s->flags |= 2;
        break;
    case 3:
        s->flags |= 1;
        break;
    }
}
int fn_802457BC(SaveLog* s) {
    int i;
    SaveLog* q = s;
    for (i = 0; i < 30; q = (SaveLog*)((u8*)q + 0x18), i++) {
        if (q->e[0].type < 0) break;
    }
    return i;
}
}
