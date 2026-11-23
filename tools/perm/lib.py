import sys,os,re,subprocess,tempfile,shlex,glob
import os as _os
ROOT=_os.path.dirname(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))))
FLAGS=shlex.split('-nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i src')
_cache={}
def origfn(name):
    if name in _cache: return _cache[name]
    for f in glob.glob(ROOT+"/build/RFEE01/asm/auto_*_text.s"):
        t=open(f).read()
        m=re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b"%(name,name),t,re.S)
        if m:
            _cache[name]=parse(m.group(1)); return _cache[name]
    return None
def parse(txt):
    out=[]
    for l in txt.splitlines():
        m=re.match(r"\s*/\*.*?\*/\s*(.*)",l)
        n=(m.group(1) if m else l).strip()
        if not n or n.startswith('.') : continue
        n=re.sub(r"\s+"," ",n)
        n=re.sub(r"\.L_[0-9A-F]+","L",n)
        n=re.sub(r'"@\d+"','@K',n)
        n=re.sub(r'lbl_804C[C-F][0-9A-F]+|lbl_804D[0-9A-F]+','@K',n)
        out.append(n)
    return out
def compile_text(text,tmp=None,ext=".cpp"):
    tmp=tmp or tempfile.mkdtemp(dir=ROOT+"/build/tmp")
    src=tmp+"/t"+ext; open(src,"w").write(text)
    obj=tmp+"/o.o"
    if os.path.exists(obj): os.remove(obj)
    r=subprocess.run([ROOT+"/tools/wibo_guard",ROOT+"/build/compilers/GC/3.0a5.2/mwcceppc.exe",*FLAGS,'-i','src/game/rB_8002E1C4','-i','src/game/rC2_8005259C',"-c",src,"-o",obj],cwd=ROOT,capture_output=True,text=True,stdin=subprocess.DEVNULL)
    if not os.path.exists(obj): return None,r.stdout+r.stderr
    subprocess.run([ROOT+"/build/tools/dtk","elf","disasm",obj,tmp+"/o.s"],capture_output=True,text=True,stdin=subprocess.DEVNULL)
    return open(tmp+"/o.s").read(),None
def fn_of(s,fn):
    m=re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b"%(fn,fn),s,re.S)
    return parse(m.group(1)) if m else None
def score(s,fn):
    a=fn_of(s,fn); b=origfn(fn)
    if a is None: return 9999
    d=abs(len(a)-len(b))*2
    for x,y in zip(a,b):
        if x!=y: d+=1
    return d
