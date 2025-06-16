/*
 * @file iir_filter.h
 *
 * Header file for iir_filter.c
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#ifndef IIR_FILTER_H_
#define IIR_FILTER_H_

/* Structure containing IIR filter parameters and state information */
typedef struct {
    int order;          /* filter order */
    double *a;          /* feedback coefficients array (a[0] assumed 1 and not stored) */
    double *b;          /* feedforward coefficients array (length order+1) */
    double *x_history;  /* input samples history buffer */
    double *y_history;  /* output samples history buffer */
} IIRFilter;

// Initialize IIR filter struct, allocate memory, and copy coeffs
int iir_init(IIRFilter *filter, int order, const double *a, const double *b);

// Process one input sample and return filtered output
double iir_process_sample(IIRFilter *filter, double input);

// Free allocated memory
void iir_free(IIRFilter *filter);

#endif
