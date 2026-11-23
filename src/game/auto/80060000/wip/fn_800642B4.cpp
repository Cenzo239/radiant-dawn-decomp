/* Six words differ: yes and inner-loop counter registers are exchanged. */
#pragma use_lmw_stmw on
extern "C" {
struct Flags { int pad; unsigned int flags; };
Flags* fn_801116B8(void*);
struct Slot { int pad; void* item; unsigned char p8[0x24]; unsigned char enabled; unsigned char p2d[3]; };
extern Slot lbl_803CB4D0[2][7];
struct O { unsigned char pad[0x40]; unsigned char a,b,pad42[2],mode; };
static inline void update(O* o) {
 /*P*/
 Slot* p;
 Slot* row;
 int j;
 int i;
 int yes;
/*E*/
 o->b=0; o->a=0;
 row=lbl_803CB4D0[0];
 for(i=0;i<2;i++,row+=7) {
  p=row;
  for(j=0;j<7;j++,p++) {
   if(o->mode) {
    yes=0;
    if(p->item) { if(fn_801116B8(&p->item)->flags&0x60) yes=1; }
    p->enabled=yes;
   } else p->enabled=p->item!=0;
  }
 }
}
void fn_800642B4(O* o) { update(o); }
}
