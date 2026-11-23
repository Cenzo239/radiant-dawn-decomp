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
#else
void fn_800C3584(int);
#endif
#if TARGET_PC
FE10_PROTO u8* fn_80076F54(p32arg);
#else
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
void fn_801D0EC0(VM* vm) {
    vm->halt = 0;
    fn_800C3584(0);
    while (vm->halt == 0) {
        int ret;
        switch (*vm->pc++) {
        case 1:
            Push(vm->locals[Fetch8()]);
            continue;
        case 2:
            Push(vm->locals[Fetch16()]);
            continue;
        case 3: {
            int i = Pop();
            int k = Fetch8();
            Push(vm->locals[k + i]);
            continue;
        }
        case 4: {
            int k = Fetch16();
            int i = Pop();
            Push(vm->locals[k + i]);
            continue;
        }
        case 5: {
            int i = Pop();
            Push(((int*)vm->locals[Fetch8()])[i]);
            continue;
        }
        case 6: {
            int i = Pop();
            Push(((int*)vm->locals[Fetch16()])[i]);
            continue;
        }
        case 7:
            Push((int)&vm->locals[Fetch8()]);
            continue;
        case 8:
            Push((int)&vm->locals[Fetch16()]);
            continue;
        case 9: {
            int i = Pop();
            Push((int)(&vm->locals[Fetch8()] + i));
            continue;
        }
        case 10: {
            int i = Pop();
            Push((int)(&vm->locals[Fetch16()] + i));
            continue;
        }
        case 0xB: {
            int i = Pop();
            Push((int)&((int*)vm->locals[Fetch8()])[i]);
            continue;
        }
        case 0xC: {
            int i = Pop();
            Push((int)&((int*)vm->locals[Fetch16()])[i]);
            continue;
        }
        case 0xD:
            { int k = Fetch8(); Push(lbl_804CB6A8[k]); }
            continue;
        case 0xE:
            Push(lbl_804CB6A8[Fetch16()]);
            continue;
        case 0xF: {
            int i = Pop();
            int k = Fetch8();
            Push(lbl_804CB6A8[k + i]);
            continue;
        }
        case 0x10: {
            int k = Fetch16();
            int i = Pop();
            Push(lbl_804CB6A8[k + i]);
            continue;
        }
        case 0x11: {
            int i = Pop();
            int k = Fetch8();
            Push(((int*)lbl_804CB6A8[k])[i]);
            continue;
        }
        case 0x12: {
            int i = Pop();
            Push(((int*)lbl_804CB6A8[Fetch16()])[i]);
            continue;
        }
        case 0x13:
            { int k = Fetch8(); Push((int)&lbl_804CB6A8[k]); }
            continue;
        case 0x14:
            Push((int)&lbl_804CB6A8[Fetch16()]);
            continue;
        case 0x15: {
            int i = Pop();
            int k = Fetch8();
            Push((int)(&lbl_804CB6A8[k] + i));
            continue;
        }
        case 0x16: {
            int i = Pop();
            Push((int)(&lbl_804CB6A8[Fetch16()] + i));
            continue;
        }
        case 0x17: {
            int i = Pop();
            int k = Fetch8();
            Push((int)&((int*)lbl_804CB6A8[k])[i]);
            continue;
        }
        case 0x18: {
            int i = Pop();
            Push((int)&((int*)lbl_804CB6A8[Fetch16()])[i]);
            continue;
        }
        case 0x19:
            Push(Fetch8());
            continue;
        case 0x1A:
            Push(Fetch16());
            continue;
        case 0x1B: {
            Push(Fetch32_(vm));
            continue;
        }
        case 0x1C:
            { int k = Fetch8(); Push(STRBASE + k); }
            continue;
        case 0x1D:
            Push(STRBASE + Fetch16());
            continue;
        case 0x1E: {
            int v = Fetch32_(vm);
            Push(STRBASE + v);
            continue;
        }
        case 0x1F: {
            int* s = vm->sp;
            Push(*(int*)s[-1]);
            continue;
        }
        case 0x44: {
            int v = vm->sp[-1];
            *vm->sp++ = v;
            continue;
        }
        case 0x20:
            vm->sp--;
            continue;
        case 0x21: {
            int v = Pop();
            *(int*)Pop() = v;
            Push(v);
            continue;
        }
        case 0x47: {
            int v = Pop();
            *(int*)Pop() = v;
            continue;
        }
        case 0x22: BIN(a + b)
        case 0x23: BIN(a - b)
        case 0x24: BIN(a * b)
        case 0x25: BIN(a / b)
        case 0x26: BIN(a % b)
        case 0x27: {
            int a = Pop();
            Push(-a);
            continue;
        }
        case 0x28: {
            int a = Pop();
            Push(~a);
            continue;
        }
        case 0x29: {
            int a = Pop();
            Push(!a);
            continue;
        }
        case 0x2A: BIN(a | b)
        case 0x2B: BIN(b & a)
        case 0x2C: BIN(b ^ a)
        case 0x2D: BIN(a << b)
        case 0x2E: BIN(a >> b)
        case 0x42:
            {
                int v = *(int*)*(vm->sp - 1);
                vm->sp--;
                *(int*)*vm->sp = v + 1;
            }
            continue;
        case 0x43:
            {
                int v = *(int*)*(vm->sp - 1);
                vm->sp--;
                *(int*)*vm->sp = v - 1;
            }
            continue;
        case 0x2F: BIN(a == b)
        case 0x30: BIN(a != b)
        case 0x31: BIN(a < b)
        case 0x32: BIN(a <= b)
        case 0x33: BIN(a > b)
        case 0x34: BIN(a >= b)
        case 0x35: {
            char* b = (char*)Pop();
            char* a = (char*)Pop();
            Push(StrEq(a, b));
            continue;
        }
        case 0x36: {
            char* b = (char*)Pop();
            char* a = (char*)Pop();
            Push(!StrEq(a, b));
            continue;
        }
        case 0x37: {
            int i = Fetch8();
            if (i < 0) i = ((i & 0x7F) << 8) + *vm->pc++;
            fn_801D0D58(vm, ((u8**)F(F(vm->fn, u8*, 8), int, 0x28))[i]);
            continue;
        }
        case 0x38: {
            u8* e = fn_80076F54(STRBASE + Fetch16());
            int n = (s8)*vm->pc++;
            if (e == NULL) {
                vm->sp -= n;
                Push(0);
                fn_800C3584(0);
            } else if (F(e, int, 8) == 0) {
                fn_801D20D4(vm, e);
            } else {
                fn_801D0D58(vm, e);
            }
            continue;
        }
        case 0x39:
            ret = Pop();
        common: {
            int n = F(vm->fn, s16, 0x12) * 4;
            vm->sp = (int*)((u8*)vm->locals + n) + 3;
            vm->locals = (int*)*vm->sp--;
            vm->globalsTop = *vm->sp--;
            vm->fn = (u8*)*vm->sp--;
            vm->pc = (u8*)*vm->sp;
            vm->sp = (int*)((u8*)vm->sp - n);
            Push(ret);
            if (vm->pc != NULL) continue;
            return;
        }
        case 0x45:
            ret = 0;
            goto common;
        case 0x46:
            ret = 1;
            goto common;
        case 0x3A: {
            int k = Fetch16();
            vm->pc = (u8*)(k + (int)vm->pc - 2);
            continue;
        }
        case 0x3B:
            if (Pop() == 0) {
                vm->pc += 2;
            } else {
                int k = Fetch16();
                vm->pc = (u8*)(k + (int)vm->pc - 2);
            }
            continue;
        case 0x3C:
            if (Pop() == 0) {
                vm->pc += 2;
            } else {
                Push(1);
                int k = Fetch16();
                vm->pc = (u8*)(k + (int)vm->pc - 2);
            }
            continue;
        case 0x3D:
            if (Pop() != 0) {
                vm->pc += 2;
            } else {
                int k = Fetch16();
                vm->pc = (u8*)(k + (int)vm->pc - 2);
            }
            continue;
        case 0x3E:
            if (Pop() != 0) {
                vm->pc += 2;
            } else {
                Push(0);
                int k = Fetch16();
                vm->pc = (u8*)(k + (int)vm->pc - 2);
            }
            continue;
        case 0x3F:
            vm->halt = 1;
            continue;
        case 0x40:
            vm->pc += 4;
            continue;
        case 0x41: {
            int n = Fetch8();
            vm->sp -= n;
            continue;
        }
        default:
            fn_801D2378(vm);
            continue;
        }
    }
    if (vm->halt) {
        Push(0);
        fn_800C3584(6);
    }
}

