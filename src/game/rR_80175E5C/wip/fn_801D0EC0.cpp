/* fn_801D0D58: 28 of 48 words differ */
void fn_801D0D58(VM* vm, u8* fn) {
    int n = F(fn, s16, 0x12);
    int* args = vm->sp - (s8)F(fn, u8, 0xD);
    vm->sp = args + n;
    *vm->sp++ = (int)vm->pc;
    *vm->sp++ = (int)vm->fn;
    *vm->sp++ = vm->globalsTop;
    *vm->sp++ = (int)vm->locals;
    vm->pc = F(fn, u8*, 4);
    vm->fn = fn;
    vm->locals = args;
    vm->globalsTop = (int)lbl_804CB6A8 + F(F(fn, u8*, 8), u16, 0x20) * 4;
    int i;
    for (i = (s8)F(fn, u8, 0xD); i < F(fn, s16, 0x12); i++) vm->locals[i] = 0;
}

