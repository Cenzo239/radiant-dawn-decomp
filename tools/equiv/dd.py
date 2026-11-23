#!/usr/bin/env python3
"""dd.py FILE fn REGION [-u] : register-masked diff ours vs orig. -u: full unmasked side by side"""
import sys,os,re,subprocess,glob,shlex,difflib,tempfile
import os as _o; ROOT=_o.path.dirname(_o.path.dirname(_o.path.dirname(_o.path.abspath(__file__))))
os.chdir(ROOT)
sys.path.insert(0,ROOT+"/tools")
import check_func as c
def parse(txt):
    out=[]
    for l in txt.splitlines():
        m=re.match(r"\s*/\*.*?\*/\s*(.*)",l)
        n=(m.group(1) if m else l).strip()
        if not n or n.startswith('.') : continue
        n=re.sub(r"\s+"," ",n)
        n=re.sub(r"\.L_[0-9A-F]+","L",n)
        n=re.sub(r'"?@\d+"?','@K',n)
        n=re.sub(r'"?@stringBase0"?','@S',n)
        n=re.sub(r'(lbl_804C[C-F][0-9A-F]+|lbl_804D[0-9A-F]+)(?=@sda21)','@K',n)
        n=re.sub(r'jumptable_[0-9A-F]+','@K',n)
        out.append(n)
    return out
def mask(l):
    l=re.sub(r'\b(r|f)([0-9]|[12][0-9]|3[01])\b',lambda m:m.group(1).upper(),l)
    l=re.sub(r'\bcr[0-7]\b','CR',l)
    return l
def orig(fn):
    for f in glob.glob(ROOT+"/build/RFEE01/asm/auto_*.s")+glob.glob(ROOT+"/build/RFEE01/asm/tu/**/*.s",recursive=True):
        t=open(f).read()
        m=re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b"%(fn,fn),t,re.S)
        if m: return parse(m.group(1))
src,fn,R=sys.argv[1:4]
tmp=tempfile.mkdtemp(dir=ROOT+"/build/tmp")
obj=tmp+"/o.o"
r=subprocess.run([c.WIBO,ROOT+"/build/compilers/GC/3.0a5.2/mwcceppc.exe",*shlex.split(c.DEFAULT_FLAGS),"-i",f"src/game/{R}","-i",f"src/game/{R}/wip","-c",src,"-o",obj],cwd=ROOT,capture_output=True,text=True,stdin=subprocess.DEVNULL)
if not os.path.exists(obj): print(r.stdout[-1500:]); sys.exit(1)
subprocess.run([ROOT+"/build/tools/dtk","elf","disasm",obj,tmp+"/o.s"],capture_output=True,text=True,stdin=subprocess.DEVNULL)
s=open(tmp+"/o.s").read()
m=re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b"%(fn,fn),s,re.S)
a=parse(m.group(1)); b=orig(fn)
import shutil; shutil.rmtree(tmp)
print("ours",len(a),"orig",len(b))
if '-u' in sys.argv:
    for i in range(max(len(a),len(b))):
        x=a[i] if i<len(a) else ''; y=b[i] if i<len(b) else ''
        print("%3d %-40s %-40s %s"%(i,x,y,'' if x==y else ('*' if mask(x)==mask(y) else '#####')))
else:
    ma=[mask(x) for x in a]; mb=[mask(x) for x in b]
    sm=difflib.SequenceMatcher(None,ma,mb,autojunk=False)
    for tag,i1,i2,j1,j2 in sm.get_opcodes():
        if tag=='equal': continue
        print(f"@@ ours {i1}..{i2}  orig {j1}..{j2}")
        for k in range(max(0,i1-2),i1): print("     ",a[k])
        for k in range(i1,i2): print("  -  ",a[k])
        for k in range(j1,j2): print("  +  ",b[k])
