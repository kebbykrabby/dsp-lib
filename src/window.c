/*
 * @file window.c
 *  
 * Implements window function generation commonly used in signal processing.
 * Provides functions to generate window coefficients for various window types,
 * such as Hamming, Hann, and Rectangular (default).
 *
 * Window functions are applied to signals prior to Fourier analysis to
 * reduce spectral leakage by tapering the signal edges.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/  
/* include block */
#include <math.h>
#include "window.h"

/******************************************************************************/  
/** local definitions **/
#define PI 3.14159265358979323846

/******************************************************************************  
 * generate_window
 *  
 * @param[out]  window Pointer to an array of doubles to hold window coefficients.
 * @param[in]   size   Number of samples in the window.
 * @param[in]   type   Type of window to generate:
 *                    - WINDOW_HAMMING: Hamming window
 *                    - WINDOW_HANN: Hann window
 *                    - default: Rectangular window (all ones)
 *  
 * @returns     void
 *  
 * @note       Computes and fills the array with window coefficients according
 *             to the specified window type. The window should be pre-allocated
 *             with length at least `size`.
 *  
 * @warning    The function assumes 'size' is greater than 1 to avoid division by zero.
 */
void generate_window(double *window, int size, WindowType type) {
    for (int n = 0; n < size; n++) {
        switch(type) {
            case WINDOW_HAMMING:
                window[n] = 0.54 - 0.46 * cos(2 * PI * n / (size - 1));
                break;
            case WINDOW_HANN:
                window[n] = 0.5 * (1 - cos(2 * PI * n / (size - 1)));
                break;
            default:
                window[n] = 1.0;
                break;
        }
    }
}
/* End of generate_window() */
/******************************************************************************/
