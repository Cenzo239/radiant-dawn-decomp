/* WIP: 6 of 189 words differ; size and references match.
 * Availability outer counter wants r29 (currently r28); Boolean wants r28
 * (currently r29). Offsets: 0x10C, 0x12C, 0x14C, 0x150, 0x17C, 0x184.
 */
extern "C" {
typedef unsigned char u8;
struct F { int pad; unsigned int flags; };
struct Slot {short x,y;u8 item[0x28];u8 enabled,pad[3];};
struct O {u8 pad[0x28];short state;u8 p2a[6];u8* a;u8* b;short x38,x3a;u8 side,index,oldSide,oldIndex,flag,phase,x42,mode,filter,x45,p46[2];void* child;};
extern Slot lbl_803CB4D0[2][7];
struct Context {u8* a;u8* b;u8 pad8[4];u8 mode,padD,index;};
extern Context lbl_803CA870;
extern u8 lbl_803CAB38[],lbl_8037F800[],lbl_8037F8E4[];
extern char lbl_804CA380[8];
extern float lbl_804CCF54,lbl_804CCF88,lbl_804CCF8C;
struct Pad { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(int); };
extern Pad* lbl_804CB5B8;
O* fn_80081194(void*,void*);
void fn_80111C78(void*,void*);
void fn_8012CAD8(void*);
F* fn_801116B8(void*);
void fn_80193054();
void* fn_80078CCC(int,const char*,int);
void* fn_8017AA08(void*);
void fn_8017A9F8(void*,float,float,float);
void fn_8017A968(void*,const void*);
void fn_80083DC4(void*,int);
static inline int find(int row) {
 Slot* p=lbl_803CB4D0[0];int i=0;
 for(;;p++,i++) {if(i>=7){i=-1;break;}if(p[row*7].enabled)break;} return i;
}
void fn_800656BC(void* parent) {
/*P*/
 O* o;
 int j;
 int x;
 int i;
 Slot* p;
 Slot* row2;
 Slot* p2;
 Slot* row;
 int y;
 int off;
/*E*/
 o=fn_80081194(lbl_8037F800,parent);
 u8* a=lbl_803CA870.a;u8* b=lbl_803CA870.b;o->a=a;o->b=b;
 o->x3a=-1;o->x38=-1;o->mode=0;o->flag=0;
 row=lbl_803CB4D0[0];x=0x26;
 for(i=0;i<2;i++,row+=7){
 p=row;j=0;y=0x77;off=0;
 for(;j<7;j++,p++,y+=0x1c,off+=0x28) {
 p->x=x;p->y=y;if(i)p->x+=0x12a;
 if(i)fn_80111C78(p->item,o->b+off+0x1bc);else fn_80111C78(p->item,o->a+off+0x1bc);
 }}
 o->filter=0;fn_8012CAD8(o->a);fn_8012CAD8(o->b);
 row2=lbl_803CB4D0[0];
 for(x=0;x<2;x++,row2+=7){p2=row2;for(j=0;j<7;j++,p2++){
 if(o->filter){i=0;if(*(void**)p2->item){if(fn_801116B8(p2->item)->flags&0x60)i=1;}p2->enabled=i;}
 else p2->enabled=*(void**)p2->item!=0;
 }}
 o->side=0;o->index=find(0);if((signed char)o->index<0){o->side=1;o->index=find(1);}
 o->oldSide=0;o->oldIndex=0;fn_80193054();lbl_803CAB38[0x92c]=15;
 void* m=fn_80078CCC(0x30,lbl_804CA380,0);if(m)m=fn_8017AA08(m);o->child=m;
 fn_8017A9F8(m,lbl_804CCF54,lbl_804CCF88,lbl_804CCF8C);fn_8017A968(o->child,lbl_8037F8E4);
 o->phase=1;o->state=4;o->x45=0x9a;o->x42=0;
 if(lbl_803CA870.mode==0x29){lbl_804CB5B8->v88(0x400);o->side=0;o->index=lbl_803CA870.index;fn_80083DC4(o,3);}
}
}
