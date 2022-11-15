# Usage: python3 join.py src.bed
import sys

def process(block):
  top = max([b[2] for b in block]) + 0.1
  w_center = sum([(top - b[2]) * b[1] for b in block]) / sum([(top - b[2]) for b in block])
  print(block[0][0] + "\t" + str(int(w_center)-256) + "\t" + str(int(w_center)+256))

block = []
with open(sys.argv[1], 'r') as src:
  for lx in src.readlines():
    obj = lx.replace('\n', '').split('\t')
    if len(obj) != 4: continue
    ch, l, r, sax = obj
    if float(sax) > 7.5: continue
    c = int((int(l) + int(r)) / 2)
    if len(block) > 0:
      if block[-1][0] != ch or (c - block[-1][1]) > 512:
        process(block)
        block = []
    block.append([ch.split('/')[-1], c, float(sax)])

if len(block) > 0:
  process(block)
