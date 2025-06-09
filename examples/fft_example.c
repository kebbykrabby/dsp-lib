#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "spectrogram.h"
#include "file_io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s input.wav [--plot]\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    int should_plot = argc >= 3 && strcmp(argv[2], "--plot") == 0;

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

    save_spectrogram_csv("plots/spectrogram.csv", spectrogram, num_frames, num_bins);

    printf("Spectrogram saved: frames=%d bins=%d\n", num_frames, num_bins);

    free_spectrogram(spectrogram, num_frames);
    free_wav(&wav);

    if (should_plot) {
        int ret = system("python3 examples/plot_spectrogram.py plots/spectrogram.csv");
printf("Plot script exited with code: %d\n", ret);
    }

    return 0;
}
