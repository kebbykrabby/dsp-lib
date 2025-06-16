/*
 * @file spectrogram.c
 * 
 * Implementation of magnitude spectrogram computation for mono audio signals.
 * Provides functions to compute spectrogram with windowing and FFT, and to free memory.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include <stdlib.h>
#include <string.h>
#include "spectrogram.h"
#include "fft.h"
#include "window.h"

/******************************************************************************
 * compute_spectrogram
 *
 * @param[in]     wav           Pointer to WavData struct (must be mono)
 * @param[in]     fft_size      FFT window size (power of two)
 * @param[in]     hop_size      Hop size between frames (window shift)
 * @param[in]     window_type   Type of window to apply (e.g., Hanning, Hamming)
 * @param[out]    out_num_frames Pointer to store number of time frames
 * @param[out]    out_num_bins  Pointer to store number of frequency bins
 *
 * @returns       Pointer to 2D array [num_frames][num_bins] of magnitudes,
 *                or NULL on error (e.g. if input not mono)
 *
 * @note
 * - Allocates memory for spectrogram matrix and window buffers.
 * - Computes magnitude spectrogram by windowing, FFT, and magnitude calculation.
 * - Caller must free returned spectrogram with free_spectrogram().
 *
 * @warning
 * - Supports only mono audio (wav->num_channels == 1).
 */
double **compute_spectrogram(const WavData *wav,
                             int fft_size,
                             int hop_size,
                             WindowType window_type,
                             int *out_num_frames,
                             int *out_num_bins) {
    if (wav->num_channels != 1) return NULL;

    int num_samples = wav->num_samples;
    int num_frames = 1 + (num_samples - fft_size) / hop_size;
    int num_bins = fft_size / 2 + 1;

    // Allocate spectrogram 2D array [num_frames][num_bins]
    double **spectrogram = malloc(num_frames * sizeof(double *));
    for (int i = 0; i < num_frames; i++) {
        spectrogram[i] = calloc(num_bins, sizeof(double));
    }

    // Allocate and generate window coefficients
    double *window = malloc(sizeof(double) * fft_size);
    generate_window(window, fft_size, window_type);

    // Allocate FFT buffer
    Complex *fft_buffer = malloc(sizeof(Complex) * fft_size);

    for (int frame = 0; frame < num_frames; frame++) {
        int offset = frame * hop_size;

        // Apply window and copy samples to FFT buffer
        for (int i = 0; i < fft_size; i++) {
            int idx = offset + i;
            double sample = (idx < num_samples) ? wav->samples[idx] / 32768.0 : 0.0;
            fft_buffer[i].real = sample * window[i];
            fft_buffer[i].imag = 0.0;
        }

        // Perform FFT
        fft(fft_buffer, fft_size);

        // Calculate magnitude spectrum for each bin
        for (int bin = 0; bin < num_bins; bin++) {
            spectrogram[frame][bin] = complex_mag(fft_buffer[bin]);
        }
    }

    free(window);
    free(fft_buffer);

    *out_num_frames = num_frames;
    *out_num_bins = num_bins;

    return spectrogram;
}
/* End of compute_spectrogram() */
/******************************************************************************/

/******************************************************************************
 * free_spectrogram
 *
 * @param[in,out] spectrogram Pointer to 2D spectrogram array to free
 * @param[in]     num_frames  Number of time frames (rows) in spectrogram
 *
 * @note
 * - Frees memory allocated by compute_spectrogram().
 *
 * @warning
 * - Safe to call with NULL pointer (no operation).
 */
void free_spectrogram(double **spectrogram, int num_frames) {
    if (!spectrogram) return;
    for (int i = 0; i < num_frames; i++) {
        free(spectrogram[i]);
    }
    free(spectrogram);
}
/* End of free_spectrogram() */
/******************************************************************************/
