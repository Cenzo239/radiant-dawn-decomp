#!/usr/bin/env python3
"""Compile the sources of public decomps with the local MWCC (never executes their code).

Usage: tools/lib/libcompile.py NAME REPO OUTDIR [-j N] [--filter substr]

NAME picks a spec below. Objects land in OUTDIR/NAME__<path with / -> __>.o and
OUTDIR/manifest.json gets one entry per source, keyed "NAME/<repo-relative path>":
  {"unit": ..., "cc": ..., "flags": [... paths rewritten to lib/NAME/<path>]}
"""
import argparse, json, os, re, shlex, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WIBO = os.path.join(ROOT, "tools/wibo_guard")

BASE = ["-nodefaults", "-proc gekko", "-align powerpc", "-enum int", "-fp hardware", "-Cpp_exceptions off",
        "-O4,p", "-inline auto", '-pragma "cats off"', '-pragma "warn_notinlined off"', "-maxerrors 1",
        "-nosyspath", "-RTTI off", "-fp_contract on", "-str reuse"]

SPECS = {
    "xeno": {
        "src": ["libs/RVL_SDK/src/revolution/hbm"],
        "flags": BASE + ["-lang=c++", "-enc SJIS", "-ipa file", "-fp_contract off", "-sdata 0", "-sdata2 0", "-RTTI on",
                         "-i include", "-i libs/PowerPC_EABI_Support/include/stl", "-i libs/PowerPC_EABI_Support/include/",
                         "-i libs/RVL_SDK/include/", "-i libs/RVL_SDK/src/revolution/hbm/include/",
                         "-DHBM_VERSION=20070709", "-DNDEBUG=1"],
        "cc": "GC/3.0a5.2",
    },
    "wii-ipl": {
        "src": ["libs/RVL_SDK/src", "libs/NW4R/src", "libs/MSL/src", "libs/Runtime/src", "libs/MetroTRK/src", "libs/EGG/src"],
        "flags": BASE + ["-W nomissingreturn", "-DSDK_IPL", "-D_REVOLUTION", "-DMEM_MANAGER_DIRECT", "-DTARGET_RVL",
                         "-i include", "-i include/global", "-i libs/MetroTRK/include", "-i libs/Runtime/include",
                         "-i libs/MSL/include", "-i libs/RVL_SDK/include", "-i libs/RevoEX/include", "-i libs/NW4R/include",
                         "-i libs/EGG/include", "-ir libs/RVL_SDK/include/private/bte", "-i libs/RVL_SDK/include/private/bte",
                         "-DNDEBUG=1", "-DBUILD_VERSION=0", "-DVERSION_43U", "-ipa file", "-fp_contract off", "-enc SJIS"],
        "cc": "GC/3.0a5.2",
        "cc_override": {"libs/RVL_SDK/src/bte/": "GC/3.0a5"},
    },
    "petari": {
        "src": ["src/RVL_SDK", "src/nw4r"],
        "flags": [f for f in BASE if f != "-inline auto"] + ["-inline auto,level=3", "-enc SJIS", "-ipa file", "-sdata 8", "-sdata2 8",
                "-i libs/MSL_C++/include", "-i libs/MSL_C/include", "-i libs/MetroTRK/include", "-i libs/RVLFaceLib/include",
                "-i libs/RVL_SDK/include", "-i libs/Runtime/include", "-i src/RVL_SDK/bte", "-i include", "-i libs/nw4r/include",
                "-ir libs/RVL_SDK/include/revolution/bte", "-DREVOLUTION", "-d VERSION=0", "-DNDEBUG=1"],
        "cc": "GC/3.0a5.2",
        "flag_override": {"src/RVL_SDK/wpad/": ("-fp hardware", "-fp off")},
    },
    "wiiplay": {  # Nikman800/wiiplay-pc (CC0): Wii Play (RHAE01, SDK Dec 2006) SDK sources derived from ogws, incl. WPADHIDParser.c
        "src": ["src/revolution"],
        "flags": BASE + ["-i include", "-i include/MSL", "-i include/MSL/internal", "-ir include/revolution/BTE", "-DREVOLUTION",
                         "-DVERSION_RHAE01_01", "-enc SJIS", "-fp_contract off", "-ipa file", "-DNDEBUG=1", "-DBUILD_VERSION=0",
                         "-DVERSION_RHAE01"],
        "cc": "GC/3.0a5.2",
    },
    "xd": {  # TeamOrre/xd-decomp (CC0): Dolphin SDK syn/seq (GameCube 2005), FE10's RVL SDK SEQ/SYN are these ported
        "src": ["libs/dolphin/src/syn", "libs/dolphin/src/seq", "libs/dolphin/src/mix"],
        "flags": BASE + ["-char unsigned", "-fp_contract off", "-ipa file", "-enc SJIS", "-D__GEKKO__", "-DDOLPHIN_SDK",
                         "-i libs/dolphin/include", "-i libs/dolphin/include/libc", "-i libs/dolphin/src/syn", "-DNDEBUG=1"],
        "cc": "GC/3.0a5.2",
    },
    "dolsdk2001": {  # doldecomp/dolsdk2001: Dolphin SDK 2001 syn/seq sources (reference only)
        "src": ["src/syn", "src/seq", "src/mix"],
        "flags": BASE + ["-char unsigned", "-fp_contract off", "-ipa file", "-enc SJIS", "-i include", "-i include/libc", "-ir src", "-DNDEBUG=1"],
        "cc": "GC/3.0a5.2",
    },
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("repo")
    ap.add_argument("out")
    ap.add_argument("-j", type=int, default=6)
    ap.add_argument("--filter", default="")
    a = ap.parse_args()
    spec = SPECS[a.name]
    os.makedirs(a.out, exist_ok=True)
    mpath = os.path.join(a.out, "manifest.json")
    man = json.load(open(mpath)) if os.path.exists(mpath) else {}
    jobs = []
    for sd in spec["src"]:
        for dp, _dn, fns in os.walk(os.path.join(a.repo, sd)):
            for fn in sorted(fns):
                if not fn.endswith((".c", ".cpp")):
                    continue
                rel = os.path.relpath(os.path.join(dp, fn), a.repo)
                if a.filter not in rel:
                    continue
                cc = spec["cc"]
                for pre, c in spec.get("cc_override", {}).items():
                    if rel.startswith(pre):
                        cc = c
                flags = list(spec["flags"])
                for pre, (old, new) in spec.get("flag_override", {}).items():
                    if rel.startswith(pre):
                        flags = [new if f == old else f for f in flags]
                key = a.name + "/" + rel
                jobs.append((rel, cc, flags, key))

    def rewrite(f):
        m = re.match(r"^(-ir?) (\S+)$", f)
        if m:
            return f"{m.group(1)} lib/{a.name}/{m.group(2)}"
        return f

    for rel, cc, flags, key in jobs:
        man[key] = {"unit": a.name + "__" + rel.replace("/", "__") + ".o", "cc": cc, "flags": [rewrite(f) for f in flags]}
    json.dump(man, open(mpath, "w"), indent=1)

    def run(j):
        rel, cc, flags, key = j
        outp = os.path.join(a.out, man[key]["unit"])
        ccp = os.path.join(ROOT, "build/compilers", cc, "mwcceppc.exe")
        cmd = [WIBO, ccp] + [x for f in flags for x in shlex.split(f)] + ["-c", rel, "-o", outp]
        r = subprocess.run(cmd, cwd=a.repo, capture_output=True, text=True)
        return key, ("ok" if r.returncode == 0 and os.path.exists(outp) else "FAIL " + (r.stdout + r.stderr)[:400].replace("\n", " | "))

    with ThreadPoolExecutor(a.j) as ex:
        for key, st in ex.map(run, jobs):
            print(key, st, flush=True)


if __name__ == "__main__":
    main()
