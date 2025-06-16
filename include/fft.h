/*
 * @file fft.h
 *
 * Header file for fft.c
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#ifndef FFT_H
#define FFT_H

#include "complex.h"

void fft(Complex *x, int n);
void ifft(Complex *x, int n);

#endif /* FFT_H */