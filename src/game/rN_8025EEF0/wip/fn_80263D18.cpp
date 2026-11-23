/* fn_80263D18 (12 words) and fn_80263DE0 (10 words): loop-register colours and load of *s after the store. */
/* copies text into lines, skipping the 02 'm' 'c' and 02 'm' 'd' control sequences */
void fn_80263D18(const char* s) {
/*P*/
    int col;
    int n;
    int ofs;
    int c;
    char* l;
/*E*/
    col = 0;
    n = 0;
    ofs = 0;
    for (;;) {
        c = *(u8*)s;
        if ((c == 2 && s[1] == 'm' && s[2] == 'c') || ((s8)c == 2 && s[1] == 'm' && s[2] == 'd')) {
            s += 3;
        } else if ((s8)c == 0 || (s8)c == '\n') {
            n++;
            l = *(char**)((u8*)lbl_804CC004->lines + ofs);
            ofs += 4;
            l[col] = 0;
            if (*s == 0) {
                break;
            }
            col = 0;
            s++;
        } else {
            s++;
            (*(char**)((u8*)lbl_804CC004->lines + ofs))[col] = c;
            col++;
        }
    }
    lbl_804CC004->nlines = n;
}

void fn_80263DE0(const char* s) {
/*P*/
    int col;
    int n;
    int ofs;
    int c;
    char* l;
/*E*/
    col = 0;
    n = 0;
    ofs = 0;
    for (;;) {
        c = *(u8*)s;
        if ((s8)c == 0 || (s8)c == '\n') {
            n++;
            l = *(char**)((u8*)lbl_804CC008->lines + ofs);
            ofs += 4;
            l[col] = 0;
            if (*s == 0) {
                break;
            }
            col = 0;
            s++;
        } else {
            s++;
            (*(char**)((u8*)lbl_804CC008->lines + ofs))[col] = c;
            col++;
        }
    }
    lbl_804CC008->nlines = n;
}

