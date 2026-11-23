#!/usr/bin/env python3
# sw.py file fn: pair-swap and move search on first P block after fn def; ties explored by keeping best
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,tempfile,shutil,os
from multiprocessing import Pool
f,fn=sys.argv[1],sys.argv[2]
t=open(f).read()
ext=os.path.splitext(f)[1]
bf=sys.argv[3] if len(sys.argv)>3 else fn
d=re.search(r'^\S.*\b%s\(.*\{\s*$'%bf,t,re.M).start()
i=t.index('/*P*/',d)+5;j=t.index('/*E*/',i)
lines=[l for l in t[i:j].split('\n') if l.strip()]
def ev(p):
    tmp=tempfile.mkdtemp(dir=sys.argv[0].rsplit('/',1)[0])
    try:
        s,e=lib.compile_text(t[:i]+'\n'+'\n'.join(p)+'\n'+t[j:],tmp,ext)
        return (lib.score(s,fn) if s else 9999,p)
    finally: shutil.rmtree(tmp,ignore_errors=True)
def nb(L):
    n=len(L)
    for a in range(n):
        for b in range(n):
            if a==b: continue
            M=list(L);x=M.pop(a);M.insert(b,x);yield M
            if a<b:
                M=list(L);M[a],M[b]=M[b],M[a];yield M
if __name__=='__main__':
    best=lines;bs=ev(lines)[0];print('start',bs)
    with Pool(10) as pool:
        for r in range(6):
            res=pool.map(ev,list(nb(best)),chunksize=4)
            res.sort(key=lambda r:r[0])
            if res[0][0]>=bs: break
            bs,best=res[0];print(bs,flush=True)
            if bs==0:break
    open(f,'w').write(t[:i]+'\n'+'\n'.join(best)+'\n'+t[j:])
    print('final',bs)
