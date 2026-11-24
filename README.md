# Fire Emblem: Radiant Dawn decompilation

[![Code](https://bytematch.dev/Cenzo239/radiant-dawn-decomp.svg?label=Code&measure=matched_code_percent)](https://bytematch.dev/Cenzo239/radiant-dawn-decomp)
[![Functions](https://bytematch.dev/Cenzo239/radiant-dawn-decomp.svg?label=Functions&measure=matched_functions)](https://bytematch.dev/Cenzo239/radiant-dawn-decomp)

A work-in-progress matching decompilation of *Fire Emblem: Radiant Dawn* for the Wii
(US release, game ID `RFEE01`, Rev 1). The build reproduces the original `main.dol`
byte for byte (SHA-1 `d1b8deabfec5a96bf38945665ffe203867612c1c`), linking C/C++ wherever it
already matches and the original assembly everywhere else.

Progress is tracked on [ByteMatch](https://bytematch.dev/Cenzo239/radiant-dawn-decomp).

## No game data

This repository contains **no game data**: no disc image, no `main.dol`, no extracted or
converted assets, textures, audio, video, text or saves. You need your own legally obtained
copy of the game to build anything. Every push is checked by a game-data guard
(`tools/guard/`, also run as a GitHub workflow) that refuses disc files, Nintendo container
formats, media files, binaries and anything identical to a local game file.

This project is not affiliated with, endorsed or sponsored by Nintendo or Intelligent Systems.
*Fire Emblem* is a trademark of Nintendo.

## Building

Requirements: Python 3 and [ninja](https://ninja-build.org/); on macOS and Linux the
CodeWarrior compilers run through a wrapper. See [docs/dependencies.md](docs/dependencies.md).

1. Extract the disc of your own copy (Dolphin: *Data Partition* → *Extract Entire Partition*)
   and place or link the result at `orig/RFEE01/` so that `orig/RFEE01/sys/main.dol` exists.
2. Configure and build:

   ```sh
   python3 configure.py
   ninja
   ```

   The build ends with `main.dol: OK` when the output matches the original.
3. Install the game-data guard hooks once per clone before committing:

   ```sh
   sh tools/guard/install.sh
   ```

`ninja progress` prints the progress numbers, and `ninja build/RFEE01/report.json` writes the
objdiff report that ByteMatch reads. [objdiff](https://github.com/encounter/objdiff) can be pointed at
the project root to diff single functions.

## Contributing

Help with matching is welcome, including work done with AI agents such as
[decompdecomp](https://github.com/n-delic/decompdecomp). See [CONTRIBUTING.md](CONTRIBUTING.md).

## Layout

- `config/RFEE01/`: decomp-toolkit config, `symbols.txt`, `splits.txt` and the generated unit list
- `src/game/`: one file per decompiled game function, grouped by address region
  (`wip/` holds drafts that do not match yet, `equiv/` functionally equivalent ones)
- `src/tu/`: generated translation units that the build links (never edited by hand)
- `lib/`: SDK, MSL, NW4R and HOME Button menu sources from other public decompilations (see below)
- `tools/`: build generators (`tools/build/`), matching helpers, library placement (`tools/lib/`),
  file format readers (`tools/formats/`), the game-data guard (`tools/guard/`)
- `docs/`: [build pipeline](docs/BUILD.md), [matching notes](docs/MATCHING.md),
  [library code](docs/LIB.md), [file formats](docs/FORMATS.md) and more

## Facts about the binary

- All game code is in one `main.dol`: 3.4 MB of `.text`, about 12,800 functions, no REL modules.
- The compiler is CodeWarrior 4.1 build 60831. Libraries include RVL_SDK, NW4R (SND, LYT),
  the HOME Button menu and MSL.
- Some original source file names survive in strings, for example `GActor.c`, `GCamera.c` and `video.cpp`.

## Credits

- [decomp-toolkit](https://github.com/encounter/decomp-toolkit), [dtk-template](https://github.com/encounter/dtk-template)
  and [objdiff](https://github.com/encounter/objdiff) by encounter and contributors.
- Library sources in `lib/` are copied from these public decompilations; their own license files
  are kept where they have one:
  [doldecomp/ogws](https://github.com/doldecomp/ogws),
  [koopthekoopa/wii-ipl](https://github.com/koopthekoopa/wii-ipl),
  [SMGCommunity/Petari](https://github.com/SMGCommunity/Petari),
  [xbret/xenoblade](https://github.com/xbret/xenoblade),
  [Nikman800/wiiplay-pc](https://github.com/Nikman800/wiiplay-pc),
  [TeamOrre/xd-decomp](https://github.com/TeamOrre/xd-decomp).
- Much of the decompilation work was done with the help of AI coding agents and checked by
  byte comparison against the original binary.

## License

The project's own code is released under [CC0 1.0](LICENSE). Files under `lib/` keep the
license of the project they come from.
