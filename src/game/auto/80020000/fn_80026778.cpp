/* Startup initialization of the 32-entry state arrays. */
extern "C" {
struct State { unsigned char a[32]; short b[32]; short c[32]; unsigned char flags[5]; signed char selected; char name[0x22]; int xC8,xCC; };
extern State lbl_803C8DA0;
static inline void init(State* s) {
 s->flags[1]=0;s->flags[2]=0;s->flags[3]=0;s->flags[4]=0;s->flags[0]=0;
 for(int i=0;i<32;i++) { s->a[i]=0;s->b[i]=0;s->c[i]=12345; }
}
void fn_80026778() {
 init(&lbl_803C8DA0);
 lbl_803C8DA0.selected=-1;
 lbl_803C8DA0.name[0]=0;
 lbl_803C8DA0.xC8=0;lbl_803C8DA0.xCC=0;
}
}
