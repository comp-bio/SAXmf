void argparse(int argc, char *argv[], size_t * threads)
{
    if (argc <= 1) {
        usage();
        exit(0);
    }

    for (size_t a = 0; a != argc; a++) {
        if (!strcmp(argv[a], "-m") && a + 1 < argc) {
            motif = read_motif(argv[a + 1]);
            motif_set = 1;
        }
        if (!strcmp(argv[a], "-n") && a + 1 < argc) {
            get_from_collection(argv[a + 1], &motif);
            motif_set = 1;
        }
        if (!strcmp(argv[a], "-t") && a + 1 < argc) {
            * threads = (size_t) atoi(argv[a + 1]);
        }
        if (!strcmp(argv[a], "-f") && a + 1 < argc) {
            src = (char *) malloc(sizeof(char) * (strlen(argv[a + 1]) + 1));
            chr = (char *) malloc(sizeof(char) * (strlen(argv[a + 1]) + 1));
            strcpy(src, argv[a + 1]);
            strcpy(chr, argv[a + 1]);
            bam_set = 1;
        }
        if (!strcmp(argv[a], "-o") && a + 1 < argc) {
            out = (char *) malloc(sizeof(char) * (strlen(argv[a + 1]) + 1));
            strcpy(out, argv[a + 1]);
            out_set = 1;
        }
    }

    if (motif_set != 1) terminate("Motif not specified.\n  Use -m <filename> or -n <code>");
    if (bam_set != 1) terminate("BAM file not specified.\n  Use -f <filename>");
    // if (out_set != 1) terminate("Output file not specified.\n  Use -o <filename>");

    // chr = basename(chr);
    sscanf(chr, "%[^.]", chr);

    motif.dist = (double*) malloc(motif.alphabet * sizeof(double));
    size_t total = 840;
    size_t line = 0;
    size_t i = 0;
    for (size_t n = 0; n < 840; n++) {
        if (line == total/motif.alphabet) { motif.dist[i++] = ndist840[n-1]; line = 0; }
        line++;
    }
}
