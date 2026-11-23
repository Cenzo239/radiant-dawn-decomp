#include <string.h>

#define K1 0x80808080
#define K2 0xfefefeff

char* strcpy(char* dst, const char* src) {
    register unsigned char *destb, *fromb;
    register unsigned long w, t, align;

    fromb = (unsigned char*)src;
    destb = (unsigned char*)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0) {
            return dst;
        }

        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0) {
                return dst;
            }
        }

        ++destb;
        ++fromb;
    }

    w = *((int*)(fromb));

    t = w + K2;
    t &= ~w;
    t &= K1;

    if (t) {
        goto bytecopy;
    }

    --((int*)(destb));

    do {
        *(++((int*)(destb))) = w;
        w = *(++((int*)(fromb)));

        t = w + K2;
        t &= ~w;
        t &= K1;

        if (t) {
            goto adjust;
        }
    } while (1);

adjust:
    ++((int*)(destb));

bytecopy:
    if ((*destb = *fromb) == 0) {
        return dst;
    }

    do {
        if ((*(++destb) = *(++fromb)) == 0) {
            return dst;
        }
    } while (1);

    return dst;
}

char* strncpy(char* destination, const char* source, size_t count) {
    const unsigned char* source_cursor = (const unsigned char*)source - 1;
    unsigned char* destination_cursor = (unsigned char*)destination - 1;
    unsigned char character;

    count = count + 1;

    while (--count != 0) {
        character = *(++source_cursor);
        *(++destination_cursor) = character;
        if (character == '\0') {
            while (--count != 0)
                *(++destination_cursor) = '\0';
            break;
        }
    }

    return destination;
}

char* strcat(char* destination, const char* source) {
    const unsigned char* source_cursor = (const unsigned char*)source - 1;
    unsigned char* result = (unsigned char*)destination - 1;
    unsigned char character;

    while (*(++result) != '\0')
        ;

    --result;
    do {
        ++source_cursor;
        ++result;
        character = *source_cursor;
        *result = character;
    } while (character != '\0');

    return destination;
}

char* strncat(char* destination, const char* source, size_t count) {
    const unsigned char* source_cursor = (const unsigned char*)source - 1;
    unsigned char* destination_cursor = (unsigned char*)destination - 1;
    unsigned char character;

    while (*(++destination_cursor) != '\0')
        ;

    --destination_cursor;
    count = count + 1;

    while (--count != 0) {
        character = *(++source_cursor);
        *(++destination_cursor) = character;
        if (character == '\0') {
            --destination_cursor;
            break;
        }
    }

    *(++destination_cursor) = '\0';
    return destination;
}

int strcmp(const char* str1, const char* str2) {
    register unsigned char* left = (unsigned char*)str1;
    register unsigned char* right = (unsigned char*)str2;
    unsigned long align, l1, r1, x;

    l1 = *left;
    r1 = *right;

    if (l1 - r1) {
        return l1 - r1;
    }

    if ((align = ((int)left & 3)) != ((int)right & 3)) {
        goto bytecopy;
    }

    if (align) {
        if (l1 == 0) {
            return 0;
        }

        for (align = 3 - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);

            if (l1 - r1) {
                return l1 - r1;
            }

            if (l1 == 0) {
                return 0;
            }
        }

        left++;
        right++;
    }

    l1 = *(int*)left;
    r1 = *(int*)right;
    x = l1 + K2;
    x &= ~l1;

    if (x & K1) {
        goto adjust;
    }

    while (l1 == r1) {
        l1 = *(++((int*)(left)));
        r1 = *(++((int*)(right)));
        x = l1 + K2;

        if (x & K1) {
            goto adjust;
        }
    }

adjust:
    l1 = *left;
    r1 = *right;

    if (l1 - r1) {
        return l1 - r1;
    }

bytecopy:
    if (l1 == 0) {
        return 0;
    }

    do {
        l1 = *(++left);
        r1 = *(++right);

        if (l1 - r1) {
            return l1 - r1;
        }

        if (l1 == 0) {
            return 0;
        }
    } while (1);
}

int strncmp(const char* str1, const char* str2, size_t n) {
    const unsigned char* p1 = (unsigned char*)str1 - 1;
    const unsigned char* p2 = (unsigned char*)str2 - 1;
    unsigned long c1, c2;

    n++;

    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return c1 - c2;
        } else if (!c1) {
            break;
        }
    }

    return 0;
}

char* strchr(const char* str, int chr) {
    const unsigned char* p = (unsigned char*)str - 1;
    unsigned long c = (chr & 0xff);
    unsigned long ch;

    while (ch = *++p) {
        if (ch == c) {
            return (char*)p;
        }
    }

    return c ? 0 : (char*)p;
}

// FE10: strtok is linked too (0x8029135C); standard MSL implementation
typedef unsigned char char_map[32];
#define set_char_map(map, ch) map[(unsigned char)ch >> 3] |= (unsigned char)(1 << (ch & 7))
#define tst_char_map(map, ch) (map[(unsigned char)ch >> 3] & (unsigned char)(1 << (ch & 7)))

char* strtok(char* str, const char* set) {
    unsigned char *p1, *p2;
    static unsigned char* n = (unsigned char*)"";
    static unsigned char* s = (unsigned char*)"";
    unsigned char c;
    char_map map = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (str) {
        s = (unsigned char*)str;
    }

    p1 = (unsigned char*)set - 1;
    while ((c = *++p1)) {
        set_char_map(map, c);
    }

    p1 = s - 1;
    while ((c = *++p1)) {
        if (!tst_char_map(map, c)) {
            break;
        }
    }

    if (!c) {
        s = n;
        return NULL;
    }

    p2 = p1;

    while ((c = *++p1)) {
        if (tst_char_map(map, c)) {
            break;
        }
    }

    if (!c) {
        s = n;
    } else {
        s = p1 + 1;
        *p1 = 0;
    }

    return (char*)p2;
}

char* strstr(const char* str, const char* pat) {
    unsigned char* s1 = (unsigned char*)str - 1;
    unsigned char* p1 = (unsigned char*)pat - 1;
    unsigned long firstc, c1, c2;

    if ((pat == 0) || (!(firstc = *++p1))) {
        return (char*)str;
    }

    while (c1 = *++s1) {
        if (c1 == firstc) {
            const unsigned char* s2 = s1 - 1;
            const unsigned char* p2 = p1 - 1;

            while ((c1 = *++s2) == (c2 = *++p2) && c1) {
            }

            if (!c2) {
                return (char*)s1;
            }
        }
    }

    return 0;
}
