#ifndef WAV_H
#define WAV_H

#include <stdint.h>

typedef struct {
    int sample_rate;
    int num_channels;
    int num_samples;
    int16_t *samples;  // Interleaved if stereo
} WavData;

int load_wav(const char *filename, WavData *out);
void free_wav(WavData *wav);

#endif