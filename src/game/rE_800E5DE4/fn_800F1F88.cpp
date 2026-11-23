/* C++ TU: the virtual calls only schedule like the original (vtable slot
 * loaded straight into r12) when compiled as real C++ virtual calls. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;

class SndMgr {
public:
    /* 40 placeholder slots so play/stop land at vtable offsets 0xA8/0xAC */
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void play(u16 id);
    virtual void stop();
};

extern "C" {
extern SndMgr* lbl_804CB5B8;
int fn_80008C98(u32*, int);
u16 fn_80008CF0(u32*, int);

BOOL fn_800F1F88(u32* f) {
    u16 v;
    if (!f) {
        return 0;
    }
    if (fn_80008C98(f, 0x2F)) {
        v = fn_80008CF0(f, 0x2F);
        if (v == 0) {
            lbl_804CB5B8->stop();
        } else {
            lbl_804CB5B8->play(v);
        }
        return 1;
    }
    return 0;
}
}
