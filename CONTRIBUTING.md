# Contributing

Help is welcome, especially with matching functions that are still assembly. Contributions
made with AI agents are welcome too. Most of this project was made with AI coding agents.
Every result is checked by byte comparison against the original binary, and that check is
what counts.

This guide covers the normal setup and the [decompdecomp](https://github.com/n-delic/decompdecomp)
desktop app.

## Ground rules

1. **Use your own copy of the game.** The target is the US release of *Fire Emblem: Radiant Dawn*,
   game ID `RFEE01`, **Revision 1**. Other regions and Rev 0 have a different `main.dol` and do
   not work. Your extracted `orig/RFEE01/sys/main.dol` must have the SHA-1
   `d1b8deabfec5a96bf38945665ffe203867612c1c` (the build output must match it too).
2. **Never commit game data.** That means no disc image, no `main.dol`, no extracted or converted
   files, no `build/` output, no generated assembly or Ghidra output from the game. Before your
   first commit, install the guard hooks once per clone:

   ```sh
   sh tools/guard/install.sh
   ```

   The same check runs on every pull request. Don't bypass it with `--no-verify`.
3. **Only byte-exact code is a match.** Don't submit code that only comes close. Put close
   attempts under `wip/` (see below).
4. **Keep the build green.** `ninja` must still end with `main.dol: OK`.

## Setup

Requirements: Python 3 and [ninja](https://ninja-build.org/). On Linux and macOS, the
CodeWarrior compilers run through [wibo](https://github.com/decompals/wibo), which the build
downloads for you. The same goes for the compilers and decomp-toolkit. See
[docs/dependencies.md](docs/dependencies.md).

```sh
git clone https://github.com/Cenzo239/radiant-dawn-decomp
cd radiant-dawn-decomp
# Extract your disc with Dolphin: Data Partition -> Extract Entire Partition,
# then put the result (or a symlink to it) at orig/RFEE01/ so orig/RFEE01/sys/main.dol exists.
python3 configure.py
ninja                     # ends with "main.dol: OK"
sh tools/guard/install.sh
```

`ninja progress` prints the progress numbers. `ninja build/RFEE01/report.json` writes the
objdiff report. [objdiff](https://github.com/encounter/objdiff) can open the project root.

## Compiler and flags

- Compiler: CodeWarrior `GC/3.0a5.2` (4.1 build 60831). Don't use the Wii compilers. They insert
  loop-alignment nops that the game doesn't have.
- Flags: the defaults in `tools/check_func.py` (`-O4,p -inline auto -enum int -fp hardware ...`).
- Many files need `#pragma use_lmw_stmw on` around functions that save 5 or more registers.

[docs/MATCHING.md](docs/MATCHING.md) collects everything we've learned about this compiler.
Read it before you start. It saves a lot of attempts.

## Where code goes

The source of truth is the per-function files under `src/game/`.
**Everything under `src/tu/` is generated. Don't edit it by hand, and don't submit changes to it.**

- Put a matched function in `src/game/<region>/fn_<address>.c` (or `.cpp` with `extern "C"`).
  Use one file per run of neighbouring functions, in address order.
- Keep the `symbols.txt` names (`fn_8XXXXXXX`, `lbl_8XXXXXXX`). If you know what a function does,
  add a comment with a proposed real name, but don't rename it.
- Shared types go in the region's `types.h`. Declare globals `extern` by their `lbl_` name.
- Close attempts go in `src/game/<region>/wip/` with a comment that says how close they got.
  Functionally equivalent but not byte-exact versions go in `equiv/`.
- Check a file before you submit it:

  ```sh
  python3 -I tools/check_func.py src/game/<region>/fn_XXXXXXXX.c -v
  ```

  It must print `MATCH` and exit 0. It also checks that every call and data reference points at
  the original address.

After merging, the maintainer reruns the build generators (see [docs/BUILD.md](docs/BUILD.md)) so
that new matches replace assembly in `src/tu/`. You don't have to do that yourself.

## Using decompdecomp

[decompdecomp](https://github.com/n-delic/decompdecomp) is a desktop app (Linux, Windows, macOS)
where AI agents write C, and a function only counts when the game's compiler reproduces it byte
for byte. It can open existing `configure.py` + `ninja` projects like this one, so the
repository doesn't need any changes to work with it.

1. Do the setup above once and make sure `ninja` prints `main.dol: OK`. That confirms your disc
   and toolchain are right before any agent starts.
2. In decompdecomp: **New project → Continue a community decomp**, and paste
   `https://github.com/Cenzo239/radiant-dawn-decomp`. The app clones the repository into its own
   folder on a local `decomp-wtf` branch and runs the project's setup. Point it at your own
   extracted `RFEE01` Rev 1 files when it asks.
3. Pick a compiler setting of **GC/3.0a5.2** if the app asks for one.
4. Let it run. Each match becomes a commit on the local `decomp-wtf` branch. The app doesn't push
   anything by itself.
5. Before opening a pull request, check the result:
   - If the app changed files under `src/tu/`, move each matched function into a file under
     `src/game/<region>/` as described above, and drop the `src/tu/` changes.
   - Run `tools/check_func.py` on every file you add, and run `ninja` once more.
   - Make sure no game data, assembly dumps or app files (logs, databases, `.decomp`) are in
     the commit. The guard hook refuses most of them.

Useful targets for agents: functions that are still assembly, and the near misses in the `wip/`
folders. Many of those differ only in register allocation. decompdecomp's permuter works on
exactly that kind of difference.

Note: decompdecomp is new. Its GameCube/Wii support is still marked beta. If something in the
import doesn't work with this repository, open an issue and describe what happened.

## Pull requests

- Fork the repository, push a branch and open a pull request against `main`.
- Keep pull requests small: one region or one group of related functions.
- In the description, list the functions you matched and say which tool or agent you used.
- Use a commit author address you're happy to publish (GitHub's noreply address works).
- Contributions are released under the project's [CC0 1.0](LICENSE) license. Files under `lib/`
  keep the license of the project they come from.
