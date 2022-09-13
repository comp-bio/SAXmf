#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(N) ((N<0)?(-N):(N))

double sax_dist_motif(Motif motif, size_t * x)
{
    size_t offset = (size_t) floor(motif.offset);
    double d = 0;
    // fprintf(stderr, "---- ---- \n");
    for (size_t k = offset; k != motif.size + offset; ++k) {
        if (ABS(x[k] - motif.motif[k-offset]) <= 1) continue;
        size_t max_symbol = MAX(x[k],motif.motif[k-offset]);
        size_t min_symbol = MIN(x[k],motif.motif[k-offset]);
        // fprintf(stderr, "%zu %zu %f %f \n", max_symbol, min_symbol, motif.dist[max_symbol-1], motif.dist[min_symbol]);
        d += pow(motif.dist[max_symbol-1] - motif.dist[min_symbol], 2);
    }
    return sqrt(d * ((float) WINDOW) / motif.size);
}


void * distances(void * data)
{
    ThreadData * block = (ThreadData*) data;

    FILE * f = fopen(src, "rb");
    if (f == NULL) {
        fprintf(stderr, "[file not found]: %s, %llu\n", src, block->begin);
        pthread_exit(0);
    }

    size_t * transformed = (size_t *) malloc(sizeof(size_t) * block->motif.segments);
    double input[WINDOW];

    fseek(f, block->begin * STEP * 2, SEEK_SET);
    size_t pointer = 0;
    for (pointer = 0; pointer < (WINDOW - STEP); ++pointer) {
        input[pointer] = (double) (fgetc(f) * 256 + fgetc(f));
    }

    for (big s = 0; s < block->count; s++) {
        for (size_t i = 0; i < STEP; ++i) {
            input[pointer] = (double) (fgetc(f) * 256 + fgetc(f));
            pointer += 1;
            if (pointer == WINDOW) pointer = 0;
        }

        big offset = (block->begin + s) * STEP;

        transform(input, block->motif, transformed, pointer);
        double dd = sax_dist_motif(block->motif, transformed);

        fprintf(block->outfile, "%s\t%llu\t%llu\t%f\n", chr, offset, offset + WINDOW, dd);

        /*
         * DEBUG:
         * Write SAX transform result
        fprintf(block->outfile, "%s\t%llu\t%llu\t", chr, offset, offset + WINDOW);
        for (size_t i = 0; i < block->motif.segments; ++i) {
            fprintf(block->outfile, "%zu ", transformed[i]);
        }
        fprintf(block->outfile, "\n");
        */
    }

    fclose(f);
    free(transformed);
    pthread_exit(0);
}
