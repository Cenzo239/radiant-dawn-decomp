# Region 0x801DD7D4..0x8023FC24 notes

546 of 1204 functions match (0xC5EC of 0x62450 bytes, about 12.6%). 131 of them are 0x80 bytes or larger; the rest are small accessors, destructors and draw helpers. `python3 -I tools/check_func.py <file> -v` prints MATCH for every `fn_*.cpp` below. The non-matching attempts are in `wip/`.

## Resume point

Work went in address order with a falling size cutoff, so coverage is not contiguous.

- Up to 0x801E8E88: functions up to about 120 words were tried.
- 0x801E8E88..0x801F4000: up to about 85 words.
- 0x801F4000..0x801F9000: up to about 60 words.
- 0x801F9000..0x80210B00: up to 22 words, plus the family at 0x802102C8..0x80210780.
- 0x80210B00..0x802135E0: up to 34 words.
- 0x802135E0..0x80222000: up to about 70 words, plus some larger ones (for example fn_8021491C, fn_80215148, fn_80215D04, fn_80216DA0, fn_80213E24).
- 0x80222000..0x8022E000: up to about 70 to 90 words.
- 0x8022E000..0x802373BC: up to about 40 words. **Nothing after fn_802373BC has been tried.** Continue there.
- Larger functions still open after 0x802135E0: the widget constructor functions (fn_80213F8C, fn_80214C00, fn_80215490, fn_8021773C, fn_8021876C), fn_802173C0 (`for_each` with a pointer-to-member), fn_80218C8C, fn_8021991C, fn_8021A47C, fn_8021B14C, fn_8021BFC0, fn_8021CF08, fn_8021D42C, fn_8021E734, fn_8021F0E0, fn_80220F28, fn_8022291C, fn_80222AD0, fn_80223580, fn_80223708, fn_80223900, fn_80224AAC, fn_80224BCC, fn_80225C70, fn_80228900, fn_80228DC4, fn_80228E5C, fn_80228F8C, fn_8022A5F8, fn_8022A6E4, fn_8022A7CC, fn_8022B9B8, fn_8022BA6C, fn_8022BB24, fn_8022BC00, fn_8022C9DC, fn_8022D404, fn_80231090, fn_80231130, fn_802311CC, fn_80231968, fn_80232864, fn_80234884 and everything above 40 words after 0x8022E000.
- The three wip families (list inserts around fn_801E5448, lazy statics around fn_801DFF2C, slide tweens around fn_801EFF40) are still open. Declaration changes alone did not fix fn_801E5448.
- The larger functions skipped in the earlier ranges are all still open.

A scan of the asm finds only two functions with real paired-single use (fn_801E0B68, fn_801E1894), so almost nothing here has to be skipped for that reason. `psq_st`/`psq_l` on r1 only saves an FP register. fn_801E2F40 and the other push_back users, and fn_801E31D4/fn_801E5640 (find child, with iterator copies on the stack), were not finished.

## Files and matched functions

