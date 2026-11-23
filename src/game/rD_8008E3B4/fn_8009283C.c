#include "game/rD_8008E3B4/types.h"

#pragma use_lmw_stmw on

/* String pool at 0x80363A40: "", "%s_0", "%s_0_2", "%s_1", "%s_2", "%s_3",
 * "Scripts/%s.cmb", "mess/"... Referenced by offset so the addresses match. */
extern char lbl_80363A40[];

int fn_80290DDC(char* buf, const char* fmt, ...); /* sprintf */
char* fn_800D0864(const char* s);

typedef struct NamedObj {
    u32 unk0;
    char* name;
} NamedObj;

char* fn_8009283C(NamedObj* obj)
{
    if (obj->name == NULL) {
        return lbl_80363A40;
    }
    return fn_800D0864(obj->name);
}

#define NAME_WITH_SUFFIX(func, off)                 \
char* func(NamedObj* obj)                           \
{                                                   \
    char buf[72];                                   \
    if (obj->name == NULL) {                        \
        return lbl_80363A40;                        \
    }                                               \
    fn_80290DDC(buf, lbl_80363A40 + off, obj->name); \
    return fn_800D0864(buf);                        \
}

NAME_WITH_SUFFIX(fn_8009285C, 0x1)  /* "%s_0" */
NAME_WITH_SUFFIX(fn_800928B0, 0x6)  /* "%s_0_2" */
NAME_WITH_SUFFIX(fn_80092904, 0xd)  /* "%s_1" */
NAME_WITH_SUFFIX(fn_80092958, 0x12) /* "%s_2" */
NAME_WITH_SUFFIX(fn_800929AC, 0x17) /* "%s_3" */

typedef struct ChapterData {
    u8 pad0[0xc];
    char* script;   /* 0x0C: script base name */
    char* mess;     /* 0x10: default message file */
    char* mess3;    /* 0x14 */
    char* mess0;    /* 0x18 */
    char* mess1;    /* 0x1C */
    char* mess2;    /* 0x20 */
} ChapterData;

extern u8 lbl_803CAB38[];
extern char* lbl_8037AB10[]; /* per-language directory names */
extern char lbl_804CA0C0[8]; /* "" (sdata) */
extern void* lbl_804CB610;

void* fn_8010B094(int id);
int fn_80290D04(char* buf, int n, const char* fmt, ...); /* snprintf */
void fn_800C3840(char* path, int v);
u8* fn_80060728(void* p);
void* fn_8024BC94(void);
void* fn_80075D78(char* path);
void fn_8023F7EC(char* path, int v);

/* Picks the message file by the difficulty-ish mode byte at +0x11. */
static inline char* GetChapterMess(ChapterData* c)
{
    char* mess = NULL;
    switch (fn_80060728(lbl_803CAB38)[0x11]) {
    case 3:
        mess = c->mess3;
        mess = mess != NULL ? mess : c->mess;
        break;
    case 0:
        mess = c->mess0;
        mess = mess != NULL ? mess : c->mess;
        break;
    case 1:
        mess = c->mess1;
        mess = mess != NULL ? mess : c->mess;
        break;
    case 2:
        mess = c->mess2;
        mess = mess != NULL ? mess : c->mess;
        break;
    }
    return mess;
}

void fn_80092A00(int id)
{
    char buf[64];
    ChapterData* c = fn_8010B094(id);
    char* mess;
    s8 lang;
    fn_80290D04(buf, 0x40, lbl_80363A40 + 0x1c, c->script); /* "Scripts/%s.cmb" */
    fn_800C3840(buf, 0);
    if (GetChapterMess(c) == NULL) {
        lbl_804CB610 = NULL;
        return;
    }
    mess = GetChapterMess(c);
    lang = *(s8*)((u8*)fn_8024BC94() + 0x1bc8);
    fn_80290DDC(buf, lbl_80363A40 + 0x2b, lang >= 0 ? lbl_8037AB10[lang] : lbl_804CA0C0, mess); /* "mess/%s%s.m" */
    lbl_804CB610 = fn_80075D78(buf);
    fn_8023F7EC(buf, 0x20);
}

void fn_800761F0(void* p);
void fn_800C3974(void);

void fn_80092BF8(void)
{
    if (lbl_804CB610 != NULL) {
        fn_800761F0(lbl_804CB610);
    }
    fn_800C3974();
}

typedef struct ModeFlags {
    u8 pad0[0x85];
    u8 val3;        /* 0x85 */
    u8 val0;        /* 0x86 */
    u8 val1;        /* 0x87 */
    u8 val2;        /* 0x88 */
    u8 pad89[4];
    u8 b80 : 1;     /* 0x8D */
    u8 b40 : 1;
    u8 b20 : 1;
    u8 b10 : 1;
    u8 flag2 : 1;
    u8 flag1 : 1;
    u8 flag0 : 1;
    u8 flag3 : 1;
} ModeFlags;

u8 fn_80092C28(ModeFlags* m, int mode)
{
    switch (mode) {
    case 3:
        return m->flag3;
    case 0:
        return m->flag0;
    case 1:
        return m->flag1;
    case 2:
        return m->flag2;
    }
    return 0;
}

u8 fn_80092C84(ModeFlags* m)
{
    switch (fn_80060728(lbl_803CAB38)[0x11]) {
    case 3:
        return m->val3;
    case 0:
        return m->val0;
    case 1:
        return m->val1;
    case 2:
        return m->val2;
    }
    return 0;
}
