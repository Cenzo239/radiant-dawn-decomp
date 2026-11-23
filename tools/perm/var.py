#!/usr/bin/env python3
# var.py file fn OLD-file VARS-file: try alternatives from a python list of (old,new) tuples
import os,sys;sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
import lib,tempfile,shutil
from multiprocessing import Pool
f,fn,vf=sys.argv[1:4]
t=open(f).read()
ns={};exec(open(vf).read(),ns)
old=ns['old'];vs=ns['vs']
assert old in t
def ev(v):
    tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp/rR12')
    s,e=lib.compile_text(t.replace(old,v),tmp,'.cpp')
    sc=lib.score(s,fn) if s else 9999
    shutil.rmtree(tmp,ignore_errors=True)
    return sc,v
if __name__=='__main__':
    with Pool(8) as p: r=p.map(ev,vs)
    r.sort(key=lambda x:x[0])
    for sc,v in r[:6]: print(sc,repr(v))
