import glob

f_collection = './storage/motif_collection.c'
f_names = './storage/motif_names.c'
f_dist = './storage/ndist.c'

files = glob.glob('./motif/mt_*.motif')
files.sort()
f = open(f_collection, 'w')
f.write("int get_from_collection(char * code, Motif * result){\n")
f.write(f"\tMotif ms[{len(files)}];\n\n")

names = []
for i, m in enumerate(files):
    with open(m, 'r') as mf:
        obj = {}
        for line in mf.readlines():
            key, val = line.replace('\n', '').split(': ')
            obj[key] = val
    motif = obj['motif'].split(',')
    names.append(obj['type'])

    f.write(f"\tsize_t motif_{i}[MOTIF_MAX_BYTES] = {{{obj['motif']}}};\n")
    f.write(f"\tmemcpy(ms[{i}].motif, &motif_{i}, sizeof(size_t) * MOTIF_MAX_BYTES);\n")
    f.write(f"\tstrcpy(ms[{i}].code, \"{obj['type']}\");\n")
    f.write(f"\tms[{i}].size = {len(motif)};\n")
    f.write(f"\tms[{i}].segments = {obj['sax_segments']};\n")
    f.write(f"\tms[{i}].alphabet = {obj['sax_alphabet']};\n")
    f.write(f"\tms[{i}].offset = {obj['offset']};\n")
    f.write(f"\n")

f.write(f"\tfor (size_t i = 0; i < 16; i++) if (!strcmp(ms[i].code, code)) {{ * result = ms[i]; return 0; }};\n")
f.write(f"\treturn 1;\n")
f.write("}\n")
f.close()

# --------------------------------------------------------------------------- #

f = open(f_names, 'w')
items = '"' + '", "'.join(names) + '"'
f.write(f'const char * collection_names[] = {{{items}}};\n')
f.write(f'const int collection_size = {len(names)};\n')
f.write(f'const int max_code_len = {max([len(i) for i in names])};\n')
f.close()

# --------------------------------------------------------------------------- #

with open('./storage/_ND840.data', 'r') as f:
    ndist = ",".join([line.replace('\n', '') for line in f.readlines()])
    f = open(f_dist, 'w')
    f.write(f"double ndist840[840] = {{{ndist}}};\n")
    f.close()
