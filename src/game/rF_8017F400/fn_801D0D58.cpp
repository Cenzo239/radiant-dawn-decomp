/* fn_801D0D58 (round 22, agent r22b): exact.
 * Event script VM: call a script function. Drops the callee's argument count
 * (fn+0xD, s8) from the stack as its locals base, reserves its local count (fn+0x12),
 * pushes the caller's pc, fn, globalsTop and locals, enters the function
 * (pc = fn+4 code pointer), sets globalsTop to lbl_804CB6A8 + the script's global index
 * (fn+8 -> +0x20, u16) and zeroes the non-argument locals.
 * Built with tools/equiv/mkself.py from rR_80175E5C/fn_801D0EC0.cpp (the interpreter that
 * calls it) and the fragment in rR_80175E5C/wip/fn_801D0EC0.cpp. The pushes must go
 * through an inline (`*vm->sp++ = v`), and the loop start must read the field as s8.
 */
/* The event script bytecode interpreter. */
#include "game/rR_80175E5C/types.h"

struct VM {
    int* stackBase;
    int s04;
    u8* fn;
    u8* pc;
    int globalsTop;
    int* locals;
    int* sp;
    s8 halt;
    s8 argc;
    u8 s1E;
    s8 s1F;

};

#define Push(v) (*vm->sp++ = (v))
#define Pop() (*--vm->sp)
#define Fetch8() ((s8)*vm->pc++)
static inline int Fetch16_(VM* vm) {
    int v = (s8)*vm->pc++ << 8;
    v += *vm->pc++;
    return v;
}
#define Fetch16() Fetch16_(vm)
static inline int Fetch32_(VM* vm) {
    u32 v = *vm->pc++ << 24;
    v += *vm->pc++ << 16;
    v += *vm->pc++ << 8;
    v += *vm->pc++;
    return v;
}
#define F(p, t, o) (*(t*)((u8*)(p) + (o)))
#define STRBASE F(F(vm->fn, u8*, 8), int, 0x24)

extern "C" {
extern int* lbl_804CB6A8;
#if TARGET_PC
FE10_PROTO void fn_800C3584(p32arg);
FE10_PROTO u8* fn_80076F54(p32arg);
#else
void fn_800C3584(int);
u8* fn_80076F54(int);
#endif
void fn_801D20D4(VM*, u8*);
void fn_801D2378(VM*);
void fn_801D0D58(VM*, u8*);

static inline int StrEq(const char* a, const char* b) {
    while (*a || *b) {
        if (*a++ != *b++) return 0;
    }
    return *a == *b;
}



#define BIN(expr) { int b = Pop(); int a = Pop(); Push(expr); continue; }

void fn_801D0EC0(VM* vm);


#if TARGET_PC
FE10_PROTO void * fn_800C3558(void);
FE10_PROTO void fn_800C3560(p32arg);
#else
int fn_800C3558();
void fn_800C3560(int);
#endif

#define CALLN(T, args) { int r = ((int (*) T)F(fn, void*, 4)) args; int* s = vm->sp; *s = r; vm->sp = s + 1; break; }

void fn_801D20D4(VM* vm, u8* fn);

void fn_801D0C20(VM* vm);

int fn_801D0C88(VM* vm, const char* name);


}

/* ---- from build/tmp/r22b/fr_q5.cpp ---- */
extern "C" {
extern "C" {
static inline void push_(VM* vm, int v) { *vm->sp++ = v; }
#define PU(v) push_(vm, v)
void fn_801D0D58(VM* vm, u8* fn) {
    int n = F(fn, s16, 0x12);
    int* args = vm->sp - (s8)F(fn, u8, 0xD);
    vm->sp = args + n;
    PU((int)vm->pc);
    PU((int)vm->fn);
    PU(vm->globalsTop);
    PU((int)vm->locals);
    vm->pc = F(fn, u8*, 4);
    vm->fn = fn;
    vm->globalsTop = (int)(lbl_804CB6A8 + F(F(fn, u8*, 8), u16, 0x20));
    vm->locals = args;
    int i;
    for (i = F(fn, s8, 0xD); i < F(fn, s16, 0x12); i++) vm->locals[i] = 0;
}
}
}
