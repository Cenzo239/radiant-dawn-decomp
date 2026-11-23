// Load the language-specific resource and remove the process once it is ready.
extern "C" {
extern const char* lbl_80392AE0[7][2];
unsigned char* fn_8024BC94(void);
int fn_801D09F0(void);
void fn_8023F1A0(const char*, int);
int fn_8023F880(const char*);
void fn_80083B78(void*);

void fn_80282720(void* process) {
    const char* (*table)[2];
    signed char language;
    language = (signed char)fn_8024BC94()[0x1BC8];
    table = lbl_80392AE0;
    fn_8023F1A0(table[language][fn_801D09F0()], 0);
    language = (signed char)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(table[language][fn_801D09F0()])) {
        fn_80083B78(process);
    }
}
}