| file | matched |
|---|---|
| fn_801DD7D4.cpp | 801DD7D4 801DD830 801DDA8C 801DDBAC 801DDC0C 801DDC14 801DDC1C 801DDCBC 801DDCC4 801DDCCC 801DDD6C 801DDD74 801DDD7C 801DDDE8 801DDDF8 801DDE18 801DE060 801DE348 801DEDCC 801DEE18 801DEE1C 801DF0D8 801DF160 801DF1E8 801DDEC8 801DE3B8 801DEC74 801DF2D4 801DF4F4 801DF1F8 |
| fn_801DF814.cpp | 801DF814 801DFCAC 801DFCB4 801DFCBC 801E06A8 801E06EC 801E06F4 801E06FC 801E0704 801E070C 801E0714 801E0754 801E09C4 801E0A4C 801E0AD4 801E0B10 801E0B18 801E0B20 |
| fn_801E0B28.cpp | 801E0B28 801E0EC0 801E0EC8 801E0ED0 801E0ED8 801E0F18 801E0FA0 801E0FA8 801E0FFC 801E1008 801E1014 801E101C 801E1024 801E1030 801E1038 801E1044 801E104C 801E1054 801E105C 801E1064 801E1070 801E107C 801E13BC 801E1418 801E159C 801E1600 801E17FC 801E1858 801E1AD8 801E1B18 801E1B58 801E1B60 801E1B68 801E1B70 801E1B78 801E1B80 801E1C2C 801E1C80 801E1CC0 801E1F10 801E1F24 801E1F38 801E1FE0 801E20C4 801E2DF0 801E2DF4 801E2DF8 801E2DFC |
| fn_801E2E00.cpp | 801E2E00 801E30C8 801E3300 801E33B4 801E3468 801E3B58 801E4094 801E40B0 |
| fn_801E5448.cpp | 801E5558 801E5860 801E5870 801E5880 801E5890 801E58A0 801E5954 801E6AE0 801E6B64 801E6BBC 801E6BD8 801E6C0C 801E6C10 801E6C44 801E6C8C 801E6CC0 801E6D0C 801E6D40 801E6D50 801E6D88 801E6DA0 801E6EE8 |
| fn_801E7024.cpp | 801E7024 801E70C4 801E7114 801E7164 801E71B4 801E7204 801E7490 801E7730 801E7938 801E7BC0 801E7DA4 801E7DD0 801E89D4 801E89E4 801E8CF8 801E8E50 801E8E58 801E8E78 801E8E7C 801E8E80 |
| fn_801E9270.cpp | 801E9270 801E9348 801E97E4 801E9850 801E9858 801E9860 801E9868 801E98C0 801E9AC4 801E9B28 801E9BE0 801E9BF4 801E9C08 801E9C64 801E9C7C 801EA48C 801EA49C 801EA518 801EA538 801EAC6C 801EB3DC 801EB904 801EB90C 801EB914 801EB968 801EB9A8 801EB9FC 801EBA3C 801EBA94 801EBB6C 801EBBC4 801EBC9C 801EBCF4 801EBDC4 801EBDCC 801EBDD4 801EBDE8 801EBDF0 801EBDF8 801EBE0C 801EBE14 801EBE28 801EBED0 801EBEDC 801EBEF0 |
| fn_801EC2BC.cpp | 801EC2BC 801ECD88 801EC334 801EC3DC 801EC3E8 801EC3FC 801EC40C 801EC7D0 801EDEE4 801EC848 801EC8F0 801EC8FC 801EC910 801EC920 801ECD10 801EEEEC 801ECE40 801ECEC0 801ECF24 801ED0E8 801ED13C 801ED20C 801ED238 801EE0F0 801EE144 801EE214 801EE240 801EF0F8 801EF14C 801EF21C 801EF248 801EFEF4 801EFF34 |
| fn_801EFF40.cpp | 801F0684 801F06C4 801F0E14 801F0E54 |
| fn_801F4148.cpp | 801F4148 801F5A40 801F7074 801F72A0 801F72E8 801F72F0 801F77BC 801F77F0 801F77F8 801F7F28 |
| fn_801F9938.cpp | 801F9938 801F9948 801FA5D8 801FA618 801FAE6C 801FB048 801FB7E8 801FBA18 801FBC30 801FBEB0 801FC114 801FC120 801FC260 801FC268 801FC3D0 801FC3D8 801FC55C 801FC564 801FC724 801FC730 801FC7D4 801FC810 801FC818 801FC934 801FC940 801FC9E4 801FC9EC 801FC9F8 801FCA04 801FCA58 801FCF7C 801FD234 801FD23C 801FD244 801FD24C 801FD3FC 801FD594 801FD5A0 801FD700 801FD70C 801FD858 801FDAA4 801FDAE0 801FE048 801FE088 801FE0C8 801FE4C4 801FE5C8 801FE5D4 801FE5E8 801FE710 801FE724 801FE72C 801FEEBC 801FEFE0 801FF00C 801FFE80 80200008 80200018 80200058 802007A8 80200ADC 80200E08 80200E40 8020109C 802010D4 80201100 80201650 80201670 80201B28 80201D18 80201D90 80201F7C |
| fn_802102C8.cpp | 802102C8 80210390 8021044C 80210514 802105EC 802105F4 80210684 80210728 80210780 802109BC 802109C0 802109D8 802109F0 80210A78 |
| fn_80211320.cpp | 80211320 802113A0 802113FC 8021143C 8021147C 80211D1C 80211EA4 80212060 802121E8 80212498 80212558 802132B4 80213390 |
| fn_802135E0.cpp | 802135E0 8021363C 8021376C 8021395C 802139D8 80213A58 80213A98 80213AE0 80213B10 80213E24 80214704 80214618 80215024 8021491C 80215B44 80215148 80215828 80215984 80215D04 802160C0 802161FC 80216478 802165B4 8021667C 80216744 80216D74 8021696C 80216A1C 80217BC4 80216F84 802170D8 80217368 802172F8 80217328 80217638 80217658 80217220 802179DC 80217ABC 80217C34 802176A0 80216DA0 80218448 80217CD4 802185D4 80218B38 80218C34 8021A89C 8021A27C 8021A434 80218B78 80218A48 8021B408 8021CCE0 8021CD64 8021CD4C 8021CD58 8021CCF0 8021C6DC 8021C638 8021C68C 8021CBC8 8021BA84 8021BA28 8021C1B0 8021CDCC |
| fn_8021D0BC.cpp | 8021D0BC 8021D108 8021D110 8021D118 8021D120 8021D174 8021D1CC 8021D21C 8021D25C 8021D268 8021D2C0 8021D2FC 8021D33C 8021D344 8021D34C 8021D360 8021D368 8021D41C 8021D424 8021D628 8021D6EC 8021D72C 8021D8A0 8021DA50 8021DA8C 8021E6CC 8021EA18 8021ECC8 8021F084 8021F2CC 8021F30C 8021F348 8021F388 8021F3D8 8021DA10 8021F418 8021F468 80220DA0 80220DA4 80220E5C 80221DBC 80221E3C 80221EBC 80221F44 80221FD8 8021FEC8 80220FD4 8021E8CC 8021EBF0 8021E9A4 80222064 802220C4 80222114 802221EC 80222210 8022227C 80222308 80222368 80222440 802224D0 8022253C 80222594 80222A10 80222A58 80222C18 80223B30 80222E08 80223C60 802236C8 802248A4 80223C8C 80224C9C 80224CA4 80224CC4 80224CC8 80223870 802250A0 |
| fn_80226BF0.cpp | 80226BF0 8022860C 80228BB8 80228C78 80228D38 80228F74 80228F80 80229190 8022919C 8022A7C0 8022B5A0 8022B5B0 8022B5B8 8022B5C0 8022B5C8 8022B5D0 8022B5D8 8022B5E0 8022C244 8022C298 8022C99C 8022CAA4 8022D364 8022D998 8022DD70 8022DDB4 8022DFD8 8022B6A0 8022A87C 8022A890 8022E514 8022F57C 80230394 80230E60 802318EC 80233824 80233A78 8022E590 8022F570 802318E0 80234590 802345E8 8022EF08 8022F624 8022F5F8 80230524 80232508 80234640 80232274 8023229C 8023269C 80232858 8023285C 80234454 802356AC 802356B4 802359A8 80236A48 8023578C 802357A8 802359BC 802373AC 8023731C 80237364 8023445C |

