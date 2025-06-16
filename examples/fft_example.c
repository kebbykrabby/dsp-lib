/*
 * @file fft_example.c
 *
 * Example program demonstrating usage of FFT and IFFT functions.
 *
 * The program:
 *   1. Generates a synthetic signal composed of two sine waves.
 *   2. Computes the FFT of the generated signal.
 *   3. Stores the FFT results for analysis.
 *   4. Computes the inverse FFT (IFFT) to reconstruct the original signal.
 *   5. Saves the original signal, FFT magnitude, and reconstructed signal to a CSV file.
 *   6. Calls a Python script to plot the results.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "fft.h"

#define N 64
#define PI 3.14159265358979323846

int main() {
    Complex signal[N];
    Complex original[N];  // store original signal for plotting

    // Generate signal: 
    for (int i = 0; i < N; i++) {
        double t = (double)i / N * 4 * PI;
        double val = sin(t) + 0.5 * sin(3 * t);
        signal[i].real = val;
        signal[i].imag = 0.0;
        original[i] = signal[i]; 
    }

    // Compute FFT
    fft(signal, N);

    // Save FFT result for plotting
    Complex fft_result[N];
    for (int i = 0; i < N; i++) {
        fft_result[i] = signal[i];
    }

    // Compute IFFT
    ifft(signal, N);  // `signal` now holds IFFT

    // Output CSV for plotting
    FILE *f = fopen("plots/fft.csv", "w");
    if (!f) {
        perror("Failed to open file for writing");
        return 1;
    }

    fprintf(f, "Index,Original,FFT_Mag,IFFT_Reconstructed\n");
    for (int i = 0; i < N; i++) {
        double fft_mag = sqrt(fft_result[i].real * fft_result[i].real + fft_result[i].imag * fft_result[i].imag);
        fprintf(f, "%d,%f,%f,%f\n", i, original[i].real, fft_mag, signal[i].real);
    }

    fclose(f);

    // Plot using Python
    int ret = system("python3 examples/plot_fft.py");
    if (ret != 0) {
        fprintf(stderr, "Failed to run plot_fft.py\n");
    }

    return 0;
}
