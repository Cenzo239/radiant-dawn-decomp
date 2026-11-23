#!/usr/bin/env python3
# tys.py file fn: greedy type search over /*P*/ lines (int<->s16)
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,tempfile,shutil
from multiprocessing import Pool
f,fn=sys.argv[1:3]
t=open(f).read()
EXT='.c' if f.endswith('.c') else '.cpp'
i=t.index('/*P*/')+5;j=t.index('/*E*/')
L=t[i:j].split('\n')
def ev(M):
    tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp')
    s,e=lib.compile_text(t[:i]+'\n'.join(M)+t[j:],tmp,EXT)
    sc=lib.score(s,fn) if s else 9999
    shutil.rmtree(tmp,ignore_errors=True)
    return sc,M
if __name__=='__main__':
    best=L;bs=ev(L)[0];print('start',bs)
    with Pool(10) as p:
        for _ in range(4):
            c=[]
            for k,l in enumerate(best):
                m=re.match(r'\s*(int|s16|u16|u32|u8|s8) (\w+);',l)
                if not m: continue
                for ty in ('int','s16','u16','u32'):
                    if ty==m.group(1): continue
                    M=list(best);M[k]='    %s %s;'%(ty,m.group(2));c.append(M)
            r=p.map(ev,c);r.sort(key=lambda x:x[0])
            if r[0][0]>=bs:break
            bs,best=r[0];print(bs,flush=True)
    open(f,'w').write(t[:i]+'\n'.join(best)+t[j:]);print('final',bs)
