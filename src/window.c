#include <math.h>
#include "window.h"

#define PI 3.14159265358979323846

void generate_window(double *window, int size, WindowType type) {
    for (int n = 0; n < size; n++) {
        switch(type) {
            case WINDOW_HAMMING:
                window[n] = 0.54 - 0.46 * cos(2 * PI * n / (size - 1));
                break;
            case WINDOW_HANN:
                window[n] = 0.5 * (1 - cos(2 * PI * n / (size - 1)));
                break;
            default:
                window[n] = 1.0;
                break;
        }
    }
}
