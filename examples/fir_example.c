/*
 * @file fir_example.c
 * 
 * Example usage of the FIR filter implementation.
 * 
 * Demonstrates initialization of a 5-tap moving average FIR filter,
 * processing a sequence of input samples, and outputting the filtered results.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/ 
/* include block */
#include <stdio.h>
#include "fir_filter.h"

/******************************************************************************
 * main
 *
 * @returns 0 on success, 1 on failure to initialize filter
 *
 * @note
 * - Defines a simple 5-tap moving average filter.
 * - Processes 10 input samples through the FIR filter.
 * - Prints input and output sample pairs.
 * - Frees filter resources before exiting.
 *
 * @warning
 * - Checks for allocation failure during filter initialization.
 */
int main() {
    double coeffs[] = {0.2, 0.2, 0.2, 0.2, 0.2}; // 5-tap moving average coefficients
    double input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t len = sizeof(input) / sizeof(input[0]);

    FIRFilter filter;
    if (fir_filter_init(&filter, coeffs, 5) != 0) {
        fprintf(stderr, "FIR filter initialization failed\n");
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        double out = fir_filter_process_sample(&filter, input[i]);
        printf("Input: %.2f\tOutput: %.2f\n", input[i], out);
    }

    fir_filter_free(&filter);
    return 0;
}
/* End of main() */
/******************************************************************************/
