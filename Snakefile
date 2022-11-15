SAMPLES = ['example']
CHROMOSOMES = ['chr' + str(i) for i in range(1, 23)] + ['chrX', 'chrY']
CHROMOSOMES = ['NC_000017.10', 'NT_167251.1']

rule all:
  input:
    expand("snakedata/{sample}.DEL_L.bed", sample=SAMPLES)

rule join:
  input:
    expand("snakedata/{sample}/{chr}.bcov.bed", sample=SAMPLES, chr=CHROMOSOMES)
  output:
    expand("snakedata/{sample}.DEL_L.bed", sample=SAMPLES)
  shell:
    "cd snakedata\n"
    "for name in $(ls *.bed.gz); do\n"
    "  code=$(basename $name | awk -F\".\" {{'print $1'}})\n"
    "  for f in $(ls $code/*.bcov.bed); do\n"
    "    python3 ../join.py $f >> $code.DEL_L.bed\n"
    "  done\n" #
    "done\n"

rule msfind:
  input:
    expand("snakedata/{sample}/{chr}.bcov", sample=SAMPLES, chr=CHROMOSOMES)
  output:
    expand("snakedata/{sample}/{chr}.bcov.bed", sample=SAMPLES, chr=CHROMOSOMES)
  shell:
    "for f in $(ls snakedata/*/*.bcov); do\n"
    "  ./build/saxmf_Linux -f $f -n DEL_L > $f.bed\n"
    "done\n"

rule doc2bcov:
  input:
    expand("snakedata/{sample}/per-base.bed.gz", sample=SAMPLES),
    "bed2cov"
  output:
    expand("snakedata/{sample}/{chr}.bcov", sample=SAMPLES, chr=CHROMOSOMES)
  shell:
    "cd snakedata\n"
    "for name in $(ls *.bed.gz); do\n"
    "  code=$(basename $name | awk -F\".\" {{'print $1'}})\n"
    "  mkdir -p $code && cd $code\n"
    "  echo \"- $code.bed.gz -> $code/*.bcov\"\n"
    "  gzip -cd ../$code.per-base.bed.gz | ../../bed2cov\n"
    "  cd ../\n"
    "done\n"

rule doc:
  input:
    "snakedata/example.bam",
    "snakedata/example.bam.bai",
    "mosdepth"
  output:
    "snakedata/example.per-base.bed.gz"
  shell:
    "./mosdepth -t 24 snakedata/example snakedata/example.bam\n"

rule install_bed2cov:
  output:
    "bed2cov"
  shell:
    "if [ ! -f './bed2cov' ]; then "
    "  wget 'https://github.com/latur/SWaveform/raw/main/bed2cov/bed2cov'; "
    "  chmod +x './bed2cov';"
    "fi"

rule install_mosdepth:
  output:
    "mosdepth"
  shell:
    "if [ ! -f './mosdepth' ]; then "
    "  wget 'https://github.com/brentp/mosdepth/releases/download/v0.3.3/mosdepth'; "
    "  chmod +x './mosdepth';"
    "fi"