## Shared headers

- `types.h`: base types and `inputBlocked()`.
- `vobj.h`: generic classes for virtual calls by slot. `VO4` has its vptr at +4, `VO0` at +0, and `VO0N` is `VO0` with no parameters. `vXX` is vtable byte offset 0xXX. Return types and parameters are only what matched callers need.
- `rlist.h`: the reference counted node and list below, including `listClear` and `listFreeAll`. `NodeGuard`, `listFind` and `listInsertN` are used only by near misses.

## Subsystems (guessed names)

- **0x801DD7D4..0x801DDD7C menu arrows:** "EID_ARROW1" effect objects with vptr at +0, an effect handle at +4 (from fn_800E4060, model at +0x30), a direction at +8 (0/1/2 = 90/270/180 degrees), scale at +0x18, colour at +0x20 and z offset at +0x24.
- **0x801DDDE8..0x801E1014 list layouts and menu items:** vptr at +4. `LL` holds a `VO4*` at +0x3C, entity ids at +0x40 and a count at +0xA4. Slots 0x48/0x4C look like origin, 0x50/0x54 size, 0x58/0x5C cell size, 0x98/0x9C offset, 0xA0/0xA4 rows and columns, 0xA8/0xAC sound ids. fn_80085EF8 returns a positioned entity by id, with x/y at +0x30/+0x32. fn_801DFF2C and its siblings build "M_ASK_Y" yes/no prompts.
- **0x801E107C..0x801E2204 widget base:** rect at +0xA..+0x10, inner rect at +0x12..+0x18, text origin at +0x1E/+0x20, colour at +0x22, flags at +0x38. fn_801E2204 maps a point and returns a pointer to the result. fn_801E2104 is a scissor callback that clamps to 0..0x7FF.
- **0x801E2E00..0x801E31D4 widget group:** vtable lbl_8038CAF0, parent at +0x3C, child list at +0x40. fn_801E30C8 removes a child. fn_801E3300/33B4/3468 multiply x2C/x30/x34 up the parent chain.
- **0x801E3B58..0x801E5954 scene process:** process class lbl_8038CB48, block count at +0x30, list at +0x34. The list back is the focused widget. lbl_804CBE30 is a global block counter (fn_801E5860/5870).
- **0x801E6A88..0x801E7020 helpers:** help window open and close, small processes, and printf-style text draw (`fn_801E6DA0`, `fn_801E6EE8`).
- **0x801E7024..0x801E7204:** "SHOP_PERSON_%s" lookups through fn_80290D04 (snprintf) and fn_80077064.
- **0x801E7218..0x801E74CC:** item counts across units and the convoy, and message preloads from "CONV_INFO_DATA" and "CONVERSATION_FE8_YELL_DATA". Units use the 0x3F0-byte table at lbl_804CB810, with 7 items of 0x28 bytes at +0x1BC.
- **0x801E75B0..0x801E8E80 list menu:** list at +0x70, cursor +0x52, scroll +0x5A, columns +0x5C, row height +0x5E, filter callback +0x7C/+0x80.
- **0x801E9270..0x801EBED0 unit item menu:** unit at +0x5C, 7 slots, selection at +0x50.
- **0x801EC2BC..0x80200058 prep menus:** arrays of lists destroyed with fn_8028C0D0, `lbl_803CA870` (0x130 bytes, shared menu state), slide tweens using fn_8017F68C, and outfit help ids ("MESS_OUTFIT_IEQUIP_HELP00" and others at lbl_8036F03C) set on a help object at +0x64.
- **0x802102C8..0x80210780:** dialogs that close on buttons 0xC00 and play "SFX_SYS_MSG_OK1" through fn_80253EE4.
- **0x802135E0..0x80216744 support menu:** "MESS_SUPPORT_*" strings at lbl_803712F8. fn_80213B4C and fn_80213F8C build the screen, the 0x8021xxxx process steps move widgets (fn_801E459C/fn_801E495C), fade them (fn_801E518C with a hidden `f32` target) and set support levels through the fn_8012E* unit calls.
- **0x802167C8..0x8021D7E0 forge and shop panels:** list widgets with cursor +0x4E, smoothed position +0x50/+0x52, row height +0x54 and a 10-slot table of 12-byte entries at +0x6C. "FSHOP_CARD_DATA" at fn_8021CCF0. The cursor list follows `Ctx::a38` at fn_80216DA0.
- **0x80220DA0..0x80223C8C skill and education menus:** "MESS_EDU_*" strings, and show or hide tweens for skills (`Tw`, fn_80222064..fn_802224D0).
- **0x8022E514..0x80234640 yes/no steps:** one dialog body repeated (fn_8022E514 and six others) with help text from a table at +0x88.
- **0x802356AC..0x80237364:** thin wrappers around a message queue and device state at lbl_80420420. These look like a different subsystem from the menus (fn_8031D284 and fn_8031D34C resemble OSSendMessage and OSReceiveMessage).

