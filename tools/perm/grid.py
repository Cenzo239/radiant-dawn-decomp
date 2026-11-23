#!/usr/bin/env python3
# grid.py file fn spec.py : spec defines groups=[(old,[alts...]),...]; tries the product
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,tempfile,shutil,itertools
from multiprocessing import Pool
f,fn,vf=sys.argv[1:4]
t=open(f).read()
EXT='.c' if f.endswith('.c') else '.cpp'
ns={};exec(open(vf).read(),ns)
G=ns['groups']
for o,_ in G: assert o in t,o
def ev(c):
    x=t
    for (o,_),v in zip(G,c): x=x.replace(o,v)
    tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp')
    s,e=lib.compile_text(x,tmp,EXT)
    sc=lib.score(s,fn) if s else 9999
    shutil.rmtree(tmp,ignore_errors=True)
    return sc,c
if __name__=='__main__':
    cs=list(itertools.product(*[a for _,a in G]));print(len(cs))
    with Pool(10) as p: r=p.map(ev,cs,chunksize=2)
    r.sort(key=lambda x:x[0])
    for sc,v in r[:int(sys.argv[4]) if len(sys.argv)>4 else 6]: print(sc,[str(q)[:70] for q in v])
    best=r[0][1];x=t
    for (o,_),v in zip(G,best): x=x.replace(o,v)
    if len(sys.argv)>5: open(f,'w').write(x)
