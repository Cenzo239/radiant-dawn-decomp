/* Rebuilds the mesh quadtree: resets the root, grows it around every mesh, then splits. */
#include "game/rL_80133EB4/map3d.h"
#pragma use_lmw_stmw off

struct QTN {
    u8 split;
    u8 visible;
    u16 count;
    Vec min;
    Vec max;
    Mesh* head;
    Mesh* tail;
    QTN* kid[4];
};
struct MM2 {
    u8 pad0[0xC];
    Mesh* mesh;
    u8 pad10[0x52 - 0x10];
    s16 nMesh;
    u8 pad54[0x80 - 0x54];
    QTN* quad;
};

extern "C" {
extern Vec lbl_80369450;
extern Vec lbl_8036945C;
extern void fn_80133EB4(QTN*);
extern void fn_80134140(QTN*);
extern int fn_80134024(QTN*);

static inline void SetMin(QTN* n) { Vec a = lbl_80369450; n->min = a; }
static inline void SetMax(QTN* n) { Vec b = lbl_8036945C; n->max = b; }
static inline void SetMin2(QTN* n) { SetMin(n); }
static inline void SetMax2(QTN* n) { SetMax(n); }
static inline void SetMin3(QTN* n) { SetMin2(n); }
static inline void SetMax3(QTN* n) { SetMax2(n); }
static inline void SetMin4(QTN* n) { SetMin3(n); }
static inline void SetMax4(QTN* n) { SetMax3(n); }
static inline void SetMin5(QTN* n) { SetMin4(n); }
static inline void SetMax5(QTN* n) { SetMax4(n); }
static inline void SetMM(QTN* n) { SetMin(n); SetMax(n); }
static inline void SetMM2(QTN* n) { SetMM(n); }
static inline void SetMB(QTN* n) { { Vec a = lbl_80369450; n->min = a; } { Vec b = lbl_8036945C; n->max = b; } }
static inline void SetMB2(QTN* n) { SetMB(n); }
static inline void QTReset(QTN* n) {
    int i;
    n->head = 0;
    n->tail = 0;
    n->count = 0;
    n->visible = 0;
    { Vec a = lbl_80369450; n->min = a; } SetMax(n);
    if (n->split) {
        for (i = 0; i < 4; i++) fn_80133EB4(n->kid[i]);
    }
}
static inline void QTReset0(QTN* n, int& i, QTN*& k) {
    n->head = 0;
    n->tail = 0;
    n->count = 0;
    n->visible = 0;
    SetMin4(n); SetMax3(n);
    if (n->split) {
        for (i = 0; i < 4; i++) { k = n->kid[i]; QTReset(k); }
    }
}

void fn_8013826C(MM2* mm) {
    if (mm->quad) {
        int oi;
        QTN* k;
        QTReset0(mm->quad, oi, k);
        Mesh* m = mm->mesh;
        Mesh* prev = 0;
        for (int i = 0; i < mm->nMesh; i++, m++) {
            if (mm->quad->min.x > m->minx) mm->quad->min.x = m->minx;
            if (mm->quad->min.y > m->miny) mm->quad->min.y = m->miny;
            if (mm->quad->min.z > m->minz) mm->quad->min.z = m->minz;
            if (mm->quad->max.x < m->maxx) mm->quad->max.x = m->maxx;
            if (mm->quad->max.y < m->maxy) mm->quad->max.y = m->maxy;
            if (mm->quad->max.z < m->maxz) mm->quad->max.z = m->maxz;
            if (prev) prev->next = m;
            m->next = 0;
            prev = m;
        }
        mm->quad->count = mm->nMesh;
        mm->quad->head = mm->mesh;
        mm->quad->tail = 0;
        fn_80134140(mm->quad);
        fn_80134024(mm->quad);
    }
}
}
