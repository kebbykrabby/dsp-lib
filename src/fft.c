#include <math.h>
#include <stdlib.h>
#include "fft.h"

#define PI 3.14159265358979323846

static void fft_rec(Complex *x, int n) {
    if (n <= 1) return;

    Complex *even = malloc(n / 2 * sizeof(Complex));
    Complex *odd = malloc(n / 2 * sizeof(Complex));

    for (int i = 0; i < n / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft_rec(even, n / 2);
    fft_rec(odd, n / 2);

    for (int k = 0; k < n / 2; k++) {
        double t = -2 * PI * k / n;
        Complex twiddle = {cos(t), sin(t)};
        Complex temp = {twiddle.real * odd[k].real - twiddle.imag * odd[k].imag,
                        twiddle.real * odd[k].imag + twiddle.imag * odd[k].real};
        x[k].real = even[k].real + temp.real;
        x[k].imag = even[k].imag + temp.imag;
        x[k + n / 2].real = even[k].real - temp.real;
        x[k + n / 2].imag = even[k].imag - temp.imag;
    }

    free(even);
    free(odd);
}

void fft(Complex *x, int n) {
    fft_rec(x, n);
}

void ifft(Complex *x, int n) {
    // Conjugate input
    for (int i = 0; i < n; i++) {
        x[i].imag = -x[i].imag;
    }

    fft_rec(x, n);

    // Conjugate output and scale
    for (int i = 0; i < n; i++) {
        x[i].real = x[i].real / n;
        x[i].imag = -x[i].imag / n;
    }
}
