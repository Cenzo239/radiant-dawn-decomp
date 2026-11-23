#!/usr/bin/env python3
"""Safe re-placement of lib functions (keeps hand-set map entries).

Usage: tools/lib/saferemap.py [KEY ...]     (all sources when no key is given)
For each source, functions that are not verified yet (lib/verified.json) are moved to an
unverified DOL function of the same size whose reloc-masked bytes are identical (unique hit
within +-0x4000 of the source's current entries). The change is kept only if check_lib reports
more OK functions for that source afterwards. Run check_lib.py --all first so verified.json is fresh.
Tiny functions (getters, stubs) can match by accident: check names of KEEP lines against neighbours.
"""
import json,os,sys,subprocess,fcntl
R=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0]=[R+'/tools/lib',R+'/tools']
os.chdir(R)
import check_func as cf
from libscan import apply
import remap
MP=R+'/lib/map.json'
MAN=json.load(open(R+'/lib/manifest.json'))
syms=cf.load_symbols(); read=cf.dol_reader()
addr_size={a:s for n,(a,s) in syms.items() if 0x8028BC54<=a<0x80360900}
ver=json.load(open(R+'/lib/verified.json'))
okaddr=set(a for d in ver.values() for a in d.values())
def okcount(key):
    out=subprocess.run([sys.executable,'tools/lib/check_lib.py',key,'-v'],capture_output=True,text=True).stdout
    return sum(1 for l in out.splitlines() if l.startswith('  OK   '))
keys=sys.argv[1:] or sorted(json.load(open(MP))['sources'])
for key in keys:
    M=json.load(open(MP)); ent=M['sources'][key]
    if key not in MAN: continue
    obj=remap.compile_obj(key,MAN[key])
    if obj is None: continue
    secs,esyms,relocs=cf.parse_elf(obj)
    addrs=[f[0] for f in ent['functions'].values()]
    if not addrs: continue
    lo,hi=min(addrs)-0x4000,max(addrs)+0x4000
    cands=sorted(a for a in addr_size if lo<=a<=hi and a not in okaddr)
    vnames=set(ver.get(key,{}))
    changes={}
    used=set()
    for s in esyms:
        if not(s['type']==2 and s['shndx'] and s['shndx']<0xFF00 and s['size']>=8 and secs[s['shndx']]['name'].startswith('.text')): continue
        if s['name'] in vnames: continue
        fb=bytes(secs[s['shndx']]['data'][s['value']:s['value']+s['size']])
        fm={}
        for off,rtype,*_ in relocs.get(s['shndx'],[]):
            if s['value']<=off<s['value']+s['size']:
                wo=off-2 if rtype in (4,5,6) else off&~3
                fm[wo-s['value']]=fm.get(wo-s['value'],0)|cf.RELOC_MASK.get(rtype,0xFFFFFFFF)
        mb=apply(fb,fm)
        hits=[a for a in cands if addr_size[a]==len(fb) and a not in used and apply(read(a,len(fb)),fm)==mb]
        if len(hits)==1:
            old=ent['functions'].get(s['name'])
            if old and old[0]==hits[0]: continue
            changes[s['name']]=[hits[0],len(fb),'diff']; used.add(hits[0])
    if not changes: continue
    before=okcount(key)
    with open(MP+'.lock','w') as lk:
        fcntl.flock(lk,fcntl.LOCK_EX)
        M=json.load(open(MP)); saved=json.loads(json.dumps(M['sources'][key]))
        M['sources'][key]['functions'].update(changes); json.dump(M,open(MP,'w'),indent=0)
    after=okcount(key)
    if after<=before:
        with open(MP+'.lock','w') as lk:
            fcntl.flock(lk,fcntl.LOCK_EX)
            M=json.load(open(MP)); M['sources'][key]=saved; json.dump(M,open(MP,'w'),indent=0)
        print('REVERT',key,before,after,list(changes)[:5])
    else:
        print('KEEP',key,before,'->',after,{k:hex(v[0]) for k,v in changes.items()})
