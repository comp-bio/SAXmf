#define MOTIF_MAX_BYTES 1024

typedef unsigned long long int big;

typedef struct {
    double mean;
    double stdev;
} Moments;

typedef struct {
    char code[MOTIF_MAX_BYTES];
    size_t motif[MOTIF_MAX_BYTES];
    size_t size;
    size_t segments;
    size_t alphabet;
    double offset;
    double * dist;
} Motif;

typedef struct {
    char * src;
    char * chr;
    big begin;
    big count;
    size_t step;
    FILE * outfile;
} ThreadData;
