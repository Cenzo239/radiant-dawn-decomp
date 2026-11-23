// Process scripts from 0x80379F58 through 0x8037A1AF. Keeping them as
// separate file statics preserves the original pooled address calculations.
extern "C" {
extern char lbl_80361628[];
extern char lbl_80361638[];
extern char lbl_80361650[];
extern char lbl_8036165C[];
extern char lbl_80361668[];
void fn_80042AE8();
void fn_80042C84();
void fn_80042D38();
void fn_80043048(void* p);
void fn_80043078(void* p);
void fn_80043208();
void fn_80043214(void* p);
void fn_800432A4();
void fn_8004333C();
#if TARGET_PC
FE10_PROTO void fn_80043418(ptr32<const void>);
#else
void fn_80043418(void* p);
#endif
void fn_8004357C();
void fn_8004361C();
void fn_800437D0();
void fn_80043BAC();
void fn_80043D3C();
void fn_80043D6C();
void fn_80043E50();
#if TARGET_PC
FE10_PROTO void fn_80044180(ptr32<const void>);
FE10_PROTO void fn_800441F0(ptr32<const void>);
#else
void fn_80044180(void* p);
void fn_800441F0(void* p);
#endif
void fn_8004425C();
void fn_80044284();
#if TARGET_PC
FE10_PROTO void fn_800443F0(ptr32<const void>);
#else
void fn_800443F0(void* p);
#endif
void fn_8004442C(void* p);
void fn_80044480(void* p);
void fn_80044850();
void fn_80044914(void* p);
void fn_80054194(void* p);
void fn_800542D8();
void fn_80054378(void* p);
void fn_80054EB4(void* p);
void fn_80054EBC(void* p);
void fn_80055350(void* p);
void fn_800556C0(void* p);
void fn_8005583C(void* p);
void fn_800787E4();
void fn_8009EBC4(void* p);
void fn_8009ECD8(void* p);
void fn_8009EEEC(void* p);
void fn_8009F1A8(void* p);
void fn_800A1D40();
void fn_800F3874();
void fn_80113370();
void fn_8012DE54();
void fn_8012FCB0();
void fn_8013E77C();
void fn_801855E0(void* p);
void fn_8019FEFC(void* p);
void* fn_80081194(void*,void*);
void* fn_80081050(void*,void*);
void fn_800CD4A4(int);
// 0x80379F58: main process script.
static void* mainScript[] = {
    (void*)0x2003,
    (void*)lbl_80361628,
    (void*)0x2004,
    (void*)fn_80044284,
    (void*)0x200F,
    (void*)fn_8004425C,
    (void*)0x5100A,
    (void*)0x1001,
    (void*)0x200F,
    (void*)fn_80043E50,
    (void*)0x1100A,
    (void*)0x100C,
    (void*)0x0
};
// 0x80379F8C: child process script.
static void* childScript[] = {
    (void*)0x2003,
    (void*)lbl_80361638,
    (void*)0x201A,
    (void*)fn_80044180,
    (void*)0x201A,
    (void*)fn_800441F0,
    (void*)0x0
};
// 0x80379FA8: parent process script.
static void* parentScript[] = {
    (void*)0x2003,
    (void*)lbl_80361650,
    (void*)0x54911001,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_80042AE8,
    (void*)0x200F,
    (void*)fn_80113370,
    (void*)0x200F,
    (void*)fn_8012DE54,
    (void*)0x200F,
    (void*)fn_800432A4,
    (void*)0x1001,
    (void*)0x2025,
    (void*)lbl_8036165C,
    (void*)0x2012,
    (void*)fn_8009EBC4,
    (void*)0x2012,
    (void*)fn_8009F1A8,
    (void*)0x2012,
    (void*)fn_8009EEEC,
    (void*)0x2012,
    (void*)fn_800A1D40,
    (void*)0x200F,
    (void*)fn_80043214,
    (void*)0x200F,
    (void*)fn_8013E77C,
    (void*)0x200F,
    (void*)fn_8004333C,
    (void*)0x200F,
    (void*)fn_80043418,
    (void*)0x100A,
    (void*)0x1206,
    (void*)0x200F,
    (void*)fn_80042C84,
    (void*)0x200F,
    (void*)fn_8004442C,
    (void*)0x2012,
    (void*)fn_80055350,
    (void*)0x2012,
    (void*)fn_800556C0,
    (void*)0x2012,
    (void*)fn_80054EB4,
    (void*)0x2012,
    (void*)fn_80054194,
    (void*)0x2012,
    (void*)fn_80054378,
    (void*)0x2012,
    (void*)fn_800542D8,
    (void*)0x2012,
    (void*)fn_8005583C,
    (void*)0x200F,
    (void*)fn_80044480,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800443F0,
    (void*)0x200F,
    (void*)fn_8004333C,
    (void*)0x1206,
    (void*)0x2025,
    (void*)lbl_80361668,
    (void*)0x2012,
    (void*)fn_8009ECD8,
    (void*)0x41001,
    (void*)0x200F,
    (void*)fn_80043048,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_80043078,
    (void*)0x100A,
    (void*)0x2012,
    (void*)fn_80054EBC,
    (void*)0x200F,
    (void*)fn_80042D38,
    (void*)0x51001,
    (void*)0x200F,
    (void*)fn_80043208,
    (void*)0x100C,
    (void*)0x11001,
    (void*)0x2025,
    (void*)lbl_80361628,
    (void*)0x200F,
    (void*)fn_801855E0,
    (void*)0x100A,
    (void*)0x16120B,
    (void*)0x200F,
    (void*)fn_8004357C,
    (void*)0x200F,
    (void*)fn_800437D0,
    (void*)0x200F,
    (void*)fn_8004361C,
    (void*)0x200F,
    (void*)fn_80043D6C,
    (void*)0x6100C,
    (void*)0x21001,
    (void*)0x2025,
    (void*)lbl_80361628,
    (void*)0x200F,
    (void*)fn_80043BAC,
    (void*)0x200F,
    (void*)fn_80043D6C,
    (void*)0x17120B,
    (void*)0x6100C,
    (void*)0x31001,
    (void*)0x200F,
    (void*)fn_8012FCB0,
    (void*)0x28100A,
    (void*)0x2025,
    (void*)lbl_80361628,
    (void*)0x200F,
    (void*)fn_8019FEFC,
    (void*)0x200F,
    (void*)fn_80043D3C,
    (void*)0x100A,
    (void*)0x1C120B,
    (void*)0x61001,
    (void*)0x200F,
    (void*)fn_80044914,
    (void*)0x100A,
    (void*)0x200F,
    (void*)fn_800F3874,
    (void*)0x200F,
    (void*)fn_80044850,
    (void*)0x100A,
    (void*)0x110F,
    (void*)0x200F,
    (void*)fn_800787E4,
    (void*)0x200F,
    (void*)fn_800787E4,
    (void*)0x0
};
void fn_80044530(void* parent) {
    fn_80081194(childScript, fn_80081050(mainScript, fn_80081194(parentScript, parent)));
    fn_800CD4A4(0x13);
}
}
