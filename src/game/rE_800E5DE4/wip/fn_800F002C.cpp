/* fn_800F002C: 7 of 504 words. Only the first Lookup (case 1 of the first switch) has i and n swapped: the original has i r31, n r28. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct Pair { const char* name; int v; } Pair;
typedef struct Unit { struct UData* d; } Unit;
typedef struct UData { u8 pad[0x12]; u8 kind; } UData;
typedef struct UF { u32 f0; u32 f4; } UF;

extern "C" {
extern void* lbl_804CB7C4;
extern u32 fn_80109A2C(void**);
extern int fn_80291188(const char*, const char*);
extern u8 fn_801108D8(UData*);
extern UF* fn_801116B8(Unit*);

#pragma pool_strings on
void pool_74b4() {
    const char* volatile s;
    s = "\x83""T\x83""E\x83""\x93""\x83""h\x8c""n"; /* 0x0 */
    s = "\x83""G\x83""t\x83""F\x83""N\x83""g\x8c""n"; /* 0xb */
    s = "\x91""\xc5""\x8c""\x82""\x94""\xad""\x90""\xb6"""; /* 0x18 */
    s = "\x89""\xf1""\x94""\xf0""\x94""\xad""\x90""\xb6"""; /* 0x21 */
    s = "\x96""\x82""\x96""@\x94""\xad""\x90""\xb6"""; /* 0x2a */
    s = "\x83""\x8a""\x83""s\x81""[\x83""g\x8a""J\x8e""n"; /* 0x33 */
    s = "\x83""\x8a""\x83""s\x81""[\x83""g\x8f""I\x97""\xb9"""; /* 0x40 */
    s = "\x8e""\x9f""\x82""\xc9""\x90""i\x82""\xde"""; /* 0x4d */
    s = "\x91""O\x82""\xc9""\x96""\xdf""\x82""\xe9"""; /* 0x56 */
    s = "\x8a""J\x8e""n"; /* 0x5f */
    s = "\x88""\xea""\x8e""\x9e""\x92""\xe2""\x8e""~"; /* 0x64 */
    s = "\x88""\xea""\x8f""u\x97""h\x82""\xe7""\x82""\xb7"""; /* 0x6d */
    s = "\x97""h\x82""\xea""\x8a""J\x8e""n"; /* 0x78 */
    s = "\x97""h\x82""\xea""\x92""\xe2""\x8e""~"; /* 0x81 */
    s = "\x83""W\x83""\x83""\x83""\x93""\x83""v"; /* 0x8a */
    s = "\x92""\x85""\x92""n"; /* 0x93 */
    s = "\x8e""\x9d""\x82""\xc2"""; /* 0x98 */
    s = "\x8b""\xdf""\x82""\xc3""\x82""\xad"""; /* 0x9d */
    s = "\x97""\xa3""\x82""\xea""\x82""\xe9"""; /* 0xa4 */
    s = "\x90""\xd8""\x82""\xe8""\x91""\xd6""\x82""\xa6"""; /* 0xab */
    s = "\x94""\xad""\x8e""\xcb"""; /* 0xb4 */
    s = "\x93""\x9e""\x92""B"; /* 0xb9 */
    s = "\x96""\x82""\x96""@\x95""\xb2""\x8a""J\x8e""n"; /* 0xbe */
    s = "\x96""\x82""\x96""@\x95""\xb2""\x8f""I\x97""\xb9"""; /* 0xc9 */
    s = "\x94""\xad""\x93""\xae""\x83""G\x83""t\x83""F\x83""N\x83""g\x8a""J\x8e""n"; /* 0xd4 */
    s = "\x96""\xda""\x83""p\x83""`\x90""\xdd""\x92""\xe8"""; /* 0xe7 */
    s = "\x83""X\x83""L\x83""b\x83""v"; /* 0xf2 */
    s = "\x83""A\x83""j\x83""\x81""\x8d""\xc4""\x90""\xb6""\x91""\xac""\x93""x"; /* 0xfb */
    s = "\x83""t\x83""H\x81""[\x83""J\x83""X\x90""\xdd""\x92""\xe8"""; /* 0x10a */
    s = "\x8c""\x87""\x94""\xd4"""; /* 0x119 */
    s = "30FPS\x89""\xbb"""; /* 0x11e */
    s = "\x96""\xdf""\x82""\xb7"""; /* 0x126 */
    s = "\x83""\x89""\x83""x\x83""\x8b""\x82""\xc9""\x88""\xda""\x93""\xae"""; /* 0x12b */
    s = "\x83""\x89""\x83""x\x83""\x8b"""; /* 0x138 */
    s = "\x83""|\x83""C\x83""\x93""\x83""g\x83""t\x83""\x89""\x83""b\x83""V\x83""\x85"""; /* 0x13f */
    s = "\x83""|\x83""C\x83""\x93""\x83""g\x83""\x89""\x83""C\x83""g\x8c""\xf5""\x8e""n\x82""\xdf""\x82""\xe9"""; /* 0x152 */
    s = "\x83""|\x83""C\x83""\x93""\x83""g\x83""\x89""\x83""C\x83""g\x88""\xc3""\x82""\xad""\x82""\xc8""\x82""\xe9"""; /* 0x169 */
    s = "\x89""\x8c""(\x92""\xca""\x8f""\xed"")"; /* 0x180 */
    s = "\x89""\x8c""(\x92""\x85""\x92""n)"; /* 0x189 */
    s = "\x89""\x8c""(\x8e""\xce""\x82""\xdf"")"; /* 0x192 */
    s = "\x89""\x8c""(\x92""\xbc""\x90""\xfc"")"; /* 0x19b */
    s = "\x83""R\x83""\x93""\x83""g\x83""\x8d""\x81""[\x83""\x89""\x81""[\x82""\xaa""\x90""k\x82""\xa6""\x82""\xe9"""; /* 0x1a4 */
    s = "\x91""\xab""\x89""\xb9"""; /* 0x1bb */
    s = "\x94""\xf2""\x82""\xd1""\x89""z\x82""\xa6""\x83""W\x83""\x83""\x83""\x93""\x83""v"; /* 0x1c0 */
    s = "\x96""\xdf""\x82""\xe8""\x83""W\x83""\x83""\x83""\x93""\x83""v"; /* 0x1d1 */
    s = "\x94""\xf2""\x82""\xd1""\x89""z\x82""\xa6""\x92""\x85""\x92""n"; /* 0x1de */
    s = "\x96""\xdf""\x82""\xe8""\x92""\x85""\x92""n"; /* 0x1eb */
    s = "\x8b""\xe6""\x90""\xd8""\x82""\xe8"""; /* 0x1f4 */
    s = "\x83""t\x83""F\x81""[\x83""h\x83""A\x83""E\x83""g"; /* 0x1fb */
    s = "\x83""t\x83""F\x81""[\x83""h\x83""C\x83""\x93"""; /* 0x20a */
    s = "\x95""\x90""\x8a""\xed""\x8c""\xf5""\x82""\xe9""\x81""i\x8f""\xac""\x82""\xb3""\x82""\xa2""\x81""j"; /* 0x217 */
    s = "\x95""\x90""\x8a""\xed""\x8c""\xf5""\x82""\xe9""\x81""i\x91""\xe5""\x82""\xab""\x82""\xa2""\x81""j"; /* 0x22a */
    s = "\x8f""\xe3""\x89""\xba""\x89""\x9f""\x82""\xb5"""; /* 0x23d */
    s = "\x8d""\xb6""\x89""E\x89""\x9f""\x82""\xb5"""; /* 0x246 */
    s = "\x8f""\xe3""\x8f""\xb8""\x82""\xcc""\x8b""\xe6""\x90""\xd8""\x82""\xe8"""; /* 0x24f */
    s = "\x89""\xba""\x8d""~\x82""\xcc""\x8b""\xe6""\x90""\xd8""\x82""\xe8"""; /* 0x25c */
    s = "\x8f""\xe3""\x95""\xfb""\x8c""\xfc""\x82""\xcc""\x83""W\x83""\x83""\x83""\x93""\x83""v\x8a""J\x8e""n"; /* 0x269 */
    s = "\x8f""\xe3""\x95""\xfb""\x8c""\xfc""\x82""\xcc""\x83""W\x83""\x83""\x83""\x93""\x83""v\x8f""I\x97""\xb9"""; /* 0x27e */
    s = "\x89""\xba""\x95""\xfb""\x8c""\xfc""\x82""\xcc""\x83""W\x83""\x83""\x83""\x93""\x83""v\x8a""J\x8e""n"; /* 0x293 */
    s = "\x89""\xba""\x95""\xfb""\x8c""\xfc""\x82""\xcc""\x83""W\x83""\x83""\x83""\x93""\x83""v\x8f""I\x97""\xb9"""; /* 0x2a8 */
    s = "\x83""\x86""\x83""j\x83""b\x83""g\x82""\xcc""\x88""\xda""\x93""\xae""\x8c""\xc0""\x8a""E\x89""\xf0""\x8f""\x9c"""; /* 0x2bd */
    s = "\x83""\x86""\x83""j\x83""b\x83""g\x82""\xcc""\x88""\xda""\x93""\xae""\x8c""\xc0""\x8a""E\x97""L\x8c""\xf8"""; /* 0x2d4 */
    s = "\x83""\x89""\x83""C\x83""g\x95""\xcf""\x89""\xbb"""; /* 0x2eb */
    s = "\x93""|\x82""\xea""\x92""\x85""\x92""n"; /* 0x2f6 */
    s = "\x90""\x81""\x82""\xc1""\x94""\xf2""\x82""\xd1""\x92""\x85""\x92""n"; /* 0x2ff */
    s = "\x8b""O\x90""\xd5""\x8a""J\x8e""n"; /* 0x30c */
    s = "\x8b""O\x90""\xd5""\x8f""I\x97""\xb9"""; /* 0x315 */
    s = "\x83""J\x83""\x89""\x81""[\x90""\xdd""\x92""\xe8""(Param=RGB565)"; /* 0x31e */
    s = "\x93""\xa7""\x96""\xbe""\x93""x\x90""\xdd""\x92""\xe8""(Param=0\x81""`255)"; /* 0x337 */
    s = "\x83""|\x83""X\x83""g\x83""G\x83""t\x83""F\x83""N\x83""g\x92""\xe2""\x8e""~"; /* 0x350 */
    s = "\x83""u\x83""\x89""\x81""["; /* 0x365 */
    s = "\x82""\xda""\x82""\xa9""\x82""\xb5"""; /* 0x36c */
    s = "\x83""N\x83""\x8d""\x83""X\x83""t\x83""F\x81""[\x83""h\x91""S\x96""\xca"""; /* 0x373 */
    s = "\x83""O\x83""\x8d""\x81""["; /* 0x386 */
    s = "\x83""O\x83""\x8c""\x81""["; /* 0x38d */
    s = "\x83""Y\x81""[\x83""\x80""\x83""C\x83""\x93"""; /* 0x394 */
    s = "\x83""Y\x81""[\x83""\x80""\x83""A\x83""E\x83""g"; /* 0x39f */
    s = "\x94""\xed""\x8e""\xca""\x8a""E\x90""[\x93""x\x81""i\x89""\x93""\x8b""\x97""\x97""\xa3""\x81""j"; /* 0x3ac */
    s = "\x94""\xed""\x8e""\xca""\x8a""E\x90""[\x93""x\x81""i\x8b""\xdf""\x8b""\x97""\x97""\xa3""\x81""j"; /* 0x3c1 */
    s = "\x90""[\x93""x\x95""`\x89""\xe6"""; /* 0x3d6 */
    s = "\x94""\xbd""\x93""]"; /* 0x3df */
    s = "\x94""g"; /* 0x3e4 */
    s = "\x83""Z\x83""s\x83""A"; /* 0x3e7 */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x93""\xa7""\x96""\xbe""\x81""j"; /* 0x3ee */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x94""\xbc""\x93""\xa7""\x96""\xbe""\x81""j"; /* 0x3fd */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x95""s\x93""\xa7""\x96""\xbe""\x81""j"; /* 0x40e */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x94""\x92""\x81""j"; /* 0x41f */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x8d""\x95""\x81""j"; /* 0x42c */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x8a""D\x81""j"; /* 0x439 */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x90""\xd4""\x81""j"; /* 0x446 */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x97""\xce""\x81""j"; /* 0x453 */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x90""\xc2""\x81""j"; /* 0x460 */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x89""\xa9""\x81""j"; /* 0x46d */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x8e""\x87""\x81""j"; /* 0x47a */
    s = "\x83""J\x83""\x89""\x81""[\x81""i\x90""\x85""\x81""j"; /* 0x487 */
    s = "\x83""G\x83""\x89""\x81""["; /* 0x494 */
    s = "\x8e""\xe8""\x91""\x84"""; /* 0x49b */
    s = "\x82""\xc8""\x82""\xb5"""; /* 0x4a0 */
    s = "OFF"; /* 0x4a5 */
    s = "\x8e""\xe8""\x95""\x80"""; /* 0x4a9 */
    s = "\x8f""\xf1"""; /* 0x4ae */
    s = "\x8c""\x95"""; /* 0x4b1 */
    s = "\x91""\x84"""; /* 0x4b4 */
    s = "\x95""\x80"""; /* 0x4b7 */
    s = "\x8b""|"; /* 0x4ba */
    s = "\x83""{\x83""E\x83""K\x83""\x93"""; /* 0x4bd */
    s = "\x91""f\x8e""\xe8"""; /* 0x4c6 */
    s = "sw"; /* 0x4cb */
    s = "sp"; /* 0x4ce */
    s = "ja"; /* 0x4d1 */
    s = "ax"; /* 0x4d4 */
    s = "ha"; /* 0x4d7 */
    s = "bw"; /* 0x4da */
    s = "rd"; /* 0x4dd */
    s = "bg"; /* 0x4e0 */
    s = "ex"; /* 0x4e3 */
    s = "ironsword"; /* 0x4e6 */
    s = "ironlance"; /* 0x4f0 */
    s = "handspear"; /* 0x4fa */
    s = "ironaxe"; /* 0x504 */
    s = "handaxe"; /* 0x50c */
    s = "ironbow"; /* 0x514 */
    s = "%s%s/pack.cmp"; /* 0x51c */
    s = "ymu/"; /* 0x52a */
    s = "%s%s/%s.pak"; /* 0x52f */
    s = "%s%s/body.gs"; /* 0x53b */
    s = "%s%s/skeleton.g"; /* 0x548 */
    s = "%s%s/%s.tpl"; /* 0x558 */
    s = "\x91""\xd2""\x8b""@"; /* 0x564 */
    s = "\x91""\xcc""\x93""\x96""\x82""\xbd""\x82""\xe8"""; /* 0x569 */
    s = "%s%s/%s_%d.ga"; /* 0x572 */
    s = "SND_SFX_MAYA_DATA"; /* 0x580 */
    s = "se"; /* 0x592 */
    s = "EIDTable"; /* 0x595 */
    s = "pl"; /* 0x59e */
}

