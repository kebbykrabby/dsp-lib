#include <stdlib.h>
#include <string.h>
#include "spectrogram.h"
#include "fft.h"
#include "complex.h"
#include "window.h"

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

    // Allocate 2D spectrogram array [num_frames][num_bins]
    double **spectrogram = malloc(num_frames * sizeof(double*));
    for (int i = 0; i < num_frames; i++) {
        spectrogram[i] = calloc(num_bins, sizeof(double));
    }

    double *window = malloc(sizeof(double) * fft_size);
    generate_window(window, fft_size, window_type);

    Complex *fft_buffer = malloc(sizeof(Complex) * fft_size);

    for (int frame = 0; frame < num_frames; frame++) {
        int offset = frame * hop_size;

        // Apply window and copy samples to fft_buffer
        for (int i = 0; i < fft_size; i++) {
            int idx = offset + i;
            double sample = (idx < num_samples) ? wav->samples[idx] / 32768.0 : 0.0;
            fft_buffer[i].real = sample * window[i];
            fft_buffer[i].imag = 0.0;
        }

        fft(fft_buffer, fft_size);

        // Compute magnitude for bins 0..num_bins-1
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

void free_spectrogram(double **spectrogram, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        free(spectrogram[i]);
    }
    free(spectrogram);
}
