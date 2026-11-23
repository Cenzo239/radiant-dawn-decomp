#!/usr/bin/env python3
"""Write a self-contained local HTML progress page (default build/progress.html).

Reads only files that already exist; compiles nothing, so it is safe to run
while agents are working:

  config/RFEE01/symbols.txt     function list with addresses and sizes
  build/m2c/matched_names.txt   byte-exact game functions (last tally)
  src/game/**                   definitions in non-wip/non-equiv files (new exact
                                matches since the last tally), wip/ drafts
  docs/EQUIVALENT.tsv           register/schedule-only near misses
  lib/map.json, lib/verified.json   SDK range (0x8028BC54-0x80360900)

Game classes (each function in exactly one):
  exact       byte-exact
  equivalent  docs/EQUIVALENT.tsv (renamed / regs / slots / sched)
  differs     a draft exists in a wip/ folder, but it is not exact or equivalent
  none        no draft

Each run appends a snapshot to build/progress_history.json when the numbers
changed, which feeds the trend chart. KB means 1000 bytes, as in the round reports.

Usage: python3 tools/progress_html.py [-o build/progress.html] [--open]
"""
import argparse
import datetime
import html
import json
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LIB_LO, LIB_HI = 0x8028BC54, 0x80360900
CLASSES = [
    ("exact", "Exact", "byte-identical to the original"),
    ("equiv", "Equivalent", "only registers/order differ (EQUIVALENT.tsv)"),
    ("differs", "Draft differs", "draft in wip/, not exact or equivalent yet"),
    ("none", "No draft", "nothing written yet"),
]


def p(*parts):
    return os.path.join(ROOT, *parts)