#if TARGET_PC
FE10_PROTO p32ret fn_800C3558(void);
#else
int fn_800C3558();
#endif
#if TARGET_PC
FE10_PROTO void fn_800C3560(p32arg);
#else
void fn_800C3560(int);
#endif

#define CALLN(T, args) { int r = ((int (*) T)F(fn, void*, 4)) args; int* s = vm->sp; *s = r; vm->sp = s + 1; break; }
void fn_801D20D4(VM* vm, u8* fn) {
    int saved = fn_800C3558();
    fn_800C3560((int)vm);
    vm->s1E = 1;
    vm->s1F = 0;
    vm->sp -= (s8)F(fn, u8, 0xD);
    int* a = vm->sp;
    switch ((s8)F(fn, u8, 0xD)) {
    case 0: CALLN((), ())
    case 1: CALLN((int), (a[0]))
    case 2: CALLN((int, int), (a[0], a[1]))
    case 3: CALLN((int, int, int), (a[0], a[1], a[2]))
    case 4: CALLN((int, int, int, int), (a[0], a[1], a[2], a[3]))
    case 5: CALLN((int, int, int, int, int), (a[0], a[1], a[2], a[3], a[4]))
    case 6: CALLN((int, int, int, int, int, int), (a[0], a[1], a[2], a[3], a[4], a[5]))
    case 7: CALLN((int, int, int, int, int, int, int), (a[0], a[1], a[2], a[3], a[4], a[5], a[6]))
    case 8: CALLN((int, int, int, int, int, int, int, int), (a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]))
    case 9: CALLN((int, int, int, int, int, int, int, int, int), (a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]))
    }
    if (vm->s1F == 0) fn_800C3560(saved);
}

void fn_801D0C20(VM* vm) {
    vm->sp = vm->stackBase;
    vm->globalsTop = 0;
    vm->locals = 0;
    vm->pc = 0;
    vm->fn = 0;
    vm->halt = 0;
    vm->argc = 0;
}

int fn_801D0C88(VM* vm, const char* name) {
    fn_800C3584(0);
    u8* e = fn_80076F54((int)name);
    if (e == NULL) {
        fn_800C3584(5);
        int n = vm->argc;
        int* s = vm->sp;
        vm->argc = 0;
        vm->sp = s + n;
        return 0;
    }
    vm->argc = 0;
    if (F(e, int, 8) == 0) {
        fn_801D20D4(vm, e);
        return *--vm->sp;
    }
    fn_801D0D58(vm, e);
    fn_801D0EC0(vm);
    return *--vm->sp;
}

}
