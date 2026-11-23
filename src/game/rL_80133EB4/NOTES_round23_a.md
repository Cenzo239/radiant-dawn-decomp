# Round 23 (agent r23a): equivalent to exact

Tried, still not exact:
- fn_80137BC8 (sched): using lbl_803EC898 directly instead of the `g` local gives the original's `lis r4; addi r30,r4` hoist (25 -> 22 words); the rest is the interleaved height stores already described in the file header.
- fn_80141334 (4 words, template base register): not retried, earlier notes list ~20 forms.
- fn_801386AC (float registers): read only.
- fn_8013E77C (sched, sda byte loads): Mv parameter order x local statement order (144 cells), no change from 16 lines.