## Struct layouts

```c
class RObj { virtual void destroy(int); /* slot +8 */ virtual int contains(RObj*, int); /* +C */
             virtual RObj* find(int, int); /* +10 */ int rc; /* +4 */ };
struct LNode { LNode* prev; LNode* next; RObj* val; };
struct RList { int size; LNode* prev; LNode* next; }; /* prev/next double as the sentinel */
```

## Caveats on matches

- `VO4`, `VO0` and the local `Win`, `MenuV`, `MBase` and `GridV` classes are stand-ins. Their slot positions are real, but their names and signatures are not.
- `lbl_804CB700` is declared `volatile` in `types.h` only to reproduce the double read in `inputBlocked()`. Other regions read it as a plain `u32`, so it is probably not volatile in the original.
- `fn_801E6DA0` and `fn_801E6EE8` use a hand-declared `va_list_` with `__builtin_va_info`, not the MSL header.
- Files are grouped by batch, not by original translation unit. Macros (`LIST_DTOR`, `MENU_CB`, `MENU_DRAW`, `FREE_FN`) generate several matched functions, which suggests templates or shared bases in the original.
- Parameter types, inline helpers and temporaries were chosen to produce the right code. Examples are the `const` parameters on fn_801DDC1C, the `lblSet`-style inlines and fn_801E6AE0's call shape.
- A `const` parameter or a function with no return on some path (the `effDim` inlines) can be accepted by the compiler here without being what the original source said.
- Parts of fn_802135E0.cpp, fn_8021D0BC.cpp and fn_80226BF0.cpp are shaped to get the right registers and are unlikely to be the original source: `animA`/`animB` (hand-unfolded recursive scale chains with flat float declarations whose order sets f28..f31, likely the inlined recursive fn_801E3468), `(int)y + (int)t` in fn_80217CD4, `(u32)p + 0x44` and repeated null checks in the member destructors, int locals around constants, and `setHelp(const char* const&)`.
- Hidden parameters were added from register evidence only: fn_801E518C's `f32`, fn_80216F84's second argument, and the second parameter of fn_8021DA10, which is really a flag, not a pointer.
- `fn_8031D284`/`fn_8031D34C` wrappers have only guessed names. Their globals are declared as plain `char` arrays.

