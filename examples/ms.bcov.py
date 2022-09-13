# -*- coding: utf-8 -*-
import sys, os, math, warnings
import numpy as np

warnings.filterwarnings("ignore")

from tslearn.piecewise import SymbolicAggregateApproximation
from tslearn.preprocessing import TimeSeriesScalerMeanVariance

WINDOW = 512
STEP = 8
motif = {
    'motif': [19,19,19,19,19,19,19,19,19,18,18,17,16,15,14,13,11,9,7,7,5,4,3,3,3,3,3,3,3,3,3,3],
    'offset': 14.440743843189814,
    'code': 'DEL_L',
    'sax_segments': 64,
    'sax_alphabet': 24
}


def echo(text, color='37'):
    sys.stdout.write("\033[1;%sm%s\033[m" % (color, text))


def usage():
    echo('Usage:    python3 %s [source bcov] > [result]\n' % sys.argv[0])
    echo('Example:  python3 %s HG002/1.bcov\n\n' % sys.argv[0])
    sys.exit(1)


def bcov(file, start=0):
    with open(file, 'rb') as f:
        f.seek(start * 2)
        while True:
            value = f.read(2)
            if not value: break
            yield value[0] * 256 + value[1]


if len(sys.argv) < 2:
    usage()

src = sys.argv[1]
sax = SymbolicAggregateApproximation(n_segments=motif['sax_segments'], alphabet_size_avg=motif['sax_alphabet'])
bases = int(os.path.getsize(src)/2)
offset = math.floor(motif['offset'])

for start in range(0, bases - WINDOW, STEP):
    tmp = bcov(src, start)
    block = [next(tmp) for _ in range(WINDOW)]
    trsf = sax.fit_transform(TimeSeriesScalerMeanVariance().fit_transform([block]))
    x1 = trsf[0][offset : offset+len(motif['motif'])]
    x2 = np.array([[i] for i in motif['motif']])
    dist = sax.distance_sax(x1, x2)
    print(f'big\t{start}\t{start+512}\t{dist}')
