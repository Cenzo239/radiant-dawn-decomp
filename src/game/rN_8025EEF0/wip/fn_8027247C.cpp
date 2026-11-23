/* fn_8027247C: 12 words, float registers only (want f2 const f3 v.x; x f4 y f3 z f0). */
u8 fn_80253DAC(int id, Vec3i* pos, f32 v, f32 ms);
u8 fn_80253718(int id, f32 v, f32 ms);

#pragma push
#pragma use_lmw_stmw off
void fn_8027247C(SndHandle* h, int mode, int id, int b, Vec3i* pos, f32 vol) {
    SndObj* o = handleObj(h);
    if (o != 0 && o->isPlaying() != 0) {
        o->stop(0);
    }
    handleInit(h);
    switch (mode) {
    case 1: {
        Vec3i t;
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        t.x = x;
        t.y = y;
        t.z = z;
        h->id = fn_80253DAC(id, &t, vol, 0.0f);
        break;
    }
    case 4: {
        Vec3i t;
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        t.x = x;
        t.y = y;
        t.z = z;
        h->id = fn_80253DAC(id, &t, vol, 0.0f);
        break;
    }
    case 3:
        h->id = fn_80253718(id, vol, 0.0f);
        break;
    }
    {
        f32 z, y, x;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        h->m0 = mode;
        h->pos.x = x;
        h->pos.y = y;
        h->pos.z = z;
    }
    h->m2 = b;
    h->vol = vol;
}
#pragma pop


