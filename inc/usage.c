void usage()
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  ./saxmf -f <bcov filename>\n");
    fprintf(stderr, "          -m <motif filename> [OR -n <motif code>]\n");
    fprintf(stderr, "          -o [result (optional)]\n");
    fprintf(stderr, "          -t [threads (optional)]\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, "  ./saxmf -f ./genome/chrX.bcov -m ./motif/DEL_L.motif > output.bed\n");
    fprintf(stderr, "  ./saxmf -f ./genome/chrX.bcov -n \"DEL_L\" -o output.bed -t 10\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Built-in motif-codes (32x24) based on HGDP data: (-n CODE)\n");
    fprintf(stderr, "Details: https://swaveform.compbio.ru/");
    for (size_t i = 0; i < collection_size; i++) {
        if (i % 4 == 0) fprintf(stderr, "\n  ");
        int space = max_code_len - strlen(collection_names[i]);
        fprintf(stderr, "%s  %*s", collection_names[i], space, "");
    }
    fprintf(stderr, "\n\n");
}

void terminate(char * error)
{
    if (motif_set == 1) {
        free(motifs[0].dist); // [!!!]
        // free(motif.dist);
    }
    if (out_set == 1) {
        free(out);
    }
    if (bam_set == 1) {
        free(src);
        free(chr);
    }
    if (pd_set == 1) {
        free(pd);
    }

    fprintf(stderr, "\033[31;1mError:\033[0m\n");
    fprintf(stderr, "\033[31;1m  %s\033[0m\n\n", error);
    usage();
    exit(EXIT_FAILURE);
}
