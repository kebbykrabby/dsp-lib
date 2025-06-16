/*
 * @file fir_filter.h
 *
 * Header file for fir_filter.c
 *
 * Provides a structure and functions for a Finite Impulse Response (FIR) filter.
 * Includes initialization, reset, sample processing, and cleanup routines.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */
#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stddef.h>

typedef struct {
    double *coeffs;
    double *history;
    size_t num_taps;
    size_t history_index;
} FIRFilter;

int fir_filter_init(FIRFilter *filter, const double *coeffs, size_t num_taps);
void fir_filter_reset(FIRFilter *filter);
double fir_filter_process_sample(FIRFilter *filter, double input);
void fir_filter_free(FIRFilter *filter);

#endif
