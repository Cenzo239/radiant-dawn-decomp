/* fn_8002FFDC: 7 of 54 words differ - original keeps it->data in r4, we get r3.
int fn_800D7D74(BUnit* p, Item* it);
int fn_8012C260(BUnit* p);

static inline u8 item_type(Item* it)
{
    return it->data ? it->data->x12 : 0x13;
}

static inline u8 item_type2(Item* it)
{
    if (it->data == 0) return 0x13;
    return it->data->x12;
}
static inline u8 data_type(ItemData* d)
{
    return d ? d->x12 : 0x13;
}

void fn_8002FFDC(BUnit* p, Item* it)
{


}
*/
