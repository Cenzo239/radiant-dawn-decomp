#!/usr/bin/env python3
# co.py file fn rounds [popsize]: random multi-move across ALL /*P*/../*E*/ blocks in file; accepts ties
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,tempfile,shutil,os,random
from multiprocessing import Pool
f,fn,N=sys.argv[1],sys.argv[2],int(sys.argv[3]);P=int(sys.argv[4]) if len(sys.argv)>4 else 280
t=open(f).read()
parts=re.split(r'(/\*P\*/.*?/\*E\*/)',t,flags=re.S)
idx=[i for i in range(len(parts)) if parts[i].startswith('/*P*/')]
B=[[l for l in parts[i][5:-5].split('\n') if l.strip()] for i in idx]
def build(bs):
    q=list(parts)
    for i,b in zip(idx,bs): q[i]='/*P*/\n'+'\n'.join(b)+'\n/*E*/'
    return ''.join(q)
def ev(bs):
    tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp/rM13')
    try:
        s,e=lib.compile_text(build(bs),tmp,'.cpp')
        return (lib.score(s,fn) if s else 9999,bs)
    finally: shutil.rmtree(tmp,ignore_errors=True)
if __name__=='__main__':
    best=B;bs=ev(B)[0];print('start',bs,flush=True)
    with Pool(14) as pool:
        for r in range(N):
            c=[]
            for _ in range(P):
                M=[list(b) for b in best]
                for _ in range(random.choice([1,1,2,2,3,4])):
                    b=random.choice(M)
                    if len(b)<2: continue
                    x=b.pop(random.randrange(len(b)));b.insert(random.randrange(len(b)+1),x)
                c.append(M)
            res=pool.map(ev,c,chunksize=4);res.sort(key=lambda x:x[0])
            if res[0][0]<=bs:
                if res[0][0]<bs: print(res[0][0],flush=True)
                bs,best=res[0]
            if bs==0:break
    open(f,'w').write(build(best));print('final',bs)
