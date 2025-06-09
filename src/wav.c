#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"

static uint32_t read_uint32_le(FILE *f) {
    uint8_t b[4];
    if (fread(b, 1, 4, f) != 4) return 0;
    return b[0] | (b[1]<<8) | (b[2]<<16) | (b[3]<<24);
}

static uint16_t read_uint16_le(FILE *f) {
    uint8_t b[2];
    if (fread(b, 1, 2, f) != 2) return 0;
    return b[0] | (b[1]<<8);
}

int load_wav(const char *filename, WavData *out) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;

    char riff[4];
    if (fread(riff, 1, 4, f) != 4 || strncmp(riff, "RIFF", 4) != 0) {
        fclose(f);
        return -2;
    }

    fseek(f, 4, SEEK_CUR); // skip chunk size

    char wave[4];
    if (fread(wave, 1, 4, f) != 4 || strncmp(wave, "WAVE", 4) != 0) {
        fclose(f);
        return -3;
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
    fseek(f, 6, SEEK_CUR); // skip byte rate + block align
    uint16_t bits_per_sample = read_uint16_le(f);
    fseek(f, chunk_size - 16, SEEK_CUR); // Skip rest of fmt chunk

    if (audio_format != 1 || bits_per_sample != 16) {
        fclose(f);
        return -5; // unsupported format
    }

    // Find "data" chunk
    while (1) {
        if (fread(chunk_id, 1, 4, f) != 4) { fclose(f); return -6; }
        chunk_size = read_uint32_le(f);
        if (strncmp(chunk_id, "data", 4) == 0) break;
        fseek(f, chunk_size, SEEK_CUR);
    }

    int num_samples = chunk_size / 2; // 16-bit = 2 bytes/sample
    int16_t *data = malloc(chunk_size);
    if (!data) { fclose(f); return -7; }

    if (fread(data, 1, chunk_size, f) != chunk_size) {
        free(data);
        fclose(f);
        return -8;
    }

    fclose(f);

    out->sample_rate = sample_rate;
    out->num_channels = num_channels;
    out->num_samples = num_samples;
    out->samples = data;

    return 0;
}

void free_wav(WavData *wav) {
    if (wav->samples) {
        free(wav->samples);
        wav->samples = NULL;
    }
}
