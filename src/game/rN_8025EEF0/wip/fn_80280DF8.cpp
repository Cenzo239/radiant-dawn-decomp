/* fn_80280DF8: dead cmpwi r3,0 at the end. fn_80282720: base r31, lang r30. fn_802889AC: no tail call in the original although the call is last. */
static inline void emptyInit(void*) {}
void fn_80280DF8(void* parent) {
    if (fn_80291188(*(const char**)fn_8006074C(lbl_803CAB38), lbl_803738BC + 0x73) == 0) {
        void* p = fn_80081050(lbl_80392A68, parent);
        if (p != 0) {
            emptyInit(p);
        }
    }
}


extern const char* lbl_80392AE0[][2];
void fn_80282720(void* p) {
    const char* (*tbl)[2];
    int lang;
    lang = (s8)fn_8024BC94()[0x1BC8];
    tbl = lbl_80392AE0;
    fn_8023F1A0(tbl[lang][fn_801D09F0()], 0);
    lang = (s8)fn_8024BC94()[0x1BC8];
    if (fn_8023F880(tbl[lang][fn_801D09F0()]) != 0) {
        fn_80083B78(p);
    }
}


void fn_802889AC(void* parent) { void* p = fn_80081194(lbl_80392D50, parent); if (p != 0) { emptyInit(p); } }

