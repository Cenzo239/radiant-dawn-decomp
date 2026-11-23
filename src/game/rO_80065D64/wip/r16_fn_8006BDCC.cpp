/* Round 16: fn_8006BDCC 7 of 25 words. Walking e pointer (*t++ = e++) keeps the e base register; the t base (addi r6,r31,0x70) still folds into r31 offsets. The other three of the family follow the same pattern. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct MsgEnt { u32 f0; const char* s; };
struct MsgTab {
    u8 pad0[0x50];
    MsgEnt e[4];   /* 50 */
    MsgEnt* t[6];  /* 70 */
    u8 o88[0x10];  /* 88 */
    u8 o98[0x10];  /* 98 */
};
extern "C" {
extern MsgTab lbl_803CB7B8;
void* fn_8009E898(void);
void* fn_800D5448(void*, void*, int);
}
extern "C" void fn_8006BDCC(const char* a, const char* b) {
    MsgTab* g = &lbl_803CB7B8;
    MsgEnt* e = g->e;
    MsgEnt** t = g->t;
    e->s = a; *t++ = e++; *t++ = e; e->s = b; *t = 0;
    fn_800D5448(g->o88, fn_8009E898(), 0);
}
