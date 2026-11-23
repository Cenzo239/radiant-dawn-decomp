/* Apply both rows of seven slots, update units, then clear temporary slots. */
#pragma use_lmw_stmw on
extern "C" {
struct Slot { int x; unsigned char item[0x28]; unsigned char enabled,pad[3]; };
extern Slot lbl_803CB4D0[2][7];
extern unsigned char lbl_803CA870[];
extern unsigned char lbl_804CB728;
struct O { unsigned char pad[0x28]; short state; unsigned char p2a[6]; void* a;void* b;unsigned char p38[9];unsigned char phase,p42,mode; };
void fn_800453B4(void*,int);
void fn_8012BC54(void*,unsigned char,void*);
int fn_80127520(void*);
void fn_80129CB8(void*,int);
void fn_80127640(void*);
void fn_80110D38(void*);
void fn_8006556C(O* o) {
 /*P*/
 Slot* row;
 unsigned char* q;
 Slot* p;
 Slot* first;
 int z;
 int k;
 int i;
 int j;
/*E*/
 if(!o->mode) {fn_800453B4(lbl_803CA870,0x24);lbl_804CB728=9;}
 else {
 first=lbl_803CB4D0[0];q=lbl_803CB4D0[1][0].item;
 for(k=0;k<7;first++,q+=0x30,k++) {fn_8012BC54(o->a,k,first->item);fn_8012BC54(o->b,k,q);}
 if((signed char)fn_80127520(o->a)<0)fn_80129CB8(o->a,-1);
 fn_80127640(o->a);
 if((signed char)fn_80127520(o->b)<0)fn_80129CB8(o->b,-1);
 fn_80127640(o->b);
 lbl_804CB728=5;
 }
 o->phase=2;o->state=4;
 row=lbl_803CB4D0[0];z=0;
 for(i=0;i<2;i++,row+=7){p=row;for(j=0;j<7;j++,p++){fn_80110D38(p->item);p->enabled=z;}}
}
}
