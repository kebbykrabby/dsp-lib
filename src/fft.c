/*
 * @file fft.c
 *
 * Implementation of Radix-2 Cooley-Tukey Fast Fourier Transform (FFT) and
 * Inverse FFT (IFFT) algorithms operating on complex input data.
 *
 * Features:
 *   - Recursive radix-2 FFT implementation
 *   - Supports input length N where N is a power of two
 *   - In-place transform of complex data array
 *   - IFFT implemented via conjugation, FFT, and scaling
 *
 * Usage:
 *   - fft(Complex *x, int n) computes the forward FFT of input array x of length n.
 *   - ifft(Complex *x, int n) computes the inverse FFT of input array x of length n.
 *
 * Requirements:
 *   - Input length n must be a power of two.
 *   - Complex type must have at least two double fields: real and imag.
 *
 * Algorithm Details:
 *   The fft_rec() function implements the recursive radix-2 Cooley-Tukey FFT:
 *   - Divides the input into even and odd indexed samples
 *   - Recursively computes FFT on these halves
 *   - Combines results using twiddle factors (complex exponentials)
 *
 * Memory:
 *   - Dynamic memory allocation for even and odd arrays at each recursion level.
 *   - May be inefficient for very large input sizes or embedded systems.
 *
 * Created on: [Insert Date]
 * Author: Omri Kebede
 */

/******************************************************************************/

#include <math.h>
#include <stdlib.h>
#include "fft.h"
// #include "complex.h"

#define PI 3.14159265358979323846

/******************************************************************************
 * fft_rec
 *
 * @brief        Recursive radix-2 Cooley-Tukey FFT implementation
 *
 * @param[inout] x  Pointer to an array of Complex numbers representing the input
 *                  time-domain samples. The array is overwritten with frequency-domain
 *                  output.
 * @param[in]    n  Length of the input array. Must be a power of two.
 *
 * @returns      void
 *
 * @details
 *   This function performs an in-place recursive FFT on the input array x:
 *   1. Base case: if n <= 1, the FFT of a single element is the element itself.
 *   2. The array is split into even-indexed and odd-indexed elements.
 *   3. fft_rec is called recursively on each half.
 *   4. Results are combined using twiddle factors W_N^k = exp(-2*pi*i*k/N).
 *
 * @note
 *   - The function assumes the input size n is a power of two.
 *   - Allocates temporary memory for even and odd arrays at each recursion.
 *   - Called internally by fft() and ifft() functions.
 *
 * @warning
 *   - Recursive allocation may be costly in memory and time for large inputs.
 ******************************************************************************/
static void fft_rec(Complex *x, int n) {
    if (n <= 1) return;

    Complex *even = malloc(n / 2 * sizeof(Complex));
    Complex *odd = malloc(n / 2 * sizeof(Complex));

    // Split input into even and odd elements
    for (int i = 0; i < n / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    // Recursive FFT calls
    fft_rec(even, n / 2);
    fft_rec(odd, n / 2);

    // Combine step with twiddle factors
    for (int k = 0; k < n / 2; k++) {
        double t = -2 * PI * k / n;
        Complex twiddle = {cos(t), sin(t)};
        Complex temp = {
            twiddle.real * odd[k].real - twiddle.imag * odd[k].imag,
            twiddle.real * odd[k].imag + twiddle.imag * odd[k].real
        };

        x[k].real       = even[k].real + temp.real;
        x[k].imag       = even[k].imag + temp.imag;
        x[k + n / 2].real = even[k].real - temp.real;
        x[k + n / 2].imag = even[k].imag - temp.imag;
    }

    free(even);
    free(odd);
}

/******************************************************************************
 * fft
 *
 * @brief        Computes the forward FFT of complex data
 *
 * @param[inout] x  Pointer to an array of Complex numbers representing time-domain
 *                  samples. The output frequency-domain coefficients overwrite x.
 * @param[in]    n  Length of the input array, must be a power of two.
 *
 * @returns      void
 *
 * @details
 *   Wrapper function calling the recursive FFT implementation.
 ******************************************************************************/
void fft(Complex *x, int n) {
    fft_rec(x, n);
}

/******************************************************************************
 * ifft
 *
 * @brief        Computes the inverse FFT of complex data
 *
 * @param[inout] x  Pointer to an array of Complex numbers representing frequency-domain
 *                  coefficients. The output time-domain samples overwrite x.
 * @param[in]    n  Length of the input array, must be a power of two.
 *
 * @returns      void
 *
 * @details
 *   Computes the inverse FFT by:
 *   1. Conjugating the input array.
 *   2. Calling the forward FFT on the conjugated data.
 *   3. Conjugating the FFT output and scaling by 1/n.
 ******************************************************************************/
void ifft(Complex *x, int n) {
    // Conjugate input
    for (int i = 0; i < n; i++) {
        x[i].imag = -x[i].imag;
    }

    fft_rec(x, n);

    // Conjugate output and scale
    for (int i = 0; i < n; i++) {
        x[i].real = x[i].real / n;
        x[i].imag = -x[i].imag / n;
    }
}
/* End of file */
/******************************************************************************/