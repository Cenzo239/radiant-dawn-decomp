#!/usr/bin/env python3
# hill.py template fn iters : permutes lines inside /*P*/ ... /*E*/ blocks; hill climbs in parallel
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,random,os,tempfile,shutil
from multiprocessing import Pool
tpl=open(sys.argv[1]).read(); fn=sys.argv[2]; iters=int(sys.argv[3])
EXT=os.path.splitext(sys.argv[1])[1]
parts=re.split(r"(/\*P\*/.*?/\*E\*/)",tpl,flags=re.S)
blocks=[i for i,p in enumerate(parts) if p.startswith("/*P*/")]
state={i:[l for l in parts[i][5:-5].split("\n") if l.strip()] for i in blocks}
def render(st):
    ps=list(parts)
    for i in blocks: ps[i]="\n".join(st[i])+"\n"
    return "".join(ps)
def ev(st):
    tmp=tempfile.mkdtemp(dir=sys.argv[0].rsplit('/',1)[0])
    try:
        s,e=lib.compile_text(render(st),tmp,EXT)
        return (lib.score(s,fn) if s else 9999, st)
    finally: shutil.rmtree(tmp,ignore_errors=True)
def mut(st):
    st={k:list(v) for k,v in st.items()}
    for _ in range(random.choice([1,1,2,3])):
        i=random.choice(blocks); L=st[i]
        if len(L)<2: continue
        a=random.randrange(len(L)); x=L.pop(a); L.insert(random.randrange(len(L)+1),x)
    return st
if __name__=="__main__":
    best=state; bs=ev(best)[0]; print("start",bs)
    with Pool(10) as pool:
        for it in range(iters):
            res=pool.map(ev,[mut(best) for _ in range(20)])
            res.sort(key=lambda r:r[0])
            if res[0][0]<=bs:
                if res[0][0]<bs: print(it,res[0][0],flush=True)
                bs,best=res[0]
                open(sys.argv[1]+".best","w").write(render(best))
            if bs==0: print("MATCH"); break
    print("final",bs)
