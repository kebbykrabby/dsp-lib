/*
 * @file spectrogram_example.c
 *
 * Example program to compute and visualize a spectrogram from a mono WAV file.
 *   1. Loads a mono WAV file from disk
 *   2. Computes a magnitude spectrogram using short-time FFT
 *   3. Saves the spectrogram to a CSV file
 *   4. Launches a Python script to visualize the result
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/ 
/* include block */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wav.h"
#include "spectrogram.h"

/******************************************************************************/ 
/* main function */

/******************************************************************************
 * main
 *
 * @param[in] argc number of command-line arguments
 * @param[in] argv array of command-line argument strings
 *
 * @returns 0 if successful, non-zero if an error occurred
 *
 * @note
 * - Only mono WAV files are supported.
 * - Outputs spectrogram data to CSV for external plotting.
 * - Requires a Python script at examples/plot_spectrogram.py.
 *
 * @warning
 * - Ensure the "plots/" directory exists before running.
 * - Input WAV must be 16-bit PCM, mono.
 *****************************************************************************/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s input.wav\n", argv[0]);
        return 1;
    }

    WavData wav;
    if (load_wav(argv[1], &wav) != 0) {
        printf("Failed to load WAV file\n");
        return 1;
    }

    if (wav.num_channels != 1) {
        printf("Mono WAV only supported\n");
        free_wav(&wav);
        return 1;
    }

    int fft_size = 1024;
    int hop_size = 256;
    int num_frames, num_bins;

    double **spectrogram = compute_spectrogram(&wav, fft_size, hop_size, WINDOW_HANN, &num_frames, &num_bins);
    if (!spectrogram) {
        printf("Failed to compute spectrogram\n");
        free_wav(&wav);
        return 1;
    }

    FILE *f = fopen("plots/spectrogram.csv", "w");
    if (!f) {
        perror("Failed to open output CSV");
        free_spectrogram(spectrogram, num_frames);
        free_wav(&wav);
        return 1;
    }

    /* Write spectrogram data to CSV */
    for (int frame = 0; frame < num_frames; frame++) {
        for (int bin = 0; bin < num_bins; bin++) {
            fprintf(f, "%f", spectrogram[frame][bin]);
            if (bin < num_bins - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);

    printf("Spectrogram saved: frames=%d bins=%d\n", num_frames, num_bins);

    free_spectrogram(spectrogram, num_frames);
    free_wav(&wav);

    /* Launch Python script to plot spectrogram */
    int ret = system("python3 examples/plot_spectrogram.py plots/spectrogram.csv");
    if (ret != 0) {
        fprintf(stderr, "Failed to run plot_spectrogram.py\n");
    }

    return 0;
}
/* End of main() */
/******************************************************************************/
