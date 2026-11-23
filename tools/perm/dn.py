#!/usr/bin/env python3
# dd.py file fn [ctx]: side-by-side unified diff of compiled vs original
import sys,os,difflib,tempfile,shutil
sys.path.insert(0,os.path.dirname(os.path.abspath(sys.argv[0])))
sys.path.insert(0,os.path.dirname(os.path.abspath(sys.argv[0]))+'/perm')
import lib
f,fn=sys.argv[1],sys.argv[2]
tmp=tempfile.mkdtemp(dir=lib.ROOT+'/build/tmp')
s,e=lib.compile_text(open(f).read(),tmp,os.path.splitext(f)[1])
shutil.rmtree(tmp,ignore_errors=True)
if not s: print(e);sys.exit(1)
a=lib.fn_of(s,fn);b=lib.origfn(fn)
import re
a=[re.sub(r'\br\d+\b','r',re.sub(r'@K|lbl_\w+|@\w+','S',x)) for x in a]
b=[re.sub(r'\br\d+\b','r',re.sub(r'@K|lbl_\w+|@\w+','S',x)) for x in b]
import re
def norm(l): return re.sub(r'lbl_[0-9A-F]+|@\w+|fn_[0-9A-F]+\+?0?x?0?','SYM',l) if 0 else l
print(len(a),len(b))
for l in difflib.unified_diff(a,b,'ours','want',lineterm='',n=int(sys.argv[3]) if len(sys.argv)>3 else 1): print(l)
