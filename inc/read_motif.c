Motif read_motif(char * src)
{
    Motif mt;
    mt.size = 0;
    FILE * fp = fopen(src, "r+");
    if (fp == NULL) terminate("Motif file not found");

    char key[MOTIF_MAX_BYTES];
    char value[MOTIF_MAX_BYTES];
    while(1) {
        if (fscanf(fp, "%[^:]: %s\n", &key[0], &value[0]) != 2) {
            if (feof(fp)) break;
        }
        if (strcmp(key, "sax_segments") == 0) mt.segments = (size_t) atoi(value);
        if (strcmp(key, "sax_alphabet") == 0) mt.alphabet = (size_t) atoi(value);
        if (strcmp(key, "offset") == 0) mt.offset = (double) atof(value);
        if (strcmp(key, "type") == 0) strcpy(mt.code, value);

        if (strcmp(key, "motif") == 0) {
            char *ptr = strtok(value, ",");
            while(ptr != NULL)
            {
                mt.motif[mt.size++] = (size_t) atoi(ptr);
                ptr = strtok(NULL, ",");
            }
        }
    }

    printf("%zu", mt.alphabet);

    fclose(fp);
    return mt;
}
