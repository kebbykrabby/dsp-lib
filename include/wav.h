/*
 * @file wav.c
 *
 * Functions to load, validate, save, and free 16-bit PCM WAV audio files.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */
#ifndef WAV_H
#define WAV_H

#include <stdint.h>

/* Structure to hold WAV audio data */
typedef struct {
    int sample_rate;       /* Sample rate in Hz */
    int num_channels;      /* Number of audio channels */
    uint16_t bits_per_sample; /* Bits per audio sample (should be 16) */
    int num_samples;       /* Number of samples */
    int16_t *samples;      /* Pointer to audio samples */
} WavData;

/* Load a 16-bit PCM WAV file. Returns 0 on success, negative on error */
int load_wav(const char *filename, WavData *out);

/* Check if WAV data is mono 16-bit. Returns 0 if valid */
int validate_wav_format(const WavData *wav);

/* Free the memory used by WAV samples */
void free_wav(WavData *wav);

/* Save WAV data as a 16-bit PCM WAV file. Returns 0 on success */
int save_wav(const char *filename, const WavData *wav);

#endif
