#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include "wav.h"
#include "window.h"

double **compute_spectrogram(const WavData *wav,
                             int fft_size,
                             int hop_size,
                             WindowType window_type,
                             int *out_num_frames,
                             int *out_num_bins);

void free_spectrogram(double **spectrogram, int num_frames);

#endif
