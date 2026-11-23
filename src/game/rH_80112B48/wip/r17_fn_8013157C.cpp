/* NOT CHECKABLE AS-IS. fn_8013157C (0x3C) is a compiler-generated static initialiser (__sinit) for three
   file statics at lbl_804133B8 (+0x0, +0x70) and lbl_8041349C (+0xE4). Compiling this file gives an
   "__sinit_\t_cpp" whose code is byte-identical to fn_8013157C (registers r4/r7/r8/r6/r5/r3 included),
   but check_func.py matches by name, so it reports SKIP. Writing the stores in a named function instead
   gives the reversed register order (14 words), and placement new adds null checks.
   Key: the vptr (+0x6C) belongs to a base class with its own virtual; without that the registers reverse.
   (In the test a function took the statics' addresses so they were kept.) The __vt__ names would need a symbol map to lbl_80385ED8 / lbl_80385EB8 / lbl_80385E98. */
#include "game/rH_80112B48/types.h"
struct CamBase { u8 pad[0x6c]; virtual void f(); };
struct CamA : CamBase { virtual void f(); };
struct CamB : CamBase { u8 pad70[4]; virtual void f(); };
struct CamC : CamBase { u8 pad70[4]; virtual void f(); };
static CamA s0;
static CamB s1;
static CamC s2;
