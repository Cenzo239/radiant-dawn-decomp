# Text: messages (`Mess/*.m`) and fonts (`Fonts/*.cms`)

Readers: `tools/formats/mess.py`, `tools/formats/font.py`.

## Message files

`Mess/*.m` are uncompressed [IS binary containers](containers.md#is-binary-container)
with **no pointer table**. Each label is a message ID and points at a
NUL-terminated string in the data region.

* Language by prefix: none = Japanese, `e_` = English (US). The US disc only
  has these two sets (plus language variants of a few other files).
* File naming: `c0314.m` / `n0314.m` = chapter texts (Part 3, chapter 14;
  `c` and `n` split the script — the meaning of the split, e.g. "chapter" vs
  "narration/base", is unverified), `common.m` = UI and system text (`MP_*`
  stat names, `MESS_*` shop texts, `MDIE_*` death quotes), `dic.m` glossary,
  `yell*.m` battle quotes, `gmap_N.m` world-map narration, `tut.m`
  tutorials, `intro.m`, `ending.m`, `epilogue.m`, `digest.m`, `movie.m`,
  `videomode.m`.
* Label prefixes: `MS_` scene text (`MS_0314_OP_01` = chapter 3-14, opening
  scene 1; `_ED_` ending, `_BT_` boss/battle talk, `_TK_` talk command,
  `_VIL_` village), `MID_` base conversations, `MP_`/`MPID_`/`MJID_`/`MIID_`
  names, `MDIE_` death quotes, `MMY_`/`MYELL_` battle yells.
* The US build has 25,910 strings in 214 files; all decode cleanly as
  Shift-JIS with the tokenizer below.

### Encoding

Shift-JIS. English text is ASCII. Bytes `0x01..0x12` (except `0x0A`) start
control commands; `0x0A` is a line break inside a balloon. `#` starts an
inline formatting code (UI text). `@{0}` style placeholders appear in UI
strings that are filled by the game (`MESS_EDU_EXP_ASSIGN_CONFIRM`).

Example (`e_c0314.m`, `MS_0314_OP_01_04`), rendered by `mess.py`:

```
[FL:MICAIAH,PELLEAS,TAURONEO][BO][R上下会話][Speaker:01][ec][Say:1D]You can't
be serious, Your Majesty![eo][A][F:*][F:H]
[Speaker:10][F:s][Say:0D]But, I am. [W3]Don't you see?![W4]
```

### Control commands

Argument layout comes from the generic skipper in the text-box code
(8026C000.c, function around 0x8026FF44) and the conversation interpreter
**fn_80149434** (`80148000.c`). The meanings are from that interpreter; where
the effect is only a flag write, the meaning is a guess and marked so.

| Byte | Args | `mess.py` tag | Meaning |
|---|---|---|---|
| `01` | 1 char | `[F:c]` | per-speaker face/balloon command, see below |
| `02` | 2 chars | `[xy]`, `[Wn]` | two-letter command, see below |
| `03` | 3 chars | `[3:xyz]` | only `DFC` seen: reset a dialogue flag (guessed: "default face/camera") |
| `04` | `field\|` | `[...]` | one `\|`-terminated field; first letter(s) = subcommand |
| `05` | `fields\|...\|\|` | `[FL:a,b]` | list of fields ending in an empty field |
| `07` | 2 hex digits | `[Speaker:XY]` | make face slot X the current speaker, balloon/window Y; animates the switch |
| `08` | digit + `D`/`L`/`R` | `[Say:SD]` | open a speech balloon for slot S with tail direction Down/Left/Right, then render the following text (fn_8014A6CC) until the next stop code |
| `09` | – | `[CloseSpeaker]` | remove current speaker's face and balloon, wait (fn_8014B0C8) |
| `0A` | – | newline | inside a balloon: line break; between commands: close/reset balloon |
| `0B` | 2 chars | `[B:..]` | skipped by the interpreter (no effect) |
| `0C` | 2 hex digits | `[Select:XY]` | select slot X / window Y without the speaker-change animation (used before `0F`/`09`) |
| `0D` | 2 chars | `[Assign:..]` | attach a face object to the current slot (fn_8014AD1C, fn_800C409C) |
| `0E` | digit + D/L/R | `[SayNoWait:SD]` | like `08` but does not stop |
| `0F` | – | `[CloseSpeakerNoWait]` | like `09` without waiting |
| `10` | – | `[NewPage]` | clear balloon, continue with next page |
| `11` | – | `[A]` | wait for button press |
| `12` | – | `[Yield]` | stop for one update |
| `00` | – | – | end of string |

`01 c` (target = current speaker's face):

| c | Effect |
|---|---|
| `a` / `s` | set / clear face flag 0x800 (alternate expression on/off; guessed "a"=angry/alt, "s"=standard) |
| `*` | close balloon (sets 0x100) then behaves like `@` |
| `@` | finish the balloon (fn_8014CAC0) |
| `H` | wait until the balloon is hidden (re-executes itself until done) |
| `G`, `P` | start a special window effect (fn_801520C0 / fn_80151548), used in world-map texts |
| `I`, `J`, `S`, `c` | set global message flags (0x30000, 0x1, 0x10000, 0xD0000) |
| `g` | set flag 0x30000 and reset a face property |

`02 xy`:

| xy | Effect |
|---|---|
| `w0`..`w8` | wait 2^n frames |
| `mc` / `md` / `mo` | mouth closed / default lip-sync / open (used around "……") |
| `ec` / `eh` / `eo` / `eO` | eyes closed / half / open / alternate |
| `bn` / `bf` / `bs` | blink mode normal / fast(?) / stop(?) |
| `f+` / `f-` / `f,` | fade face in / out |
| `F0`..`F3` | screen fade variants (fn_800C835C types 2, 3, 5, 6) |
| `BO` | balloon option flag 0x8000 (unless disabled by settings) |
| `KH` | stop the "talking" state of all 9 face slots |
| `O<hex>` | set window option byte |
| `PH` / `PL` | face placed high / low |
| `VW` | wait until the current voice clip ends |
| `v<n>` | fade out voice channel n |
| `WO` / `WX` | set / clear flag 0x1000 |
| `sd` / `se` | set / clear flag 0x8 (guessed: skip disabled/enabled) |
| `nc` | clear flag 0x40 |

`04` subcommands (one `|`-terminated field):

| Field | Effect |
|---|---|
| `R<name>` | conversation background: look up `RID_<name>` in `s/rect.bin` (fn_8014A5A8) |
| `B<name>` | background change with fade (fn_8014A63C + screen fade) |
| `b<name>` | background change without fade |
| `S<name>` | play sound / BGM by label (fn_80253EE4) |
| `V<ch><name>` | play voice `<name>` on channel `<ch>` |
| `W<n>` | wait n frames (scaled by text speed) |
| `s<n>` | set text speed |
| `FT<n>` | set fade time |
| `NF<slot><name>` | load face `<name>` into `<slot>` mid-scene |
| `rk<name>`, `rb<name>` | resource load / background by resource name |

`05` subcommands (field list):

| First field | Effect |
|---|---|
| `FL` | face list: up to 16 names, each becomes `FID_<name>` and is looked up in `Face/facedata.bin`; certain names (IKE, MICAIAH, ...) are swapped for costume variants depending on story progress (fn_8014AE04) |
| `rc` | `rc|name|a|b|c|d|e|` rectangle/illustration placement (fn_80094648) |
| `FX` | `FX|name|n|` start a screen effect |

### Inline `#` codes (UI text renderer, `800C8000.c`)

Parsed by the string renderer near 0x800CB928; numbers are fixed-width
decimal digits (fn_800CA1B4).

| Code | Meaning |
|---|---|
| `##` | literal `#` |
| `#Ann` | alpha |
| `#Rnn` `#Gnn` `#Bnn` | colour channel |
| `#Cnn` / `#c` | palette colour on / restore |
| `#Fnn` | switch font |
| `#Pnnn` | inline icon (3 digits), e.g. `#P011` axe icon |
| `#Snn` `#Xnn` `#Ynn` / `#s` `#x` | scale both / x / y, and reset |
| `#E` `#e`, `#O` `#o`, `#K` `#k`, `#Inn` `#i`, `#D` | style toggles (unverified) |

## Fonts (`Fonts/*.cms`)

LZ10-compressed bitmap fonts. `talk` = dialogue, `system` = menus, `fe_font`,
`alpha` and `bigkana` = large title glyphs, `ruby` = furigana, `debug`. `_w`
variants are for 16:9.

```
0x00 u16 0
0x02 u16 first_code          0x0020
0x04 u16 last_code           e.g. 0xEA74 (Shift-JIS)
0x08 u16 line_height         talk: 24, system: 20
0x0A u16 ?                   0x0C u16 ascent? (talk: 19)
0x16 u16 sheet_bytes         0x8000
0x18 u32 sheet_count         talk: 23
0x1C u32 sheet_width         256
0x20 u16 sheet_height        256 (ruby: 128)
0x22 u16 glyph_table_offset  0x30
0x24 u32 texture_offset      = end of glyph table
0x28 u32 texture_size
0x30 glyph[], 16 bytes, sorted by code:
     u16 code, u16 sheet, u16 x, u16 y, u8 w, u8 h, u8 x_offset,
     u8 y_offset (baseline-relative), u8 advance, u8[3] 0
     sheets: GX I4 texture data (4-bit alpha, 8x8 tiles)
```

`talk.cms` has 4113 glyphs (Shift-JIS kanji and kana plus ASCII). Verified by
rendering the sheets (`font.py Fonts/talk.cms OUTDIR`) and checking glyph
rectangles; the meaning of the two unnamed header fields is not confirmed.

Porting note: for a native port, a TTF font can replace these, but keeping
the bitmaps preserves the look; the glyph table maps straight to a texture
atlas.
