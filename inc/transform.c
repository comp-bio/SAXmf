Moments train(const double * input)
{
    Moments m;
    m.mean = 0;
    m.stdev = DBL_MIN;

    size_t n = 0;
    double M2 = 0;
    for (big k = 0; k != WINDOW; ++k) {
        ++n;
        double delta = input[k] - m.mean;
        m.mean += delta / n;
        M2 += delta * (input[k] - m.mean);
    }
    m.stdev = sqrt(M2 / (n-1));
    if (m.stdev == 0) m.stdev = DBL_MIN;

    return m;
}

void transform(const double * input, Motif motif, size_t * out, size_t pointer)
{
    Moments m = train(input);
    big merged = WINDOW/motif.segments;
    big i = 0;
    size_t merged_k = 0;
    double sum = 0;
    for (big k = pointer; k != WINDOW + pointer; ++k) {
        merged_k++;
        sum += (input[k % WINDOW] - m.mean) / m.stdev;
        if (merged_k == merged) {
            sum = sum/merged;
            size_t a = 0;
            for (a = 0; a < motif.alphabet-1; a++) if (motifs[0].dist[a] > sum) break; // [!!!]
            out[i++] = a;
            merged_k = 0;
            sum = 0;
        }
    }
}

/*
void transform_OLD(const double * input, big offset, big size, size_t * out, big mod)
{
    Moments m = train(input, offset, size);
    big window = size/10; //model.segments;
    big i = 0;
    double sum = 0;
    size_t window_k = 0;
    for (big k = offset; k != offset + size; ++k) {
        window_k++;
        sum += (input[k % mod] - m.mean) / m.stdev;
        if (window_k == window) {
            sum = sum/window;
            window_k = 0;
            size_t a = 0;
            for (a = 0; a < model.alphabet; a++) if (model.B[a] > sum) break;
            out[i++] = a-1;
        }
    }
}

size_t * transform_wrapper(const double * input, big offset, big size)
{
    size_t * out = (size_t *) malloc(sizeof(size_t) * model.segments);
    transform(input, offset, size, out, offset + size + 1);
    return out;
}
*/