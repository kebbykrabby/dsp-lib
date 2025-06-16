/*
 * @file fir_filter.c
 *  
 * Implements a Finite Impulse Response (FIR) filter.
 * Provides functions for filter initialization, resetting state,
 * processing individual input samples, and freeing resources.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/ 
/* include block */
#include <stdlib.h>
#include <string.h>
#include "fir_filter.h"

/******************************************************************************
 * fir_filter_init
 *
 * @param[in,out] filter Pointer to FIRFilter struct to initialize.
 * @param[in] coeffs     Array of FIR filter coefficients.
 * @param[in] num_taps   Number of filter taps (length of coeffs).
 *
 * @returns 0 on success, -1 on memory allocation failure.
 *
 * @note Initializes the FIR filter structure by allocating memory for the
 *       coefficients and history buffers, copies coefficients, and
 *       sets the initial history index to zero.
 *
 * @warning Caller must ensure fir_filter_free() is called to avoid leaks.
 */
int fir_filter_init(FIRFilter *filter, const double *coeffs, size_t num_taps) {
    filter->num_taps = num_taps;
    filter->coeffs = (double*)malloc(sizeof(double) * num_taps);
    filter->history = (double*)calloc(num_taps, sizeof(double));
    filter->history_index = 0;

    if (!filter->coeffs || !filter->history) {
        free(filter->coeffs);
        free(filter->history);
        return -1; // Allocation failed
    }

    memcpy(filter->coeffs, coeffs, sizeof(double) * num_taps);
    return 0; // Success
}
/* End of fir_filter_init() */
/******************************************************************************/

/******************************************************************************
 * fir_filter_reset
 *
 * @param[in,out] filter Pointer to FIRFilter struct to reset.
 *
 * @returns None
 *
 * @note Resets the filter history buffer by zeroing the delay line and
 *       resetting the circular buffer index.
 *
 * @warning None
 */
void fir_filter_reset(FIRFilter *filter) {
    if (filter->history) {
        memset(filter->history, 0, sizeof(double) * filter->num_taps);
    }
    filter->history_index = 0;
}
/* End of fir_filter_reset() */
/******************************************************************************/

/******************************************************************************
 * fir_filter_process_sample
 *
 * @param[in,out] filter Pointer to FIRFilter struct.
 * @param[in]     input  Input sample to filter.
 *
 * @returns Filtered output sample.
 *
 * @note Inserts the input sample into the history buffer and computes
 *       the FIR output by convolving the coefficients with the delay line.
 *       Uses a circular buffer approach for the history.
 *
 * @warning None
 */
double fir_filter_process_sample(FIRFilter *filter, double input) {
    filter->history[filter->history_index] = input;

    double output = 0.0;
    size_t index = filter->history_index;

    for (size_t i = 0; i < filter->num_taps; i++) {
        output += filter->coeffs[i] * filter->history[index];
        if (index == 0)
            index = filter->num_taps - 1;
        else
            index--;
    }

    filter->history_index = (filter->history_index + 1) % filter->num_taps;
    return output;
}
/* End of fir_filter_process_sample() */
/******************************************************************************/

/******************************************************************************
 * fir_filter_free
 *
 * @param[in,out] filter Pointer to FIRFilter struct.
 *
 * @returns None
 *
 * @note Frees memory allocated for coefficients and history buffers
 *       and clears struct members to safe defaults.
 *
 * @warning After calling this, filter should not be used unless reinitialized.
 */
void fir_filter_free(FIRFilter *filter) {
    free(filter->coeffs);
    free(filter->history);
    filter->coeffs = NULL;
    filter->history = NULL;
    filter->num_taps = 0;
    filter->history_index = 0;
}
/* End of fir_filter_free() */
/******************************************************************************/