#define NN "OFF"
static inline int Spec(const char* s) {
    if (fn_80291188("\x82""\xc8""\x82""\xb5""", s) == 0) return -1;
    return -(BOOL)!fn_80291188(NN, s);
}
static inline int Lookup(const char* s) {
    void* b = lbl_804CB7C4;
    int n = (u16)fn_80109A2C(&b);
    Pair* t;
    int i;
    fn_80109A2C(&b);
    t = (Pair*)b;
    for (i = 0; i < n; i++, t++) {
        if (fn_80291188(t->name, s) == 0) return i;
    }
    return Spec(s);
}
static inline int Lookup2(const char* s) {
    int i;
    void* b = lbl_804CB7C4;
    int n = (u16)fn_80109A2C(&b);
    Pair* t;
    fn_80109A2C(&b);
    t = (Pair*)b;
    for (i = 0; i < n; i++, t++) {
        if (fn_80291188(t->name, s) == 0) return i;
    }
    return Spec(s);
}
static inline int Kind(Unit* u) {
    return u->d ? u->d->kind : 0x13;
}
int fn_800F002C(Unit* u, int a) {
    if (u == 0) goto def;
    if (u->d == 0) goto def;
    if (a == 0 && fn_801108D8(u->d) > 1 && !(fn_801116B8(u)->f4 & 0x200)) {
        switch (Kind(u)) {
        case 1:
            return Lookup2("\x8e""\xe8""\x91""\x84""");
        case 2:
            return Lookup("\x8e""\xe8""\x95""\x80""");
        }
    }
    if (fn_801116B8(u)->f0 & 0x4000000) {
        return Lookup("\x8f""\xf1""");
    }
    switch (Kind(u)) {
    case 0:
        return Lookup("\x8c""\x95""");
    case 1:
        return Lookup("\x91""\x84""");
    case 2:
        return Lookup("\x95""\x80""");
    case 3:
        return Lookup("\x8b""|");
    case 0xB:
        return Lookup("\x8f""\xf1""");
    case 4:
        return Lookup("\x8c""\x95""");
    case 0xD:
        return Lookup("\x83""{\x83""E\x83""K\x83""\x93""");
    case 0x10:
        return -1;
    default:
    def:
        return Lookup("\x91""f\x8e""\xe8""");
    }
}
}
