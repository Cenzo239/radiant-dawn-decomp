/* Inventory index of an item, 8012C9BC. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
int fn_8012C9BC(Unit* u, void* it) {
    if (u->inv[0].item) {
        if (u->inv[0].item == it) return 0;
        if (u->inv[1].item) {
        if (u->inv[1].item == it) return 1;
        if (u->inv[2].item) {
        if (u->inv[2].item == it) return 2;
        if (u->inv[3].item) {
        if (u->inv[3].item == it) return 3;
        if (u->inv[4].item) {
        if (u->inv[4].item == it) return 4;
        if (u->inv[5].item) {
        if (u->inv[5].item == it) return 5;
        if (u->inv[6].item) {
        if (u->inv[6].item == it) return 6;
        }}}}}}
    }
    return -1;
}
}
