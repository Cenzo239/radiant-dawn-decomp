#!/usr/bin/env python3
# grid2.py file fn spec.py : as grid, prints rows-order line info: regs of the row adds
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,tempfile,shutil,itertools,re
from multiprocessing import Pool
f,fn,vf=sys.argv[1:4]
t=open(f).read()
ns={};exec(open(vf).read(),ns)
G=ns['groups'];pat=ns['pat']
for o,_ in G: assert o in t,o
def ev(c):
    x=t
    for (o,_),v in zip(G,c): x=x.replace(o,v)
    tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp/rM13')
    s,e=lib.compile_text(x,tmp,'.cpp')
    sc=lib.score(s,fn) if s else 9999
    info=''
    if s:
        L=lib.fn_of(s,fn)
        info=pat(L)
    shutil.rmtree(tmp,ignore_errors=True)
    return sc,info,c
if __name__=='__main__':
    cs=list(itertools.product(*[a for _,a in G]));print(len(cs))
    with Pool(14) as p: r=p.map(ev,cs,chunksize=2)
    r.sort(key=lambda x:(not x[1],x[0]))
    for sc,i,v in r[:int(sys.argv[4]) if len(sys.argv)>4 else 8]: print(sc,i[:400],[str(q)[-45:] for q in v])
