#!/usr/bin/env python3
import sys;sys.path.insert(0,sys.argv[0].rsplit('/',1)[0])
import lib,re,tempfile,shutil,os,itertools
from multiprocessing import Pool
f,fn=sys.argv[1],sys.argv[2]
t=open(f).read();ext=os.path.splitext(f)[1]
d=t.index('void '+fn) if 'void '+fn in t else re.search(r'\b%s\('%fn,t).start()
i=t.index('/*P*/',d)+5;j=t.index('/*E*/',i)
L=[l for l in t[i:j].split('\n') if l.strip()]
def ev(p):
    tmp=tempfile.mkdtemp(dir=sys.argv[0].rsplit('/',1)[0])
    try:
        s,e=lib.compile_text(t[:i]+'\n'+'\n'.join(p)+'\n'+t[j:],tmp,ext)
        return (lib.score(s,fn) if s else 9999,p)
    finally: shutil.rmtree(tmp,ignore_errors=True)
if __name__=='__main__':
    with Pool(10) as pool: r=pool.map(ev,list(itertools.permutations(L)),chunksize=4)
    r.sort(key=lambda x:x[0]);print(r[0][0]);open(f,'w').write(t[:i]+'\n'+'\n'.join(r[0][1])+'\n'+t[j:])
