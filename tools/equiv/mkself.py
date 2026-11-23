#!/usr/bin/env python3
"""mkself.py PARENT FRAG OUT [--only fn_X,fn_Y] [--keepfrag]
Parent with exported fn_ bodies turned into prototypes + fragment (open fn_ only)."""
import re,sys
import os as _o; ROOT=_o.path.dirname(_o.path.dirname(_o.path.dirname(_o.path.abspath(__file__))))
matched=set(open(ROOT+"/build/m2c/matched_names.txt").read().split())
FN=re.compile(r'\b(fn_[0-9A-F]{8})\s*\(')

def items(src):
    """split into top-level items: list of (text, kind, header) ; kind 'def' for brace-bodied fn def"""
    out=[]; i=0; n=len(src); start=0; depth=0; pdepth=0; bstart=None; inext=[]
    def skip_ws_comment(i): return i
    while i<n:
        ch=src[i]
        if src.startswith('//',i):
            j=src.find('\n',i); i=n if j<0 else j; continue
        if src.startswith('/*',i):
            j=src.find('*/',i+2); i=n if j<0 else j+2; continue
        if ch=='"' or ch=="'":
            j=i+1
            while j<n and src[j]!=ch:
                if src[j]=='\\': j+=1
                j+=1
            i=j+1; continue
        if ch=='#' and src[:i].rstrip(' \t').endswith('\n') or (ch=='#' and i==0):
            # preprocessor line with continuations
            j=i
            while True:
                k=src.find('\n',j)
                if k<0: k=n; break
                if src[k-1]=='\\': j=k+1; continue
                break
            if depth==0:
                out.append((src[start:i],'misc',None))
                out.append((src[i:k+1],'pp',None)); start=k+1
            i=k+1; continue
        if ch=='(': pdepth+=1
        elif ch==')': pdepth-=1
        elif ch=='{':
            if depth==0:
                hdr=src[start:i]
                hs=re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S).strip()
                if re.match(r'extern\s+"C"\s*$',hs) or re.match(r'namespace\b[^=()]*$',hs):
                    out.append((src[start:i+1],'open',None)); start=i+1; inext.append(1); i+=1; continue
                bstart=i
            depth+=1
        elif ch=='}':
            if depth==0 and inext:
                out.append((src[start:i],'misc',None))
                out.append((src[i:i+1],'close',None)); start=i+1; inext.pop(); i+=1; continue
            depth-=1
            if depth==0:
                hdr=src[start:bstart]
                hs=re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S).strip()
                if hs.endswith(')') or re.search(r'\)\s*const$',hs):
                    if '=' not in hs or 'operator' in hs:
                        out.append((src[start:i+1],'def',hdr)); start=i+1; i+=1; continue
                # struct / initializer: continue to ';'
        elif ch==';' and depth==0 and pdepth==0:
            out.append((src[start:i+1],'misc',None)); start=i+1
        i+=1
    if src[start:].strip(): out.append((src[start:],'misc',None))
    return out

def exported(hdr):
    hs=re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S)
    m=FN.search(hs)
    if not m: return None
    # name must be the declarator (first paren group at top level)
    pre=hs[:m.start()]
    if '(' in pre: return None
    if re.search(r'\b(static|inline)\b',pre): return None
    return m.group(1)

def main():
    a=sys.argv[1:]
    only=None; keep=False; inl=set()
    if '--inline' in a:
        k=a.index('--inline'); inl=set(a[k+1].split(',')); del a[k:k+2]
    if '--only' in a:
        k=a.index('--only'); only=set(a[k+1].split(',')); del a[k:k+2]
    parent,frag,out=a[:3]
    res=[]
    psrc=open(parent).read()
    psrc=re.sub(r'(?m)^[A-Z_0-9]+\((?:[^\n]|\\\n)*fn_[0-9A-F]{8}(?:[^\n]|\\\n)*\)[ \t]*;?[ \t]*$','',psrc)
    for text,kind,hdr in items(psrc):
        if kind=='def':
            nm=exported(hdr)
            if nm and nm in inl:
                res.append('\n/* Local inline copy of %s (matched elsewhere): the original inlines it here. */\nstatic inline '+re.sub(r'\b'+nm+r'\b',nm+'_i',text.lstrip(),count=0)%() if False else '\n/* Local inline copy of '+nm+' (matched elsewhere): the original inlines it here. */\nstatic inline '+re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S).strip().replace(nm,nm+'_i')+text[len(hdr):]+'\n')
                continue
            if nm:
                # leading comments go, prototype stays
                h=re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S).strip()
                res.append('\n'+h+';\n'); continue
        res.append(text)
    cpp=out.endswith('.cpp')
    res.append('\n\n/* ---- from %s ---- */\n'%frag.split('src/game/')[-1])
    if cpp: res.append('extern "C" {\n')
    opens=0
    fitems=items(open(frag).read()) if frag!='-' else []
    for text,kind,hdr in fitems:
        if kind=='def':
            nm=exported(hdr)
            if nm and nm in inl:
                res.append('\n/* Local inline copy of '+nm+': the original inlines it here. */\nstatic inline '+re.sub(r'/\*.*?\*/|//[^\n]*','',hdr,flags=re.S).strip().replace(nm,nm+'_i')+text[len(hdr):]+'\n')
                continue
            if nm and (nm in matched or (only and nm not in only)):
                continue
        res.append(text)
    if cpp: res.append('\n}\n')
    s=''.join(res)
    for nm in inl:
        s=re.sub(r'\b'+nm+r'\b(?!_i)',nm+'_i',s)
        s=re.sub(r'(?m)^(?!static)[A-Za-z_][^\n{;=]*\b'+nm+r'_i\s*\([^;{]*\)\s*;[ \t]*\n','',s)
    open(out,'w').write(s)
main()
