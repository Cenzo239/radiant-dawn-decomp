/* Six words differ in the availability-loop registers; control flow matches. */
#pragma use_lmw_stmw on
extern "C" {
struct Flags { int pad; unsigned int flags; };
Flags* fn_801116B8(void*);
struct Slot { int pad; void* item; unsigned char p8[0x24]; unsigned char enabled; unsigned char p2d[3]; };
extern Slot lbl_803CB4D0[2][7];
struct O { unsigned char pad[0x3c]; signed char side,index,oldSide,oldIndex;unsigned char a,b,pad42[2],mode; };
static inline int enabled(Slot* p, int yes) {if(p->item) {if(fn_801116B8(&p->item)->flags&0x60)yes=1;}return yes;}
void fn_800649AC(O* o) {
/*P*/
 int j;
 int i;
 int yes;
 Slot* row;
 Slot* p;
/*E*/
 o->b=0;o->a=1;
 row=lbl_803CB4D0[0];
 for(i=0;i<2;i++,row+=7) {
  p=row;
  for(j=0;j<7;j++,p++) {
   if(o->mode) {p->enabled=enabled(p, 0);}
   else p->enabled=p->item!=0;
  }
 }
 o->oldSide=o->side;o->oldIndex=o->index;o->side^=1;
 if(!lbl_803CB4D0[o->side][6].enabled) {
  int n=6;Slot* q=&lbl_803CB4D0[o->side][6];
  for(;;q--,n--) {if(n<0)break;if(q->enabled)break;}
  int k=n+1;if(k<0)k=0;
  lbl_803CB4D0[o->side][k].enabled=1;
  o->index=k;
 }
}
}
