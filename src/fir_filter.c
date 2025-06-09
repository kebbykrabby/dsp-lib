#include <stdlib.h>
#include <string.h>
#include "fir_filter.h"

void fir_filter_init(FIRFilter *filter, const double *coeffs, size_t num_taps) {
    filter->num_taps = num_taps;
    filter->coeffs = (double*)malloc(sizeof(double) * num_taps);
    memcpy(filter->coeffs, coeffs, sizeof(double) * num_taps);

    filter->history = (double*)calloc(num_taps, sizeof(double));
    filter->history_index = 0;
}

double fir_filter_process_sample(FIRFilter *filter, double input) {
    filter->history[filter->history_index] = input;
    double output = 0.0;
    size_t index = filter->history_index;
    for (size_t i = 0; i < filter->num_taps; i++) {
        output += filter->coeffs[i] * filter->history[index];
        if (index == 0) index = filter->num_taps - 1;
        else index--;
    }
    filter->history_index = (filter->history_index + 1) % filter->num_taps;
    return output;
}

void fir_filter_free(FIRFilter *filter) {
    free(filter->coeffs);
    free(filter->history);
}
