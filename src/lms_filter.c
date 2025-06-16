/**
 * @file lms_filter.c
 *
 * @brief Implements the Least Mean Squares (LMS) adaptive filtering algorithm.
 *
 * This function processes a noisy input signal and a desired (clean) signal to adaptively minimize
 * the mean squared error. It returns the filtered signal output and the final filter weights.
 *
 * Created on: Jun 16, 2025  
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include <stdlib.h>
#include <string.h>
#include "lms_filter.h"

/******************************************************************************/
/**
 * @brief Applies the Least Mean Squares (LMS) adaptive filtering algorithm.
 *
 * @param[in]  noisy_signal     Pointer to the input noisy signal array (length: num_samples).
 * @param[in]  desired_signal   Pointer to the desired (reference) signal array (length: num_samples).
 * @param[in]  num_samples      Number of samples in the input signals.
 * @param[in]  filter_order     Number of filter taps (length of adaptive filter).
 * @param[in]  mu               Learning rate (adaptation step size), e.g., 0.001–0.1.
 * @param[out] output_signal    Pointer to the output signal array (length: num_samples).
 * @param[out] final_weights    Pointer to the final filter weights array (length: filter_order).
 *
 * @returns     void
 *
 * @note 
 *  - The first `filter_order` samples in the output will be zero.
 *  - The user must preallocate memory for `output_signal` and `final_weights`.
 *  - This implementation uses a direct form LMS update rule:
 *       w_j ← w_j + 2 * mu * error * x_j
 *
 * @warning
 *  - If memory allocation for internal weights fails, the function exits early without processing.
 */
void lms_filter(
    const double *noisy_signal,
    const double *desired_signal,
    int num_samples,
    int filter_order,
    double mu,
    double *output_signal,
    double *final_weights
) {
    double *weights = calloc(filter_order, sizeof(double));
    if (!weights) return;  /* allocation failed */

    int i, j;

    /* Initialize output signal to zero */
    for (i = 0; i < num_samples; i++) {
        output_signal[i] = 0.0;
    }

    /* Main LMS loop: iterate over each sample starting from `filter_order` */
    for (i = filter_order; i < num_samples; i++) {
        double y = 0.0;  /* predicted output for current sample */

        /* Compute filter output using dot product of weights and past inputs */
        for (j = 0; j < filter_order; j++) {
            y += weights[j] * noisy_signal[i - j - 1];
        }

        double error = desired_signal[i] - y;  /* compute instantaneous error */

        /* Update filter weights based on error and input */
        for (j = 0; j < filter_order; j++) {
            weights[j] += 2 * mu * error * noisy_signal[i - j - 1];
        }

        output_signal[i] = y;  /* store output */
    }

    /* Copy final weights to user-provided array */
    for (i = 0; i < filter_order; i++) {
        final_weights[i] = weights[i];
    }

    free(weights);  /* cleanup allocated memory */
}
/* End of lms_filter() */
/******************************************************************************/
