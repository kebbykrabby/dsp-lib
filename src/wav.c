/*
 * @file wav.c
 *
 * WAV file loader and saver for 16-bit PCM WAV audio files.
 * Supports reading WAV files into memory, validating mono 16-bit format,
 * freeing allocated memory, and saving WAV data to disk.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "wav.h"

/* Internal helper: read 4 bytes as little-endian uint32 from file */
static uint32_t read_uint32_le(FILE *f) {
    uint8_t b[4];
    if (fread(b, 1, 4, f) != 4) return 0;
    return b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24);
}

/* Internal helper: read 2 bytes as little-endian uint16 from file */
static uint16_t read_uint16_le(FILE *f) {
    uint8_t b[2];
    if (fread(b, 1, 2, f) != 2) return 0;
    return b[0] | (b[1]<<8);
}

/**
 * Loads a 16-bit PCM WAV file from disk into a WavData struct.
 * Supports mono or stereo.
 * Returns 0 on success, negative error codes on failure.
 */
int load_wav(const char *filename, WavData *out) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;

    char riff[4];
    if (fread(riff, 1, 4, f) != 4 || strncmp(riff, "RIFF", 4) != 0) {
        fclose(f);
        return -2;  // Not a RIFF file
    }

    fseek(f, 4, SEEK_CUR); // Skip chunk size

    char wave[4];
    if (fread(wave, 1, 4, f) != 4 || strncmp(wave, "WAVE", 4) != 0) {
        fclose(f);
        return -3;  // Not a WAVE format
    }

    char chunk_id[4];
    uint32_t chunk_size;

    // Find "fmt " chunk
    while (1) {
        if (fread(chunk_id, 1, 4, f) != 4) { fclose(f); return -4; }
        chunk_size = read_uint32_le(f);
        if (strncmp(chunk_id, "fmt ", 4) == 0) break;
        fseek(f, chunk_size, SEEK_CUR);
    }

    uint16_t audio_format = read_uint16_le(f);
    uint16_t num_channels = read_uint16_le(f);
    uint32_t sample_rate = read_uint32_le(f);
    fseek(f, 6, SEEK_CUR); // Skip byte rate + block align
    uint16_t bits_per_sample = read_uint16_le(f);
    fseek(f, chunk_size - 16, SEEK_CUR); // Skip any extra fmt bytes

    if (audio_format != 1 || bits_per_sample != 16) {
        fclose(f);
        return -5; // Unsupported format (only PCM 16-bit supported)
    }

    // Find "data" chunk
    while (1) {
        if (fread(chunk_id, 1, 4, f) != 4) { fclose(f); return -6; }
        chunk_size = read_uint32_le(f);
        if (strncmp(chunk_id, "data", 4) == 0) break;
        fseek(f, chunk_size, SEEK_CUR);
    }

    int num_samples = chunk_size / 2; // 2 bytes per sample (16-bit)
    int16_t *data = malloc(chunk_size);
    if (!data) { fclose(f); return -7; }

    if (fread(data, 1, chunk_size, f) != chunk_size) {
        free(data);
        fclose(f);
        return -8;
    }

    fclose(f);

    // Fill output struct
    out->sample_rate = sample_rate;
    out->num_channels = num_channels;
    out->num_samples = num_samples;
    out->bits_per_sample = bits_per_sample;
    out->samples = data;

    return 0;
}

/**
 * Validates that a WavData struct contains mono 16-bit data.
 * Returns 0 if valid, negative error codes otherwise.
 */
int validate_wav_format(const WavData *wav) {
    if (!wav) {
        fprintf(stderr, "Error: WAV data is NULL\n");
        return -1;
    }
    if (wav->num_channels != 1) {
        fprintf(stderr, "Error: WAV file is not mono. Channels: %d\n", wav->num_channels);
        return -2;
    }
    if (wav->bits_per_sample != 16) {
        fprintf(stderr, "Error: WAV file is not 16-bit. Bits per sample: %d\n", wav->bits_per_sample);
        return -3;
    }
    return 0;  // valid format
}

/**
 * Frees memory allocated for samples in WavData.
 */
void free_wav(WavData *wav) {
    if (wav->samples) {
        free(wav->samples);
        wav->samples = NULL;
    }
}

/* Internal helper: write a 4-byte little-endian uint32 to file */
static void write_uint32_le(FILE *f, uint32_t val) {
    uint8_t b[4] = { val & 0xFF, (val >> 8) & 0xFF, (val >> 16) & 0xFF, (val >> 24) & 0xFF };
    fwrite(b, 1, 4, f);
}

/* Internal helper: write a 2-byte little-endian uint16 to file */
static void write_uint16_le(FILE *f, uint16_t val) {
    uint8_t b[2] = { val & 0xFF, (val >> 8) & 0xFF };
    fwrite(b, 1, 2, f);
}

/**
 * Saves WAV data as a 16-bit PCM file to disk.
 * Returns 0 on success, negative error codes on failure.
 */
int save_wav(const char *filename, const WavData *wav) {
    if (!wav || !wav->samples) return -1;

    FILE *f = fopen(filename, "wb");
    if (!f) return -2;

    uint32_t data_chunk_size = wav->num_samples * wav->num_channels * (wav->bits_per_sample / 8);
    uint32_t fmt_chunk_size = 16;
    uint32_t riff_chunk_size = 4 + (8 + fmt_chunk_size) + (8 + data_chunk_size);

    // Write RIFF header
    fwrite("RIFF", 1, 4, f);
    write_uint32_le(f, riff_chunk_size);
    fwrite("WAVE", 1, 4, f);

    // Write fmt chunk
    fwrite("fmt ", 1, 4, f);
    write_uint32_le(f, fmt_chunk_size);
    write_uint16_le(f, 1); // PCM format
    write_uint16_le(f, wav->num_channels);
    write_uint32_le(f, wav->sample_rate);
    uint32_t byte_rate = wav->sample_rate * wav->num_channels * (wav->bits_per_sample / 8);
    write_uint32_le(f, byte_rate);
    uint16_t block_align = wav->num_channels * (wav->bits_per_sample / 8);
    write_uint16_le(f, block_align);
    write_uint16_le(f, wav->bits_per_sample);

    // Write data chunk
    fwrite("data", 1, 4, f);
    write_uint32_le(f, data_chunk_size);
    fwrite(wav->samples, 1, data_chunk_size, f);

    fclose(f);
    return 0;
}
