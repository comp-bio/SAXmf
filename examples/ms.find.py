# -*- coding: utf-8 -*-
import sys, gzip
import numpy as np
import warnings

warnings.filterwarnings("ignore")

window_size = 32
scale = 8
motif = {
    'DEL_L': {'m': [19,19,19,19,19,19,19,19,19,18,18,17,16,15,14,13,11,9,7,7,5,4,3,3,3,3,3,3,3,3,3,3], 'offset': 14.440743843189814}
}


def echo(text, color='37'):
    sys.stdout.write("\033[1;%sm%s\033[m" % (color, text))


def usage():
    echo('Usage:    python3 %s [source bed.gz] [result] [SV code: DEL_{L,R} or DUP_{L,R}] [threshold, optional]\n' % sys.argv[0])
    echo('Example:  python3 %s HG002.per-base.bed.gz HG001.DEL_L.bed.gz DEL_L 5\n\n' % sys.argv[0])
    sys.exit(1)


def read(src):
    with gzip.open(src, 'rt') as f:
        for line in f:
            obj = line.strip().split('\t')
            if len(obj) < 4: continue
            yield [obj[0]] + list(map(int, obj[1:4]))
    yield None


def slide(src, window=512, offset=32):
    last_chr, stack_start, stack, bed = ('-', 0, [], read(src))
    while True:
        while len(stack) < window:
            obj = next(bed)
            if obj == None: return None
            cur_chr, start, stop, v = obj
            if cur_chr != last_chr: 
                last_chr, stack_start, stack = (cur_chr, 0, [])
            stack.extend([0 for i in range(start - stack_start - len(stack))])
            stack.extend([v for i in range(start, stop)])
        res, stack, stack_start = (stack[0:window], stack[offset:], stack_start + offset)
        yield last_chr, stack_start - offset, np.array(res)

    
if len(sys.argv) < 4: usage()

from tslearn.piecewise import SymbolicAggregateApproximation
from tslearn.preprocessing import TimeSeriesScalerMeanVariance

sax = SymbolicAggregateApproximation(
    n_segments=64, 
    alphabet_size_avg=24)

src, dst, name = sys.argv[1:4]
threshold = 5 if len(sys.argv) < 5 else sys.argv[4]

if name not in motif:
    names = ", ".join([name for name in motif])
    echo(f"Error:    Code '{name}' not found.  Available: {names}\n", 31)
    usage()
    

offset = int((sax.n_segments - window_size) / 2)
target = np.array(motif[name]["m"]).reshape(32,1)

found = 0
with gzip.open(dst, 'wt') as r:
    for chr_, start_, coverage in slide(src):
        if np.sum(coverage) == 0: continue
        trsf = sax.fit_transform(TimeSeriesScalerMeanVariance().fit_transform([coverage]))
        dist = sax.distance_sax(trsf[0][offset:offset+window_size], target)
        if dist > threshold: continue # Q[0.05] ~= 10
        D, start, stop = (format(dist, ".2f"), start_ + offset*scale, start_ + (offset + window_size)*scale)
        r.write(f"{chr_}\t{start}\t{stop}\t{D}\n")
        found += 1
        echo(f"Chr: {chr_} • Regions found: {found}\r")

echo(f"\nDone\n")
