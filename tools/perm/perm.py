# perm.py file.c funcname: tries every order of the lines between /*PERM*/ and /*ENDPERM*/
# (usually local declarations) until check_func.py reports funcname as OK.
import sys, itertools, subprocess, re, os, tempfile
f, fn = sys.argv[1], sys.argv[2]
src = open(f).read()
start = src.index('/*PERM*/'); end = src.index('/*ENDPERM*/')
block = src[start+len('/*PERM*/'):end]
lines = [l for l in block.split('\n') if l.strip()]
try_path = os.path.join(tempfile.mkdtemp(), 'perm_try' + os.path.splitext(f)[1])
for p in itertools.permutations(lines):
    t = src[:start] + '\n' + '\n'.join(p) + '\n' + src[end+len('/*ENDPERM*/'):]
    open(try_path,'w').write(t)
    r = subprocess.run(['python3','-I','tools/check_func.py',try_path],capture_output=True,text=True)
    m = [l for l in r.stdout.split('\n') if fn in l]
    print([x.strip() for x in p], m)
    if any('OK' in x for x in m):
        print("FOUND"); break
