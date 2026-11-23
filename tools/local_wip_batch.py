#!/usr/bin/env python3
"""Conservative local WIP batch: scan sources, try up to 16 candidates with four workers.

Run from the repository root: python3 tools/local_wip_batch.py
Existing function-name references are conservatively excluded to avoid duplicate
matches. This also excludes some genuinely unmatched functions. Search scoring
uses the existing wip_search checker; recheck any result with --strict-references
before counting it as fully reference-verified. Results: build/round15_local_batch.json.
"""
from pathlib import Path
import sys,re,concurrent.futures,json,os
sys.path.insert(0,'tools');import wip_search as ws
known=set()
for p in Path('src/game').rglob('*'):
 if p.suffix in ('.c','.cpp') and 'wip' not in p.parts:known.update(re.findall(r'\bfn_[0-9A-F]{8}\b',p.read_text()))
items=[]
for p in Path('src/game').glob('*/wip/*.cpp'):
 items.append((str(p.resolve()),str(p.parent.parent.resolve()),12,known))
found={}
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
 for results in pool.map(ws.scan,items):
  for p,n,w in results:
   if n not in found or w<found[n][1]:found[n]=(p,w)
todo=sorted(found.items(),key=lambda x:x[1][1])[:16]
print('Scanned',len(items),'WIP files;',len(todo),'candidates',flush=True)
results=[]
work=[(p,n,str(Path(p).parent.parent),250,Path(p).suffix) for n,(p,w) in todo]
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
 for r in pool.map(ws.run_one,work):results.append(r);print(r,flush=True)
Path('build/round15_local_batch.json').write_text(json.dumps(results,indent=2))
