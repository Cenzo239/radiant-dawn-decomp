#!/usr/bin/env python3
# rr.py file fn tries: random pair of moves + greedy, bounded
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,tempfile,shutil,os,random
from multiprocessing import Pool
f,fn,N=sys.argv[1],sys.argv[2],int(sys.argv[3])
t=open(f).read();ext=os.path.splitext(f)[1]
d=re.search(r'^\S.*\b%s\(.*\{\s*$'%fn,t,re.M).start()
i=t.index('/*P*/',d)+5;j=t.index('/*E*/',i)
L=[l for l in t[i:j].split('\n') if l.strip()]
def ev(p):
    tmp=tempfile.mkdtemp(dir=sys.argv[0].rsplit('/',1)[0])
    try:
        s,e=lib.compile_text(t[:i]+'\n'+'\n'.join(p)+'\n'+t[j:],tmp,ext)
        return (lib.score(s,fn) if s else 9999,p)
    finally: shutil.rmtree(tmp,ignore_errors=True)
if __name__=='__main__':
    best=L;bs=ev(L)[0];print('start',bs)
    with Pool(10) as pool:
        for r in range(N):
            c=[]
            for _ in range(200):
                M=list(best)
                for _ in range(random.choice([2,3,4])):
                    x=M.pop(random.randrange(len(M)));M.insert(random.randrange(len(M)+1),x)
                c.append(M)
            res=pool.map(ev,c,chunksize=4);res.sort(key=lambda x:x[0])
            if res[0][0]<bs: bs,best=res[0];print(bs,flush=True)
            if bs==0:break
    open(f,'w').write(t[:i]+'\n'+'\n'.join(best)+'\n'+t[j:]);print('final',bs)