## Near misses in wip/

Each `wip/` file is a full snapshot of its batch at the time it was pruned, with the misses listed at the top. Some predate `inputBlocked()` moving to `types.h`, so they may need the local copy removed to compile.

- **fn_801E5448:** all logic matches, with only the sentinel and new node registers swapped (11 of 68 words). `NodeGuard` in `rlist.h` reproduces the dead `b; bl free` block and the stack stores, which should help the whole push_back family.
- **fn_801DFF2C:** only the register numbers in the two lazy static constructors are wrong (25 of 105 words). fn_801E00D0, fn_801E0274 and fn_801E041C share this shape and were not attempted.
- **fn_801EFF40:** 32 of 142 words. The structure is right, but `o` should stay in r3 after the switch. fn_801F044C and the 801F06D0, 801F0BDC, 801F0E60 and 801F136C functions look like siblings.
- **fn_801E9914, fn_801E999C, fn_801E9B58:** the registers of the inline slot test rotate (10 to 11 words).
- **fn_801E74CC:** 4 words. The counter and limit of the second loop are swapped.
- **fn_801EDE3C, fn_801EEE44, fn_801EFE4C:** `std::for_each` with a pointer-to-member functor (7 words). The structure matches through `(n->val->*f.f)(f.arg)`.
- **fn_801E1BB0, fn_801E1BEC, fn_80201CE0, fn_80201D58:** 3 to 6 words of register choice in the rectangle setter.
- **fn_80211384, fn_802113E0, fn_801FE504:** a 12-byte struct copy that loads all words first (4 to 5 words).
- **wip/fn_802135E0.cpp, wip/fn_8021D0BC.cpp, wip/fn_80226BF0.cpp** are full snapshots before pruning. fn_80215688 (5 words) has base register r4 where the original has r3. fn_8021C278 (5) has the float registers swapped. fn_802228B8 (3) has `rowH` and `ty` swapped. fn_8022B6DC (8) and fn_8022B620 (14) are order and register misses in the table scan. fn_8021D17C (12), fn_8021D964 (26, wants `mr r0; addic. r4,r0,1`), fn_8021C1EC (11), fn_8021EA80 (68, wants a reload of `a40` in each branch), fn_8022C2D8 (34, keeps the 0 in r31) and fn_80213B4C (25, register choice in the second inline constructor) are still open.

