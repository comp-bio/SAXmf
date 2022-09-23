#define WINDOW 512 // WINDOW size from DB (512)
#define STEP   8   // Window part for step (8 -> 1/8)

void decomposition(size_t * threads)
{
    FILE * f = fopen(src, "rb");
    if (f == NULL) terminate("The specified .bcov file not found.");

    fseek(f, 0, SEEK_END);
    big total_bp = ((big) ftell(f))/2;
    fclose(f);

    big total_steps = floorl(((double) (total_bp - WINDOW)) / STEP);
    big steps4thread = total_steps;
    if (*threads > total_steps/32) *threads = total_steps/32;
    if (*threads > 1) steps4thread = ceil((double) total_steps/(*threads));

    pd = (ThreadData*) malloc((*threads) * sizeof(ThreadData));
    pd_set = 1;

    for (size_t t = 0; t < *threads; t++){
        pd[t].begin = t * steps4thread;
        pd[t].count = steps4thread;
        pd[t].outfile = tmpfile();

        if (pd[t].begin >= total_steps) {
            pd[t].count = 0;
        } else {
            if (pd[t].begin + pd[t].count > total_steps) {
                pd[t].count = total_steps - pd[t].begin;
            }
        }

        if (pd[t].outfile == NULL) terminate("Error creating temporary file");
    }

    if (DEBUG == 1) {
        printf("--- Decomposition --- \n");
        printf("total_steps:  %llu \n", total_steps);
        printf("steps4thread: %llu \n", steps4thread);
        printf("magic:        %lu > %llu \n", (size_t) steps4thread * (*threads), total_steps);
        for (size_t t = 0; t < *threads; t++){
            printf("-> Thread: %zu\n", t);
            printf("   begin: %llu, count: %llu\n", pd[t].begin, pd[t].count);
            printf("   chr: %s, src: %s\n", pd[t].chr, pd[t].src);
        }
        printf("\n");
    }
}
