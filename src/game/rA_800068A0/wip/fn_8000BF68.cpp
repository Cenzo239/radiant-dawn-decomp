/* fn_8000BF68: first draft, 6 words short with registers off. Structure of the camera setup is right; the count loop uses bdnz with a guard, the search must keep the n == 0 test, and the key reads look like lhaux through a key-pair pointer. */
#include "game/rA_800068A0/types.h"
/* Applies a camera animation (chunk type 1) from an actor to a camera. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16 node; u16* offs; } ASet;
typedef struct ATrack { u16 n; u8 kind; u8 shift; u16 keys[1]; } ATrack;
typedef struct GCam { u8 x0[0xD4]; Vec pos; Vec at; Vec up; u8 xF8[0x104 - 0xF8]; Vec off; u8 x110[0x140 - 0x110]; f32 nearZ, farZ, aspect, fovy; } GCam;
typedef struct GAct { u8 x0[0x10]; Mtx m; u8 x40[0x58 - 0x40]; f32 frame; } GAct;
extern AList* fn_80007F10(GAct* a);
extern GCam* fn_8000F470(void);
extern Mtx* fn_800080B8(GAct* a);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_80312DB4(const void* m, const Vec* a, Vec* b);
extern void fn_8001E6D0(const void* a, void* b);
extern void fn_80313460(const Vec* a, const Vec* b, Vec* c);
extern void fn_803134C4(const Vec* a, Vec* b);
extern void fn_8000F954(GCam* c, int a, int b);
extern void fn_8000FA98(GCam* c);
int fn_8000BF68(GAct* a, GCam* cam) {
    AList* an;
    f32 frame;
    AChunk* c;
    ASet* set;
    int ofs;
    u32 left;
    f32 fNear;
    f32 fFar;
    f32 fAsp;
    f32 fFov;
    u16 node;
    ATrack* t;
    int n;
    int kind;
    u16* keys;
    int f0;
    int f1;
    int v0;
    int v1;
    int has;
    int i;
    int lo;
    int hi;
    int mid;
    int last;
    int kv;
    f32 v;
    Mtx* bones;
    Mtx m;
    if (a == 0) return 0;
    an = fn_80007F10(a);
    frame = a->frame;
    if (an == 0) return 0;
    for (c = an->head; c != 0; c = c->next) {
        if (c->type == 1) {
            set = (ASet*)c->data;
            goto found;
        }
    }
    set = 0;
found:
    if (set == 0) return 0;
    if (cam == 0) cam = fn_8000F470();
    ofs = 0;
    fFov = cam->fovy;
    fAsp = cam->aspect;
    fNear = cam->nearZ;
    fFar = cam->farZ;
    node = set->node;
    for (left = set->count; left != 0; left--) {
        if (*(u16*)((u8*)set->offs + ofs) == 0xFFFF) {
            t = 0;
        } else {
            t = (ATrack*)((u8*)set + *(u16*)((u8*)set->offs + ofs));
        }
        n = t->n;
        f0 = -1;
        kind = t->kind;
        f1 = -1;
        v1 = 0;
        keys = t->keys;
        if (n == 0) {
            kind = -1;
            v = 0.0f;
        } else {
            last = n - 1;
            hi = last;
            lo = 0;
            while (lo <= hi) {
                mid = lo + ((hi - lo) >> 1);
                kv = keys[mid * 2];
                if (kv < (s32)frame) {
                    lo = mid + 1;
                } else if (kv > (s32)frame) {
                    hi = mid - 1;
                } else {
                    i = mid;
                    goto sdone;
                }
            }
            if (hi < 0) {
                i = -1;
                goto sdone;
            }
            if (lo > last) {
                i = last;
                goto sdone;
            }
            kv = keys[lo * 2];
            i = lo - 1;
            if (kv <= (s32)frame) {
                i = lo;
            }
        sdone:
            if (i < 0) {
                v0 = (s16)keys[1];
                has = 0;
            } else if (i < n - 1) {
                f0 = (s16)keys[i * 2];
                v0 = (s16)keys[i * 2 + 1];
                f1 = (s16)keys[(i + 1) * 2];
                v1 = (s16)keys[(i + 1) * 2 + 1];
                has = 1;
            } else {
                has = 0;
                v0 = (s16)keys[i * 2 + 1];
            }
            if (has) {
                v = (f32)v0 + (f32)(v1 - v0) * (frame - (f32)f0) / (f32)(f1 - f0);
            } else {
                v = v0;
            }
            v /= (f32)(1 << t->shift);
        }
        switch (kind) {
        case 8:
            fNear = v;
            break;
        case 6:
            fFov = v;
            break;
        case 7:
            fAsp = v;
            break;
        case 9:
            fFar = v;
            break;
        }
        ofs += 2;
    }
    if (fNear < 0.1f) {
        fNear = 0.1f;
    }
    bones = fn_800080B8(a);
    cam->off.x = 1.0f;
    cam->off.y = 0.0f;
    cam->off.z = 0.0f;
    cam->up.x = 0.0f;
    cam->up.y = 1.0f;
    cam->up.z = 0.0f;
    cam->at.x = 0.0f;
    cam->at.y = 0.0f;
    cam->at.z = -1.0f;
    cam->pos.x = 0.0f;
    cam->pos.y = 0.0f;
    cam->pos.z = 0.0f;
    cam->fovy = fFov;
    cam->aspect = fAsp;
    cam->nearZ = fNear;
    cam->farZ = fFar;
    fn_80312378(a->m, bones[node], m);
    fn_80312DB4(m, &cam->pos, &cam->pos);
    fn_8001E6D0(m, m);
    fn_80312DB4(m, &cam->at, &cam->at);
    fn_80313460(&cam->pos, &cam->at, &cam->at);
    fn_80312DB4(m, &cam->up, &cam->up);
    fn_803134C4(&cam->up, &cam->up);
    fn_8000F954(cam, 0, 1);
    fn_8000FA98(cam);
    return 1;
}
}
