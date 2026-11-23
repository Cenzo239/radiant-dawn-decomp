#ifndef RB_STATEFN_BSS_H
#define RB_STATEFN_BSS_H
#include "game/rB_8002E1C4/statefn.h"

/* The .bss block of the unit 0x8003CD54..0x80042AC4 starts with the lazily
 * constructed state objects of fn_8003CD54 .. fn_8003DCAC (0xA0 bytes,
 * lbl_803CA720 .. lbl_803CA7B0); the static initialiser's own objects
 * (fn_8004288C.cpp, sObjA = lbl_803CA7C0 ..) follow. In the original they
 * are C++ function-local statics; here they are file statics in function
 * order, defined once ahead of their users, so that
 *  - every per-function file compiles the same block (its "...bss.0" is
 *    lbl_803CA720, see the .symbols.json maps), and the static initialiser
 *    addresses its objects as block + 0xA0.. like the original, and
 *  - the merged unit defines the block once, before its first user.
 * Each user file includes this header; the include guard keeps one copy. */
static BigStateObj sState_8003CD54;  /* lbl_803CA720 */
static BigStateObj sState_8003CE54;  /* lbl_803CA730 */
static MidStateObj sState_8003CFD4;  /* lbl_803CA740 */
static MidStateObj sState_8003D09C;  /* lbl_803CA74C */
static MidStateObj sState_8003D79C;  /* lbl_803CA758 */
static MidStateObj sState_8003D854;  /* lbl_803CA764 */
static MidStateObj sState_8003D90C;  /* lbl_803CA770 */
static MidStateObj sState_8003D9C4;  /* lbl_803CA77C */
static MidStateObj sState_8003DA7C;  /* lbl_803CA788 */
static MidStateObj sState_8003DB34;  /* lbl_803CA794 */
static BigStateObj sState_8003DBEC;  /* lbl_803CA7A0 */
static BigStateObj sState_8003DCAC;  /* lbl_803CA7B0 */

#endif
