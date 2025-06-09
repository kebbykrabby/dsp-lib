#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stddef.h>

typedef struct {
    size_t num_taps;
    double *coeffs;
    double *history;
    size_t history_index;
} FIRFilter;

void fir_filter_init(FIRFilter *filter, const double *coeffs, size_t num_taps);
double fir_filter_process_sample(FIRFilter *filter, double input);
void fir_filter_free(FIRFilter *filter);

#endif
