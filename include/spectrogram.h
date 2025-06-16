/*
 * @file spectrogram.h
 *
 * Header file for spectrogram.c
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#ifndef SPECTROGRAM_H_
#define SPECTROGRAM_H_

#include "wav.h"
#include "window.h"

/* Contains spectrogram parameters and magnitude data */
typedef struct {
    int numFrames;   /* number of time frames */
    int numBins;     /* number of frequency bins */
    double **data;   /* pointer to 2D array of magnitudes [numFrames][numBins] */
} Spectrogram;

double **compute_spectrogram(const WavData *wav,
                             int fft_size,
                             int hop_size,
                             WindowType window_type,
                             int *out_num_frames,
                             int *out_num_bins);

void free_spectrogram(double **spectrogram, int num_frames);

#endif /* SPECTROGRAM_H_ */
