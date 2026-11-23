#include "game/rS_8023FD30/types.h"
/* Writes the id tables of the save header: persons, jobs, items, skills, then named data tables. */
extern "C" {
extern int lbl_804CB790;
extern int lbl_804CB798;
extern int lbl_804CB7A0;
extern int lbl_804CB7A8;
extern char lbl_80372B4C[];
void fn_8008A5E4(void*, int);
void fn_8008A71C(void*, const char*);
void* fn_8010B1B4(int);
void* fn_8010B1DC(int);
void* fn_8010B204(int);
void* fn_8010B22C(int);
const char* fn_80118DE8(void*);
const char* fn_8011927C(void*);
#if TARGET_PC
FE10_PROTO ptr32<const char> fn_8010F5B4(void*);
#else
const char* fn_8010F5B4(void*);
#endif
const char* fn_8011A028(void*);
const char** fn_80077064(const char*);

#define TBL(ofs, skip) { \
    int n = 0; \
    const char** p = fn_80077064(lbl_80372B4C + ofs); \
    const char** q = p; \
    while (*q != 0) { q++; n++; } \
    fn_8008A5E4(s, n); \
    while (*p != 0) { fn_8008A71C(s, *p + skip); p++; } \
}
void fn_80242920(void* s) {
    int i;
    int n;
    n = lbl_804CB790;
    fn_8008A5E4(s, n);
    for (i = 1; i <= n; i++) {
        fn_8008A71C(s, fn_80118DE8(fn_8010B1B4(i)));
    }
    n = lbl_804CB798;
    fn_8008A5E4(s, n);
    for (i = 1; i <= n; i++) {
        fn_8008A71C(s, fn_8011927C(fn_8010B1DC(i)));
    }
    n = lbl_804CB7A0;
    fn_8008A5E4(s, n);
    for (i = 1; i <= n; i++) {
        fn_8008A71C(s, fn_8010F5B4(fn_8010B204(i)));
    }
    n = lbl_804CB7A8;
    fn_8008A5E4(s, n);
    for (i = 0; i < n; i++) {
        fn_8008A71C(s, fn_8011A028(fn_8010B22C(i)));
    }
    TBL(0, 4)
    TBL(0xF, 4)
    TBL(0x1E, 4)
    TBL(0x2E, 6)
}
}
