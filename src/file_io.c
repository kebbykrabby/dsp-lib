#include <stdio.h>
#include "file_io.h"

int save_spectrogram_csv(const char *filename, double **spectrogram, int num_frames, int num_bins) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    for (int frame = 0; frame < num_frames; frame++) {
        for (int bin = 0; bin < num_bins; bin++) {
            fprintf(f, "%f", spectrogram[frame][bin]);
            if (bin < num_bins - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}
