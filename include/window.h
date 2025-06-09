#ifndef WINDOW_H
#define WINDOW_H

typedef enum {
    WINDOW_HAMMING,
    WINDOW_HANN
} WindowType;

void generate_window(double *window, int size, WindowType type);

#endif
