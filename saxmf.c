#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <libgen.h>
#include "pthread.h"

#include "inc/types.c"

// Motif motif;
Motif motifs[256];
ThreadData * pd;
char * src = NULL;
char * out = NULL;
char * chr = NULL;
short unsigned pd_set = 0;
short unsigned bam_set = 0;
short unsigned motif_set = 0;
short unsigned out_set = 0;

#include "storage/ndist.c"
#include "storage/motif_collection.c"
#include "storage/motif_names.c"
#include "inc/usage.c"
#include "inc/read_motif.c"
#include "inc/argparse.c"
#include "inc/decomposition.c"
#include "inc/transform.c"
#include "inc/distances.c"

int main(int argc, char *argv[])
{
    size_t threads = 1;
    argparse(argc, argv, &threads);
    decomposition(&threads);

    pthread_t * thread = (pthread_t*) malloc(threads * sizeof(pthread_t));

    for (unsigned t = 0; t < threads; t++){
        pthread_create( &(thread[t]), NULL, distances, &pd[t]);
    }
    for (unsigned t = 0; t < threads; t++){
        pthread_join(thread[t], NULL);
    }

    FILE * res;
    if (out != NULL) {
        res = fopen(out, "w");
        fprintf(res, "#chr\tstart\tend");
        for (int mti = 0; mti < motif_set; mti++) fprintf(res, "\t%s", motifs[mti].code);
        fprintf(res, "\n");
    } else {
        printf("#chr\tstart\tend");
        for (int mti = 0; mti < motif_set; mti++) printf("\t%s", motifs[mti].code);
        printf("\n");
    }

    for (unsigned t = 0; t < threads; t++){
        rewind(pd[t].outfile);
        char ch = fgetc(pd[t].outfile);
        while (ch != EOF) {
            if (out_set == 1) {
                fprintf(res, "%c", ch);
            } else {
                printf("%c", ch);
            }
            ch = fgetc(pd[t].outfile);
        }
        fclose(pd[t].outfile);
    }

    if (out_set == 1) {
        fclose(res);
        free(out);
    }

    free(src);
    free(chr);
    free(pd);
    free(thread);
    free(motifs[0].dist);
    // for (int mti = 0; mti < motif_set; mti++) free(motifs[mti].dist);



    return 0;
}
