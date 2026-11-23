/* fn_8009167C: near miss. Control flow and instruction selection match;
 * ~28-30 of 118 words differ only in volatile register allocation inside the
 * unrolled (x2) inner loop (want e=r4, bestCost=r6, best=r7, i=r8).
 * Tried all declaration orders and an inline helper. Needs the GetUnit
 * helper and prototypes from ../fn_8008E3B4.c. */
typedef struct SkillEntry {
    u8* skill;      /* 0x00: skill data (0x1e: cost, 0x1f: removable?) */
    u8 unk4;
    u8 f80 : 1;     /* 0x05 */
    u8 f40 : 1;
    u8 f20 : 1;
    u8 f10 : 1;
    u8 f08 : 1;
    u8 f04 : 1;
    u8 free : 1;    /* 0x02: skill costs nothing */
    u8 f01 : 1;
    u8 pad6[2];
} SkillEntry;

static inline u8 SkillEntryCost(SkillEntry* e)
{
    return e->free ? 0 : e->skill[0x1e];
}

static inline SkillEntry* FindCheapestSkill(SkillEntry* e)
{
    u8 bestCost = 0xff;
    SkillEntry* best = NULL;
    int i;
    for (i = 0; i < 18; e++, i++) {
        if (e != NULL && e->skill != NULL && e->skill[0x1f] != 0 && SkillEntryCost(e) != 0 &&
            SkillEntryCost(e) < bestCost) {
            bestCost = SkillEntryCost(e);
            best = e;
        }
    }
    return best;
}

int fn_8009167C(int id, int v)
{
    u8* unit = GetUnit(id);
    if (unit == NULL || *(int*)(unit + 0xec) == 0) {
        return 0;
    }
    fn_8011AEA0(unit + 0x12c, v, 2, 0);
    while ((u8)fn_8011AB30(unit + 0x12c) > 6 || fn_80127A90(unit) - fn_8011B8A4(unit + 0x12c) < 0) {
        fn_8011B32C(unit + 0x12c, FindCheapestSkill((SkillEntry*)(unit + 0x12c))->skill);
        fn_8011A36C(unit + 0x12c);
    }
    return 1;
}
