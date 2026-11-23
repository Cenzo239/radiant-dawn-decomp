#ifndef RN_8025EEF0_ROOM_H
#define RN_8025EEF0_ROOM_H
#include "game/rN_8025EEF0/calls.h"
/* Conversation room data: E_ConversationRoom (lbl_804CC06C + 0x108) or E_ConversationRoomFe8 (lbl_804CC074 + 0xC). */
struct Room {
    s16 m0;
    u8 pad2[2];
    f32 m4[4];
    f32 m14;
    f32 m18;
    s16 m1C;
    s16 m1E;
    s16 m20;
    s16 m22;
    s16 m24[4];
    s16 m2C;
    u8 pad2E[2];
    s16 m30;
    s16 m32;
    s16 m34;
    s16 m36;
    s16 m38;
    s16 m3A;
    s16 m3C;
    s16 m3E;
    s16 m40;
    s16 m42;
    s16 m44;
    s16 m46;
    f32 m48;
    f32 m4C;
    f32 m50;
    s16 m54;
    u8 pad56[2];
    void* m58;
    void* m5C;
};
struct ConvItem { char* m0; char* m4; int m8; int mC; };
/* lbl_804CC06C: entries 0x30 bytes each */
struct ConvSt {
    u8 pad0[8];
    void* m8;       /* 0x08 */
    int n;          /* 0x0C */
    u8* tbl;        /* 0x10 */
    int m14;
    char** names;   /* 0x18 */
    int m1C;
    char** names2;  /* 0x20 */
    void* items[0x28]; /* 0x24 */
    int count;      /* 0xC4 */
    char text[0x40]; /* 0xC8 */
};
extern "C" {
extern char lbl_8037359C[];
extern u8* lbl_804CC06C;
extern u8* lbl_804CC074;
extern u8* lbl_804CC068;
}
static inline BOOL isProc(const char* s) { return fn_80085708(s) != 0; }
static inline Room* roomData(void) {
    if (isProc(lbl_8037359C)) {
        return (Room*)(lbl_804CC06C + 0x108);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return (Room*)(lbl_804CC074 + 0xC);
    }
    return 0;
}
static inline void* roomTex(void) {
    if (isProc(lbl_8037359C)) {
        return ((Room*)(lbl_804CC06C + 0x108))->m5C;
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return ((Room*)(lbl_804CC074 + 0xC))->m5C;
    }
    return 0;
}
/* Current-page values. The local pointer keeps the addi in a saved register across the second roomData(). */
static inline f32 curF(void) { f32* q = roomData()->m4; return q[roomData()->m30]; }
static inline void setCurF(f32 v) { f32* q = roomData()->m4; q[roomData()->m30] = v; }
static inline s16 curS(void) { s16* q = roomData()->m24; return q[roomData()->m30]; }
static inline void setCurS(int v) { s16* q = roomData()->m24; q[roomData()->m30] = v; }
#endif
