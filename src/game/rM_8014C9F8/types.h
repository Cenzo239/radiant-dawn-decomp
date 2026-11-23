#ifndef RM_8014C9F8_TYPES_H
#define RM_8014C9F8_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;
typedef int BOOL;
#ifndef NULL
#define NULL 0
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec;

/* Process object, copied from rJ_800799AC/proc.h. */
struct Proc;
typedef void (*ProcFunc)(Proc*);
struct Proc {
    u32* script;   /* 0x00 */
    u32* cur;      /* 0x04 */
    ProcFunc onEnd;  /* 0x08 */
    ProcFunc onIdle; /* 0x0C */
    ProcFunc loop;   /* 0x10 */
    const char* name; /* 0x14 */
    Proc* parent;  /* 0x18 */
    Proc* child;   /* 0x1C */
    Proc* next;    /* 0x20 */
    Proc* prev;    /* 0x24 */
    s16 sleep;     /* 0x28 */
    u8 mark;       /* 0x2A */
    u8 layer;      /* 0x2B */
    u8 flags;      /* 0x2C */
    u8 lockCnt;    /* 0x2D */
    u8 pause;      /* 0x2E */
    u8 pad2F;
};

extern "C" {
Proc* fn_80081050(void* script, void* parent); /* Proc_Create */
Proc* fn_80081194(void* script, void* parent); /* Proc_CreateBlocking */
void fn_80081A90(void* p);      /* Proc_End */
void fn_80083B78(void* p);      /* Proc_Break */
Proc* fn_80083B84(void* script); /* Proc_Find by class */
void fn_8008319C(void* p);      /* clear blocking */
int fn_800839DC(void);          /* free slot count */
Proc* fn_80085708(const char* name); /* find by name */
}

#endif
