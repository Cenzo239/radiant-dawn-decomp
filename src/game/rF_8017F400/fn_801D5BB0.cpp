/* fn_801D5BB0: help window text setup. Resolves the message id at +0x64 into the string at +0x40; in the base
   (lbl_8041EB20 state) it rewrites the text: with mode 0 the part after "#P" is cut and MESS_BASE_HELP_STR appended,
   otherwise the text is cleared. Then the common open (fn_801D5914). */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

/* Small-string layout: top bit of the first byte means heap. */
struct Str {
    union {
        u32 w;
        struct {
            u8 l;
            char d[11];
        } s;
        struct {
            u32 cap;
            u32 len;
            char* ptr;
        } h;
    };
};

struct HelpWin {
    u8 pad0[0x40];
    Str text;
    u8 pad4C[0x64 - 0x4C];
    const char* mid;
};

struct BaseSt {
    u8 pad0[0xD8];
    s16 mode;
};

#pragma pool_strings on
struct Tag { Tag() {} char c; };
extern "C" {
extern BaseSt lbl_8041EB20;
int strlen(const char*);
char* strcpy(char*, const char*);
char* fn_80291480(const char*, const char*); /* strstr */
char* fn_80291110(char*, const char*);       /* strcat */
void fn_800250B0(Str*, int, u32, const char*, const char*, Tag);
const char* fn_800D0864(const char*);
int fn_801A2224(BaseSt*);
#if TARGET_PC
FE10_PROTO void fn_801D5914(HelpWin*, p32arg);
#else
void fn_801D5914(HelpWin*, int);
#endif
void fn_801D5BB0(HelpWin* w, int a);
}

static inline bool Small(const Str* s) { return !(s->w >> 31); }
static inline u32 Size(const Str* s) { if (Small(s)) return s->s.l & 0x7F; return s->h.len; }
static inline const char* CStr(const Str* s) { if (Small(s)) return s->s.d; return s->h.ptr; }
static inline u32 Len(const char* p) { return strlen(p); }
static inline void Assign(Str* s, const char* p) {
    Tag t;
    fn_800250B0(s, 0, Size(s), p, p + Len(p), t);
}
void fn_801D5BB0(HelpWin* w, int a) {
    char buf[0x108];
    if (w->mid != 0) {
        Assign(&w->text, fn_800D0864(w->mid));
    }
    if (fn_801A2224(&lbl_8041EB20) && w->mid != 0) {
        if (lbl_8041EB20.mode == 0) {
            strcpy(buf, CStr(&w->text));
            char* p = fn_80291480(buf, "#P");
            if (p == 0) goto done;
            p[5] = 0;
            fn_80291110(buf, fn_800D0864("MESS_BASE_HELP_STR"));
        } else {
            strcpy(buf, "");
        }
        Assign(&w->text, buf);
    }
done:
    fn_801D5914(w, a);
}
