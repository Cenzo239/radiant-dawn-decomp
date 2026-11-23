/* Support partner list for a unit, from the script's kind 8 entries. */
#include "game/rD_8008E3B4/evflags.h"

extern "C" {

u8* fn_800C3558(void);
u8* fn_800C3BC8(void* p);
int fn_801D0C88(void* ctx, void* v);
void* fn_8010B1D8(void* x);
u8* fn_8012CECC(void* pid);
int fn_8011F5B4(void* u);
int fn_8011F680(void* u);
int fn_8011F6F8(void* u);

#pragma push
#pragma use_lmw_stmw on
int fn_8009DBE4(u8* unit, u8** out, int n, int mode)
{
    /*P*/
    char* name;
    int count;
    u8* p;
    u8* other;
    int i;
/*E*/
    count = 0;
    for (i = 0; i < n; i++) {
        out[i] = NULL;
    }
    p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == 8) {
            name = *(char**)(*(u8**)(p + 8) + 0x24) + *(u16*)(p + 0x1a);
            if (name != NULL && *name != 0) {
                if (flagHas(&lbl_803CAB38, (const char*)name)) {
                    if (!flagGet(&lbl_803CAB38, (const char*)name)) {
                        goto go;
                    }
                    goto next;
                } else if (!fn_801D0C88(fn_800C3558(), name)) {
                    goto next;
                }
            }
        go:
            {
                void* a = fn_8010B1D8(*(char**)(*(u8**)(p + 8) + 0x24) + *(u16*)(p + 0x14));
                void* b = fn_8010B1D8(*(char**)(*(u8**)(p + 8) + 0x24) + *(u16*)(p + 0x16));
                void* pid = *(void**)(unit + 0xec);
                void* m;
                if (pid == a) {
                    m = b;
                } else {
                    if (*(s16*)(p + 0x18) == 0 || pid != b) {
                        goto next;
                    }
                    m = a;
                }
                other = fn_8012CECC(m);
            }
            if (other != NULL) {
                if (mode) {
                    if (!fn_8011F5B4(other)) {
                        goto next;
                    }
                    if (fn_8011F680(other)) {
                        goto next;
                    }
                    if (!fn_8011F6F8(other)) {
                        goto app;
                    }
                    goto next;
                } else if ((*(u8**)(other + 0xf4))[8] == 6) {
                    goto next;
                }
            app:
                out[count++] = other;
                if (count == n) {
                    break;
                }
            }
        }
    next:
        p = fn_800C3BC8(p);
    }
    return count;
}
#pragma pop

}
