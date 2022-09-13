# SAX Motif finder (saxmf)

A tool to quickly search for [motifs](https://swaveform.compbio.ru/) in genomic coverage data 
based on [SAX distance](https://jmotif.github.io/sax-vsm_site/morea/algorithm/SAX.html).  
**INPUT**: Genome coverage data in .bcov format, motif  
**OUTPUT**: .bed-file with SAX distances between each genome region and motif.
Smaller distances correspond to the most motif-like regions of the genome.


## Installation:
```bash
# Mac OSX
curl 'https://raw.githubusercontent.com/latur/saxmf/main/build/saxmf_Darwin' --output /usr/local/bin/saxmf
chmod +x /usr/local/bin/saxmf
saxmf

# Linux
curl 'https://raw.githubusercontent.com/latur/saxmf/main/build/saxmf_Linux' --output ~/.local/bin/saxmf
chmod +x ~/.local/bin/saxmf
saxmf
```


## Usage:
```bash
saxmf -f <bcov filename>
      -m <motif filename> [OR -n <motif code>]
      -o [result (optional)]
      -t [threads (optional)]
```


## Examples:
```bash
saxmf -f ./genome/chrX.bcov -m ./motif/DEL_L.motif > output.bed
saxmf -f ./genome/chr1.bcov -n "DEL_L" -o output.bed -t 10
```

Built-in motif-codes (32x24) based on HGDP data: (-n CODE)
```bash
  CNV_gain_L  CNV_gain_L  CNV_gain_R  CNV_gain_R  
  CNV_loss_L  CNV_loss_R  DEL_L       DEL_R       
  DUP_L       DUP_R       INS_C       INS_C       
  INV_L       INV_L       INV_R       INV_R  
```

Details: [https://swaveform.compbio.ru/](https://swaveform.compbio.ru/)


## Compilation:
```bash
gcc saxmf.c -std=c99 -m64 -O3 -lpthread -lm -o build/saxmf # OR: build/saxmf_$(uname)
# Valgrind, memcheck:
valgrind --leak-check=full ./build/saxmf_Linux -f ./examples/test.bcov -n DEL_L -o /tmp/output.bed -t 16
```
