"""ps.py FILE FN [iters] [-j N]: random/hill search over orderings of lines tagged /*P*/ (declarations) to make
masked (register-free) instruction sequence equal the original. Extra include dirs from region in path/contents.
Score = positional mismatches of register-masked instructions (incl. branch targets). Writes best to FILE.best"""
import sys,os,re,subprocess,shlex,glob,tempfile,random,struct,shutil
from multiprocessing import Pool
import os as _o; ROOT=_o.path.dirname(_o.path.dirname(_o.path.dirname(_o.path.abspath(__file__))))
sys.path.insert(0,ROOT+'/tools')
os.chdir(ROOT)
import check_regs as cr, check_func as c
FLAGS=shlex.split(c.DEFAULT_FLAGS)
def inc_for(src,text):
    m=re.search(r'(r[A-Z0-9]+_[0-9A-F]{8})',text+src)
    return ['-i','src/game/'+m.group(1),'-i','src/game/'+m.group(1)+'/wip'] if m else []
_orig={}
def orig(fn):
    if fn not in _orig:
        syms=c.load_symbols(); addr,size=syms[fn]; _orig[fn]=bytes(c.dol_reader()(addr,size))
    return _orig[fn]
def score_text(args):
    text,ext,fn,inc=args
    tmp=tempfile.mkdtemp(dir=ROOT+'/build/tmp')
    try:
        src=tmp+'/t'+ext; open(src,'w').write(text); obj=tmp+'/o.o'
        r=subprocess.run([c.WIBO,ROOT+'/build/compilers/GC/3.0a5.2/mwcceppc.exe',*FLAGS,*inc,'-c',src,'-o',obj],capture_output=True,text=True,stdin=subprocess.DEVNULL)
        if not os.path.exists(obj): return 10**9
        secs,syms,relocs=c.parse_elf(obj)
        for s in syms:
            if s['name']==fn and s['type']==2:
                sec=secs[s['shndx']]
                ours=bytearray(sec['data'][s['value']:s['value']+s['size']]); theirs=bytearray(orig(fn))
                for off,rtype,_t,_a,_s in relocs.get(s['shndx'],[]):
                    rel=off-s['value']
                    if 0<=rel<len(ours):
                        wo=rel-2 if rtype in (4,5,6) else rel&~3
                        mask=c.RELOC_MASK.get(rtype,0xFFFFFFFF)
                        for buf in (ours,theirs):
                            if wo+4<=len(buf):
                                w,=struct.unpack('>I',buf[wo:wo+4]); struct.pack_into('>I',buf,wo,w&~mask)
                d=abs(len(ours)-len(theirs))*3; ex=0
                for i in range(min(len(ours),len(theirs))//4):
                    a,=struct.unpack('>I',ours[i*4:i*4+4]); b,=struct.unpack('>I',theirs[i*4:i*4+4])
                    if cr.split(a)[0]!=cr.split(b)[0]: d+=10
                    elif cr.zero_base(a) and (((a>>16)&31)==0)!=(((b>>16)&31)==0): d+=10
                    elif a!=b: ex+=1
                return d*1000+ex
        return 10**9
    finally: shutil.rmtree(tmp,ignore_errors=True)
def main():
    f=sys.argv[1]; fn=sys.argv[2]; iters=int(sys.argv[3]) if len(sys.argv)>3 else 200
    text=open(f).read(); ext=os.path.splitext(f)[1]; inc=inc_for(f,text)
    lines=text.split('\n'); idx=[i for i,l in enumerate(lines) if '/*P*/' in l and l.strip()!='/*P*/']
    inb=False
    for i,l in enumerate(lines):
        if l.strip()=='/*P*/': inb=True; continue
        if l.strip().startswith('/*E*/'): inb=False; continue
        if inb and l.strip(): idx.append(i)
    idx=sorted(set(idx))
    def build(order):
        L=list(lines)
        for pos,src in zip(idx,order): L[pos]=lines[src]
        return '\n'.join(L)
    cur=list(idx); best=score_text((build(cur),ext,fn,inc)); print('start',best,len(idx),'lines',flush=True)
    rnd=random.Random(int(os.environ.get("SEED","1")))
    with Pool(6) as pool:
        it=0
        while it<iters and best>=1000:
            cands=[]
            for _ in range(12):
                o=list(cur)
                k=rnd.choice([1,1,2,3])
                for _ in range(k):
                    a,b=rnd.sample(range(len(o)),2)
                    if rnd.random()<0.5: o[a],o[b]=o[b],o[a]
                    else: x=o.pop(a); o.insert(b,x)
                cands.append(o)
            res=pool.map(score_text,[(build(o),ext,fn,inc) for o in cands])
            it+=len(cands)
            m=min(res)
            if m<=best:
                if m<best: print(it,'->',m,flush=True)
                best=m; cur=cands[res.index(m)]
                open(f+'.best','w').write(build(cur))
    print('final',best)
if __name__=='__main__': main()