def load_functions():
    fn = {}
    pat = re.compile(r"^(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)")
    for line in open(p("config/RFEE01/symbols.txt")):
        m = pat.match(line)
        if m:
            fn[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
    return fn


def defined_names(text, names):
    """Names from `names` that the text defines (NAME(...) followed by '{')."""
    text = re.sub(r"//[^\n]*|/\*.*?\*/", "", text, flags=re.S)
    out = set()
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", text):
        n = m.group(1)
        if n not in names:
            continue
        i, depth = m.end(), 1
        while i < len(text) and depth:
            c = text[i]
            depth += c == "("
            depth -= c == ")"
            i += 1
        while i < len(text) and text[i] in " \t\r\n":
            i += 1
        if text.startswith("{", i):
            out.add(n)
    return out


def scan_sources(names):
    main, wip = set(), set()
    for dp, _, files in os.walk(p("src/game")):
        for f in files:
            if not f.endswith((".c", ".cpp")):
                continue
            path = os.path.join(dp, f)
            d = defined_names(open(path, errors="replace").read(), names)
            if "/wip/" in path:
                wip |= d
            elif "/equiv/" not in path:
                main |= d
    return main, wip


def load_equiv():
    eq = {}
    for line in open(p("docs/EQUIVALENT.tsv")):
        if line.startswith("#") or not line.strip():
            continue
        c = line.rstrip("\n").split("\t")
        eq[c[0]] = (c[1], c[5] if len(c) > 5 else "")
    return eq


def regions():
    out = []
    for d in os.listdir(p("src/game")):
        m = re.match(r"^(r[A-Z]\d?)_([0-9A-F]{8})$", d)
        if m:
            out.append((int(m.group(2), 16), m.group(1), d))
    return sorted(out)


def lib_module(path):
    s = path.lower()
    if "hbm" in s or "homebutton" in s:
        return "HOME Button menu"
    if "metrotrk" in s:
        return "MetroTRK (Debugger)"
    if "/msl" in s:
        return "MSL (C library)"
    if "runtime" in s:
        return "Runtime"
    if "nw4r" in s:
        parts = path.split("/")
        i = [x.lower() for x in parts].index("nw4r")
        sub = parts[i + 1] if parts[i + 1] != "src" else parts[i + 2]
        return "NW4R " + sub
    if "/egg/" in s:
        return "EGG"
    if "rvlfacelib" in s:
        return "RFL (Mii)"
    if "/syn" in s or "/seq" in s or "/mix" in s:
        return "SDK AX (MIX/SYN/SEQ)"
    parts = path.split("/")
    sub = parts[-2]
    return "SDK " + sub.upper()


def git_head():
    try:
        return subprocess.run(["git", "-C", ROOT, "log", "-1", "--format=%h %cd", "--date=format:%d.%m.%Y %H:%M"],
                              capture_output=True, text=True, timeout=10).stdout.strip()
    except Exception:
        return ""


def kb(b):
    return f"{b / 1000:,.1f}".replace(",", " ")


def pct(a, b):
    return 100.0 * a / b if b else 0.0


def collect():
    fn = load_functions()
    game = {n: v for n, v in fn.items() if v[0] < LIB_LO}
    tally = set(open(p("build/m2c/matched_names.txt")).read().split()) if os.path.exists(p("build/m2c/matched_names.txt")) else set()
    lib_names = {n for n, v in fn.items() if LIB_LO <= v[0] < LIB_HI}
    main, wip = scan_sources(set(game) | lib_names)
    eq = load_equiv()
    cls, sub = {}, {}
    new_exact = set()
    for n in game:
        if n in tally or n in main:
            cls[n] = "exact"
            if n not in tally:
                new_exact.add(n)
        elif n in eq:
            cls[n] = "equiv"
            sub[n] = eq[n]
        elif n in wip:
            cls[n] = "differs"
        else:
            cls[n] = "none"

    regs = regions()
    starts = [r[0] for r in regs]

    def region_of(addr):
        i = 0
        for k, s in enumerate(starts):
            if s <= addr:
                i = k
        return regs[i][1]

    reg_rows = defaultdict(lambda: {"bytes": Counter(), "count": Counter(), "lo": None, "hi": 0, "funcs": []})
    for n, (a, s) in sorted(game.items(), key=lambda x: x[1][0]):
        r = reg_rows[region_of(a)]
        r["bytes"][cls[n]] += s
        r["count"][cls[n]] += 1
        r["lo"] = a if r["lo"] is None else min(r["lo"], a)
        r["hi"] = max(r["hi"], a + s)
        r["funcs"].append((a, s, cls[n], n))

    # SDK range
    m = json.load(open(p("lib/map.json")))
    ver = json.load(open(p("lib/verified.json")))
    tgt = {a: (n, s) for n, (a, s) in fn.items() if LIB_LO <= a < LIB_HI and n.startswith("fn_")}
    mod_of, size_of = {}, {}
    for src, ent in m["sources"].items():
        for name, (a, s, st) in ent["functions"].items():
            mod_of.setdefault(a, lib_module(src))
            size_of[a] = max(size_of.get(a, 0), s)
    vaddr = {a for d in ver.values() for a in d.values()}
    got = {a for a in tgt if a in vaddr}
    # the game's own __sinit sits at the start of the SDK range and is matched in src/game
    game_side = {a for a in tgt if tgt[a][0] in tally or tgt[a][0] in main}
    got |= game_side
    for a in list(vaddr):
        sz = size_of.get(a, 0)
        for a2 in range(a + 4, a + sz, 4):
            if a2 in tgt and a2 not in got and a2 + tgt[a2][1] <= a + sz:
                got.add(a2)
                mod_of.setdefault(a2, mod_of.get(a))
    lib_mods = defaultdict(lambda: {"ok": 0, "okb": 0, "n": 0, "b": 0})
    last = "SDK (unassigned)"
    lib_open = []
    for a in sorted(tgt):
        mod = "Game code in the SDK range" if a in game_side else (mod_of.get(a) or last)
        last = mod
        r = lib_mods[mod]
        r["n"] += 1
        r["b"] += tgt[a][1]
        if a in got:
            r["ok"] += 1
            r["okb"] += tgt[a][1]
        else:
            lib_open.append((a, tgt[a][1], tgt[a][0], mod))

    tot_b = Counter()
    tot_c = Counter()
    for n, (a, s) in game.items():
        tot_b[cls[n]] += s
        tot_c[cls[n]] += 1
    eq_b = Counter()
    eq_sym = Counter()
    for n, (k, symc) in sub.items():
        eq_b[k] += game[n][1]
        eq_sym["clean" if symc == "clean" else "flagged" if symc else "unchecked"] += game[n][1]
    open_list = sorted(((game[n][1], n, cls[n]) for n in game if cls[n] in ("differs", "none")), reverse=True)

    return {
        "game_bytes": sum(s for _, s in game.values()), "game_count": len(game),
        "tot_b": tot_b, "tot_c": tot_c, "eq_b": eq_b, "eq_sym": eq_sym,
        "regions": [(rid, reg_rows[rid]) for _, rid, _ in regs if rid in reg_rows],
        "new_exact": sorted(new_exact, key=lambda n: game[n][0]), "game": game,
        "open_list": open_list,
        "lib_n": len(tgt), "lib_b": sum(s for _, s in tgt.values()),
        "lib_ok": len(got), "lib_okb": sum(tgt[a][1] for a in got),
        "lib_mods": sorted(lib_mods.items(), key=lambda x: -x[1]["b"]), "lib_open": lib_open,
    }


# Earlier round tallies (exact / equivalent KB of game code) from the round reports, so the
# trend starts before this script existed. Snapshots of later runs are appended after them.
SEED = [
    ("2026-11-04", "R5", 807, None), ("2026-11-04", "R6", 947, None), ("2026-11-05", "R7", 1090, None),
    ("2026-11-05", "R8", 1214, None), ("2026-11-05", "R9", 1314, None), ("2026-11-05", "R10", 1408, None),
    ("2026-11-05", "R11", 1534, None), ("2026-11-05", "R12", 1666, None), ("2026-11-06", "R13", 1788, None),
    ("2026-11-07", "R14", 1883, None), ("2026-11-10", "R15", 1940, None), ("2026-11-10", "R16", 1976, None),
    ("2026-11-11", "R17", 2006, None), ("2026-11-11", "R18", 2027, 250), ("2026-11-11", "R19", 2032, 382),
    ("2026-11-12", "R20", 2041, 454), ("2026-11-12", "R21", 2053, 476),
]


def update_history(d):
    path = p("build/progress_history.json")
    hist = [dict(t=t, label=l, exact=e * 1000, equiv=(q * 1000 if q is not None else None), game=2642868, seed=True)
            for t, l, e, q in SEED]
    if os.path.exists(path):
        try:
            hist = json.load(open(path))
        except Exception:
            hist = []
    snap = {
        "exact": d["tot_b"]["exact"], "equiv": d["tot_b"]["equiv"], "differs": d["tot_b"]["differs"],
        "none": d["tot_b"]["none"], "game": d["game_bytes"], "exact_n": d["tot_c"]["exact"],
        "lib_ok": d["lib_okb"], "lib": d["lib_b"],
    }
    if hist[-1].get("seed") or {k: hist[-1].get(k) for k in snap} != snap:
        snap["t"] = datetime.datetime.now().isoformat(timespec="minutes")
        hist.append(snap)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        json.dump([h for h in hist if not h.get("seed")], open(path, "w"), indent=0)
    return hist


CSS = """
:root{--bg:#f6f5f1;--card:#fff;--ink:#1d1d1b;--muted:#6b6a65;--line:#e4e2db;
--exact:#2f8a4e;--equiv:#3b7dc4;--differs:#d9902b;--none:#c9c6bd;--accent:#2f8a4e}
@media (prefers-color-scheme: dark){:root:not([data-theme="light"]){--bg:#151614;--card:#1f201e;--ink:#ecebe6;
--muted:#9c9b94;--line:#33342f;--exact:#4fb06e;--equiv:#5f9be0;--differs:#e6a64a;--none:#4a4b46}}
*{box-sizing:border-box}
body{margin:0;background:var(--bg);color:var(--ink);font:15px/1.5 -apple-system,BlinkMacSystemFont,"Segoe UI",Helvetica,Arial,sans-serif}
main{max-width:1080px;margin:0 auto;padding:28px 16px 64px}
.top{display:flex;justify-content:space-between;align-items:flex-start;gap:12px;flex-wrap:wrap}
button#refresh{font:inherit;font-weight:600;padding:8px 16px;border-radius:8px;border:1px solid var(--line);background:var(--exact);color:#fff;cursor:pointer}
button#refresh:disabled{opacity:.6;cursor:wait}
#msg{font-size:12.5px;color:var(--muted);margin-top:4px;text-align:right}
h1{font-size:26px;margin:0 0 2px;letter-spacing:-.01em}
h2{font-size:17px;margin:36px 0 12px}
.sub{color:var(--muted);font-size:13px}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:16px;margin-top:20px}
.card{background:var(--card);border:1px solid var(--line);border-radius:12px;padding:18px 20px}
.card h3{margin:0 0 4px;font-size:14px;font-weight:600;color:var(--muted);text-transform:uppercase;letter-spacing:.04em}
.big{font-size:40px;font-weight:700;letter-spacing:-.02em;line-height:1.1}
.big small{font-size:16px;font-weight:500;color:var(--muted);margin-left:6px}
.bar{display:flex;height:14px;border-radius:7px;overflow:hidden;background:var(--none);margin:12px 0 10px}
.bar.thin{height:10px;margin:0;border-radius:5px;min-width:120px}
.bar span{display:block;height:100%}
.exact{background:var(--exact)}.equiv{background:var(--equiv)}.differs{background:var(--differs)}.none{background:var(--none)}
.legend{display:grid;grid-template-columns:auto 1fr auto auto;gap:4px 12px;font-size:13.5px;align-items:center}
.legend .dot{width:10px;height:10px;border-radius:3px}
.legend .n{text-align:right;white-space:nowrap;font-variant-numeric:tabular-nums}
.legend .pc{text-align:right;font-weight:600;font-variant-numeric:tabular-nums;min-width:52px}
table{width:100%;border-collapse:collapse;font-size:13.5px;font-variant-numeric:tabular-nums}
th{text-align:left;font-weight:600;color:var(--muted);font-size:12px;text-transform:uppercase;letter-spacing:.03em;padding:6px 8px;border-bottom:1px solid var(--line)}
td{padding:6px 8px;border-bottom:1px solid var(--line);vertical-align:middle}
td.r,th.r{text-align:right}
.tablewrap{overflow-x:auto;background:var(--card);border:1px solid var(--line);border-radius:12px;padding:6px 10px}
.mono{font-family:ui-monospace,SFMono-Regular,Menlo,monospace;font-size:12.5px}
.map{background:var(--card);border:1px solid var(--line);border-radius:12px;padding:12px 14px}
.maprow{display:grid;grid-template-columns:44px 1fr;gap:8px;align-items:center;margin:3px 0}
.maprow svg{width:100%;height:16px;display:block;border-radius:3px}
.note{font-size:13px;color:var(--muted);margin-top:8px}
.pill{display:inline-block;padding:1px 8px;border-radius:10px;font-size:12px;color:#fff}
details summary{cursor:pointer;color:var(--muted);font-size:13.5px;margin-top:8px}
"""


JS = """<script>
const b=document.getElementById('refresh'),m=document.getElementById('msg');
if(location.protocol==='file:'){m.textContent='To refresh, run tools/progress_html.py --serve.';b.onclick=()=>m.textContent='Only available with tools/progress_html.py --serve.';}
b.onclick=b.onclick||async()=>{b.disabled=true;b.textContent='Computing …';
 try{const r=await fetch('/refresh',{method:'POST'});if(!r.ok)throw 0;location.reload()}
 catch(e){m.textContent='Failed. Is tools/progress_html.py --serve still running?';b.disabled=false;b.textContent='Refresh'}};
</script>"""


def bar(parts, total, thin=False):
    segs = "".join(f'<span class="{k}" style="width:{pct(v, total):.3f}%" title="{k}: {pct(v, total):.1f}%"></span>'
                   for k, v in parts if v)
    return f'<div class="bar{" thin" if thin else ""}">{segs}</div>'


def trend_svg(hist):
    W, H, pad = 900, 200, 34
    n = len(hist)

    def x(i):
        return pad + (W - 2 * pad) * i / max(n - 1, 1)

    def y(v):
        return H - pad - (H - 2 * pad) * v / 100

    lines = []
    for col, f in (("var(--exact)", lambda h: pct(h["exact"], h["game"])),
                   ("var(--equiv)", lambda h: pct(h["exact"] + h["equiv"], h["game"]) if h.get("equiv") is not None else None),
                   ("var(--muted)", lambda h: pct(h["lib_ok"], h["lib"]) if h.get("lib") else None)):
        pts = [(x(i), y(v)) for i, h in enumerate(hist) for v in [f(h)] if v is not None]
        if len(pts) > 1:
            lines.append(f'<polyline fill="none" stroke="{col}" stroke-width="2.5" points="{" ".join(f"{a:.1f},{b:.1f}" for a, b in pts)}"/>')
        lines += [f'<circle cx="{a:.1f}" cy="{b:.1f}" r="3" fill="{col}"/>' for a, b in pts]
    grid = "".join(f'<line x1="{pad}" x2="{W - pad}" y1="{y(g)}" y2="{y(g)}" stroke="var(--line)"/>'
                   f'<text x="2" y="{y(g) + 4}" font-size="11" fill="var(--muted)">{g}%</text>' for g in (0, 25, 50, 75, 100))
    lab = "".join(f'<text x="{x(i):.1f}" y="{H - 10}" font-size="10.5" fill="var(--muted)" text-anchor="middle">'
                  f'<title>{html.escape(h["t"].replace("T", " "))}</title>{html.escape(h.get("label") or h["t"][5:10].replace("-", "."))}</text>'
                  for i, h in enumerate(hist) if h.get("label") or i == n - 1)
    return (f'<div class="map"><svg viewBox="0 0 {W} {H}" style="width:100%;height:auto">{grid}{"".join(lines)}{lab}</svg>'
            '<div class="note"><span style="color:var(--exact)">●</span> Game code exact &nbsp; '
            '<span style="color:var(--equiv)">●</span> exact + equivalent (counted from round 18) &nbsp; '
            '<span style="color:var(--muted)">●</span> SDK verified<br>R5 to R21 come from the round reports, '
            'after that one point per script run with changed numbers (build/progress_history.json).</div></div>')


def render(d, hist):
    G = d["game_bytes"]
    tb, tc = d["tot_b"], d["tot_c"]
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M")
    head = git_head()
    out = []
    w = out.append
    w('<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">')
    w(f"<title>FE10 decomp progress</title><style>{CSS}</style></head><body><main>")
    w('<div class="top"><div><h1>Fire Emblem: Radiant Dawn – Decomp</h1>')
    w(f'<div class="sub">As of {now}{" · last commit " + html.escape(head) if head else ""} · generated by tools/progress_html.py</div></div>'
      '<div><button id="refresh">Refresh</button><div id="msg"></div></div></div>')

    # summary cards
    legend = "".join(
        f'<span class="dot {k}"></span><span title="{html.escape(desc)}">{lab}</span>'
        f'<span class="n">{tc[k]:,} functions · {kb(tb[k])} KB</span><span class="pc">{pct(tb[k], G):.1f}%</span>'
        for k, lab, desc in CLASSES)
    ee = pct(tb["exact"] + tb["equiv"], G)
    w('<div class="grid">')
    w(f'<div class="card"><h3>Game code</h3><div class="big">{pct(tb["exact"], G):.1f}%<small>exact</small></div>'
      f'<div class="sub">{ee:.1f}% exact or equivalent · {kb(G)} KB in {d["game_count"]:,} functions</div>'
      + bar([(k, tb[k]) for k, *_ in CLASSES], G) + f'<div class="legend">{legend}</div></div>')
    L = d["lib_b"]
    w(f'<div class="card"><h3>SDK & libraries</h3><div class="big">{pct(d["lib_okb"], L):.1f}%<small>byte-exact</small></div>'
      f'<div class="sub">{d["lib_ok"]:,} of {d["lib_n"]:,} functions · {kb(d["lib_okb"])} of {kb(L)} KB</div>'
      + bar([("exact", d["lib_okb"])], L)
      + '<div class="legend">' + "".join(
          f'<span class="dot none"></span><span class="mono">{html.escape(n)}</span><span class="n">{s} B</span><span class="pc">open</span>'
          for a, s, n, mod in d["lib_open"][:6]) + "</div></div>")
    allb = G + L
    w(f'<div class="card"><h3>All code</h3><div class="big">{pct(tb["exact"] + d["lib_okb"], allb):.1f}%<small>exact</small></div>'
      f'<div class="sub">{pct(tb["exact"] + tb["equiv"] + d["lib_okb"], allb):.1f}% with equivalent functions · {kb(allb)} KB code (.text)</div>'
      + bar([("exact", tb["exact"] + d["lib_okb"]), ("equiv", tb["equiv"]), ("differs", tb["differs"]), ("none", tb["none"])], allb)
      + "</div>")
    w("</div>")

    # equivalence detail
    eb, es = d["eq_b"], d["eq_sym"]
    eqt = sum(eb.values())
    w("<h2>Equivalent functions in detail</h2>")
    w('<div class="grid"><div class="card"><div class="legend">')
    for k, lab in (("renamed", "renamed – registers renamed only (proven)"), ("regs", "regs – same instructions, other registers"),
                   ("slots", "slots – also other stack slots"), ("sched", "sched – same instructions per block, other order")):
        w(f'<span class="dot equiv"></span><span>{lab}</span><span class="n">{kb(eb[k])} KB</span><span class="pc">{pct(eb[k], eqt):.0f}%</span>')
    w('</div></div><div class="card"><div class="legend">')
    for k, lab, c in (("clean", "symcheck clean", "exact"), ("flagged", "symcheck with flagged blocks (see SCHED_REVIEW.md)", "differs"),
                      ("unchecked", "no symcheck entry", "none")):
        if es[k]:
            w(f'<span class="dot {c}"></span><span>{lab}</span><span class="n">{kb(es[k])} KB</span><span class="pc">{pct(es[k], eqt):.0f}%</span>')
    w("</div></div></div>")

    if d["new_exact"]:
        G_ = d["game"]
        w(f'<p class="note">{len(d["new_exact"])} functions ({kb(sum(G_[n][1] for n in d["new_exact"]))} KB) are already finished files in src/game, '
          f'but not yet in the last tally (build/m2c/matched_names.txt): {", ".join(d["new_exact"][:12])}{" …" if len(d["new_exact"]) > 12 else ""}. '
          "They already count as exact here.</p>")

    # trend
    w("<h2>History</h2>")
    w(trend_svg(hist))

    # regions table
    w("<h2>Game code by region</h2>")
    w('<div class="tablewrap"><table><thead><tr><th>Region</th><th>Addresses</th><th class="r">Fns</th><th class="r">KB</th>'
      '<th>Shares</th><th class="r">exact</th><th class="r">+ equiv.</th><th class="r">open</th></tr></thead><tbody>')
    for rid, r in d["regions"]:
        b, c = r["bytes"], r["count"]
        t = sum(b.values())
        open_n = c["differs"] + c["none"]
        w(f'<tr><td><b>{rid}</b></td><td class="mono">{r["lo"]:08X}–{r["hi"]:08X}</td><td class="r">{sum(c.values())}</td>'
          f'<td class="r">{kb(t)}</td><td>{bar([(k, b[k]) for k, *_ in CLASSES], t, thin=True)}</td>'
          f'<td class="r">{pct(b["exact"], t):.1f}%</td><td class="r">{pct(b["exact"] + b["equiv"], t):.1f}%</td>'
          f'<td class="r">{open_n} · {kb(b["differs"] + b["none"])} KB</td></tr>')
    w("</tbody></table></div>")

    # address map
    w("<h2>Address map</h2>")
    w('<div class="map">')
    for rid, r in d["regions"]:
        lo, hi = r["lo"], r["hi"]
        span = max(hi - lo, 1)
        rects = "".join(
            f'<rect x="{(a - lo) / span * 1000:.2f}" width="{max(s / span * 1000, 0.6):.2f}" height="16" class="{k}" style="fill:var(--{k})"><title>{n} · {s} B · {k}</title></rect>'
            for a, s, k, n in r["funcs"])
        w(f'<div class="maprow"><span class="mono">{rid}</span><svg viewBox="0 0 1000 16" preserveAspectRatio="none">{rects}</svg></div>')
    w('<div class="note">Each row is a region in address order, each function a stripe as wide as its size. '
      'Hover over a stripe to see the function name.</div></div>')

    # biggest open
    ol = d["open_list"]
    w(f"<h2>Largest open functions</h2>")
    w('<div class="tablewrap"><table><thead><tr><th>Function</th><th>Status</th><th class="r">Size</th></tr></thead><tbody>')
    lab = {k: l for k, l, _ in CLASSES}
    for s, n, k in ol[:25]:
        w(f'<tr><td class="mono">{n}</td><td><span class="pill {k}">{lab[k]}</span></td><td class="r">{s:,} B</td></tr>')
    w("</tbody></table></div>")
    if len(ol) > 25:
        w(f'<details><summary>All {len(ol)} open functions</summary><div class="tablewrap"><table><tbody>')
        for s, n, k in ol[25:]:
            w(f'<tr><td class="mono">{n}</td><td>{lab[k]}</td><td class="r">{s} B</td></tr>')
        w("</tbody></table></div></details>")

    # lib modules
    w("<h2>SDK & libraries by module</h2>")
    w('<div class="tablewrap"><table><thead><tr><th>Module</th><th class="r">Fns</th><th class="r">KB</th><th>Share</th><th class="r">verified</th></tr></thead><tbody>')
    for mod, r in d["lib_mods"]:
        w(f'<tr><td>{html.escape(mod)}</td><td class="r">{r["ok"]}/{r["n"]}</td><td class="r">{kb(r["b"])}</td>'
          f'<td>{bar([("exact", r["okb"])], r["b"], thin=True)}</td><td class="r">{pct(r["okb"], r["b"]):.1f}%</td></tr>')
    w("</tbody></table></div>")

    w('<h2>Where the numbers come from</h2><div class="note">'
      "Function sizes from config/RFEE01/symbols.txt (game code below 0x8028BC54, SDK below 0x80360900). "
      "<b>Exact</b>: build/m2c/matched_names.txt plus definitions in src/game outside wip/ and equiv/. "
      "<b>Equivalent</b>: docs/EQUIVALENT.tsv. <b>Draft differs</b>: definition in a wip/ folder. "
      "<b>SDK</b>: lib/verified.json (from tools/lib/check_lib.py --all) and lib/map.json. "
      "The script compiles nothing; it shows the state of the last checks. KB = 1000 bytes.</div>")
    w(JS)
    w("</main></body></html>")
    return "\n".join(out)


def serve(port):
    """Tiny local server (127.0.0.1 only): serves the page, POST /refresh rebuilds it."""
    import http.server
    out = p("build/progress.html")

    class H(http.server.BaseHTTPRequestHandler):
        def log_message(self, *a):
            pass

        def _send(self, code, body=b"", ctype="text/plain"):
            self.send_response(code)
            self.send_header("Content-Type", ctype)
            self.send_header("Content-Length", str(len(body)))
            self.send_header("Cache-Control", "no-store")
            self.end_headers()
            self.wfile.write(body)

        def do_GET(self):
            if self.path.split("?")[0] in ("/", "/progress.html"):
                if not os.path.exists(out):
                    write_page(out)
                self._send(200, open(out, "rb").read(), "text/html; charset=utf-8")
            else:
                self._send(404)

        def do_POST(self):
            if self.path == "/refresh":
                try:
                    write_page(out)
                    self._send(200, b"ok")
                except Exception as e:
                    self._send(500, str(e).encode())
            else:
                self._send(404)

    write_page(out)
    srv = http.server.ThreadingHTTPServer(("127.0.0.1", port), H)
    url = f"http://127.0.0.1:{port}/"
    print(f"Progress page: {url}  (Ctrl+C stops)")
    subprocess.run(["open", url] if sys.platform == "darwin" else ["xdg-open", url])
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        pass


def write_page(path):
    d = collect()
    page = render(d, update_history(d))
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    open(path, "w").write(page)
    return d


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--serve", action="store_true", help="local server with a working Refresh button")
    ap.add_argument("--port", type=int, default=8765)
    ap.add_argument("-o", "--out", default=p("build/progress.html"))
    ap.add_argument("--open", action="store_true", help="open the page in the default browser")
    a = ap.parse_args()
    if a.serve:
        return serve(a.port)
    d = write_page(a.out)
    G = d["game_bytes"]
    tb = d["tot_b"]
    print(f"Game code: exact {pct(tb['exact'], G):.1f}%, equivalent {pct(tb['equiv'], G):.1f}%, "
          f"draft differs {pct(tb['differs'], G):.1f}%, no draft {pct(tb['none'], G):.1f}%  ({G / 1000:.0f} KB)")
    print(f"SDK: {d['lib_ok']}/{d['lib_n']} functions, {pct(d['lib_okb'], d['lib_b']):.1f}% of the bytes")
    print(f"-> {os.path.abspath(a.out)}")
    if a.open:
        subprocess.run(["open", a.out] if sys.platform == "darwin" else ["xdg-open", a.out])


if __name__ == "__main__":
    main()
