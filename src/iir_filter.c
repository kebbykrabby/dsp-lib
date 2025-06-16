/*
 * @file iir_filter.c
 * 
 * Implementation of a direct form I Infinite Impulse Response (IIR) filter.
 * Provides initialization, single-sample processing, and cleanup functions.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include <stdlib.h>
#include <string.h>
#include "iir_filter.h"

/******************************************************************************
 * iir_init
 *
 * @param[in,out] filter pointer to IIRFilter struct to initialize
 * @param[in]     order  filter order (number of feedback coefficients)
 * @param[in]     a      array of feedback coefficients, a[0] assumed to be 1 (not stored)
 * @param[in]     b      array of feedforward coefficients (length order+1)
 *
 * @returns 0 on success, -1 on memory allocation failure
 *
 * @note
 * - Allocates memory for coefficients and input/output histories.
 * - Copies coefficients from given arrays (a excluding a[0], b entire).
 * - Initializes histories to zero.
 * - The filter uses the difference equation:
 *     y[n] = sum_{i=0}^{order} b[i]*x[n-i] - sum_{i=1}^{order} a[i]*y[n-i]
 *
 * @warning
 * - Caller must ensure 'a' array has at least order+1 elements, with a[0] = 1.
 * - Must call iir_free() to release allocated resources.
 */
int iir_init(IIRFilter *filter, int order, const double *a, const double *b) {
    filter->order = order;

    filter->a = malloc(order * sizeof(double));
    filter->b = malloc((order + 1) * sizeof(double));
    filter->x_history = calloc(order + 1, sizeof(double));
    filter->y_history = calloc(order, sizeof(double));

    if (!filter->a || !filter->b || !filter->x_history || !filter->y_history) {
        free(filter->a);
        free(filter->b);
        free(filter->x_history);
        free(filter->y_history);
        return -1;
    }

    // a[0] is assumed 1 and not stored
    memcpy(filter->a, a + 1, order * sizeof(double));
    memcpy(filter->b, b, (order + 1) * sizeof(double));

    return 0;
}
/* End of iir_init() */
/******************************************************************************/

/******************************************************************************
 * iir_process_sample
 *
 * @param[in,out] filter pointer to initialized IIRFilter struct
 * @param[in]     input  new input sample to process
 *
 * @returns output sample after filtering
 *
 * @note
 * - Processes a single input sample through the IIR filter using direct form I.
 * - Updates internal input and output histories.
 * - Computes output as:
 *     y[n] = sum_{i=0}^{order} b[i]*x[n-i] - sum_{i=1}^{order} a[i]*y[n-i]
 *
 * @warning
 * - filter must be properly initialized before calling.
 */
double iir_process_sample(IIRFilter *filter, double input) {
    int order = filter->order;

    // Shift input history to make room for new sample
    memmove(&filter->x_history[1], &filter->x_history[0], order * sizeof(double));
    filter->x_history[0] = input;

    // Compute output sample (feedforward part)
    double output = 0.0;
    for (int i = 0; i <= order; i++) {
        output += filter->b[i] * filter->x_history[i];
    }

    // Subtract feedback contributions
    for (int i = 0; i < order; i++) {
        output -= filter->a[i] * filter->y_history[i];
    }

    // Update output history
    memmove(&filter->y_history[1], &filter->y_history[0], (order - 1) * sizeof(double));
    filter->y_history[0] = output;

    return output;
}
/* End of iir_process_sample() */
/******************************************************************************/

/******************************************************************************
 * iir_free
 *
 * @param[in,out] filter pointer to IIRFilter struct to free resources of
 *
 * @note
 * - Frees all dynamically allocated memory inside the filter.
 * - Does not free the filter struct itself.
 *
 * @warning
 * - Safe to call with NULL pointer (no operation).
 */
void iir_free(IIRFilter *filter) {
    if (!filter) return;
    free(filter->a);
    free(filter->b);
    free(filter->x_history);
    free(filter->y_history);
}
/* End of iir_free() */
/******************************************************************************/