## Lessons

- **`inputBlocked()`:** the `lwz r0; lwz r4; rlwinm. 27,27; beq; rlwinm. 26,26` pattern appears 103 times in this region. It matches with a `volatile` global read into two locals, with the result flag declared after them.
- **`s16` locals keep registers.** `s16 x = p->x; x -= w / 2;` keeps one register where `int` splits the value, and it also fixed the allocation of the other locals in fn_801DF814. Permuting declarations had no effect there.
- **`const` parameters** also fix `lwz` before `stw r31` in a prologue (fn_801DDC1C, fn_801E9AC4).
- **Float result of a call:** to get `fmuls f1,f1,f31`, assign the call to a local and multiply it by a value loaded earlier.
- **Function-pointer casts don't reproduce virtual calls.** They load through another register before r12, so use a real class.
- **Dead `b; bl free` blocks** come from an inlined class destructor on a stack guard whose pointer was just set to null.
- **Switch trees:** a `case 3: break;` placed first, with labels 0, 2 and 1 after it, gives the compare tree with `cmpwi 2` on top (fn_801DDA8C).
- **Argument setters:** `set(o, a, b, W(o) - 2, H(o) - 5, c, d)` through an inline with `s16` parameters reproduces odd store and `extsh` orders in rectangle init functions, because arguments are evaluated from the right.
- **`__builtin_va_info`** with a local `va_list` struct matches printf-style functions, including the `bne cr1` FP save block.
- **Widget constructors match as a plain inline.** `wfInit` in fn_802135E0.cpp reproduces the 0x40-byte base constructor, followed by the derived vtable store. It works directly in fn_8021A27C and nearly in fn_80213B4C, so it should apply to the roughly 114 uses of lbl_8038CB1C (228 lis and addi lines). Hoist a value such as `s16 a = o->a26;` before the call.
- **A `const T&` inline parameter forces the argument into a register before the body.** `setHelp(s, base + 0x1a)` only gets `addi r30,r30,0x1a` before the call with `const char* const&`. A by-value parameter is re-derived after the call.
- **Inner rect setter with `int` parameters** (`setI2`) fixes `setI(w, 0, 0, W, H)`, where an `s16` version picks different registers.
- **Unrolled loops:** a plain `for (j = 0; j < 10; j++, s++)` over slots reproduces the 5x unrolled `bdnz` loop with its extra induction register. Write it as a `j++, s++` step, since `s++` in the body swaps the two `addi`s.
- **A local aggregate initialiser** `C4 c = {0x80, 0x80, 0x80, 0xff};` gives `lbz lbl@sda21; lbz lbl+1@sda21` with stack copies, from a compiler-made constant.
- **`bool` field:** `r.b = x == 0` gives `cntlzw; srwi 5`, while a `u8` field gives `extrwi`.
- **Stack slots of block locals sit above those of inlines.** Move a `Pt` into a small inline to get descending offsets in source order (fn_80215148).

## Round 24

Targets: the functions that keep build units from linking (docs/tu_units.tsv).

- `fn_8022C2D8.cpp` exact (0xAC). The destructor keeps the null it stores into the child slot in a saved register (`li r31,0` before the vtable store, `stw r31,0x7c` after the virtual call). That is a constant hoisted out of a loop that CW then unrolls: the release is written as a loop over a one-element child array. Explicit zero locals, inline setters with a zero parameter and the propagation pragmas did not give it.
- fn_8021E23C (6 words, top-level cost value wants f31): canUpB/C/D/E in either or both top-level tests: no gain.
- fn_8021F0E0 (17 words, size -4): the original computes the colour temporary's address (`addi r4,r1,8`) before the byte copy and passes it with `mr r3,r4`. col()/col2() inlines, a `C4(...)` temporary, a named copy, a pointer local, getters returning C4 by value, C4 with no / init-list / assignment copy constructor: 17-19 words. fn_801E163C (also unmatched) is the only other function with this shape.
- fn_801EA17C (15 words, size -4): `int cur` / `int n` / both, int-returning prv/nxt, `int res`, a second `lha` for `n`: the extsh of `cur` at the final compare comes only together with extra extsh elsewhere.
