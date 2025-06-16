/*
 * @file iir_example.c
 *  
 * Test routine for IIR filter:
 *   1. Initializes a 2nd order Butterworth low-pass filter
 *   2. Processes a short impulse input sequence through the filter
 *   3. Prints the filter output samples to standard output
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include <stdio.h>
#include "iir_filter.h"  /* IIR filter header */

/******************************************************************************/
/* main function */

/******************************************************************************
 * main
 *
 * @param[in]     none
 *
 * @returns       0 if successful, 1 if an error occurred
 *
 * @note          Demonstrates initialization and sample-by-sample processing
 *                of an IIR filter with a fixed impulse input.
 *
 * @warning       None
 ******************************************************************************/
int main() {
    const int order = 2;
    double a[] = {1.0, -1.5610180758007182, 0.6413515380575631}; // feedback coefficients a0=1 (implicit), a1, a2
    double b[] = {0.020083365564211236, 0.04016673112842247, 0.020083365564211236}; // feedforward coefficients b0, b1, b2

    IIRFilter filter;
    if (iir_init(&filter, order, a, b) != 0) {
        fprintf(stderr, "Failed to initialize IIR filter\n");
        return 1;
    }

    double input_samples[] = {1.0, 0.0, 0.0, 0.0, 0.0}; // impulse input signal
    int len = sizeof(input_samples) / sizeof(double);

    for (int i = 0; i < len; i++) {
        double output = iir_process_sample(&filter, input_samples[i]);
        printf("Input: %f, Output: %f\n", input_samples[i], output);
    }

    iir_free(&filter);
    return 0;
}
/* End of main() */
/******************************************************************************/
