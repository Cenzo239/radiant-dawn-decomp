/* Show the disabled-entry hint or create the command process. */
#pragma use_lmw_stmw on
struct Base { int value; };
struct Widget : Base { virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(); };
struct Parent { unsigned char pad[0x3c]; Widget* widget; };
struct Entry { unsigned char pad[0x30]; short x,y; unsigned char p34[5]; unsigned char disabled; };
extern "C" {
extern char lbl_80379300[];
extern char lbl_80379048[];
const char* fn_800D0864(const char*);
void fn_801A23E0(int,int,const char*,Parent*);
void* fn_80081194(void*,void*);
int fn_80025CC8(void*,Parent* parent,Entry* entry) {
 /*P*/
 int wy;
 const char* text;
 short y;
 short x;
 Widget* w;
 int wx;
/*E*/
 if(entry->disabled) {
  text=fn_800D0864(lbl_80379300);
  w=parent->widget;
  y=entry->y;
  x=entry->x;
  wy=(short)w->v64();
  wx=(short)w->v60();
  fn_801A23E0(wx+x,wy+y,text,parent);
  return 0;
 }
 fn_80081194(lbl_80379048,parent);
 return 4;
}
}
