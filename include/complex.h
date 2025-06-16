/*
 * @file complex.h
 *
 * Header file for complex.c
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

/* Structure representing a complex number with real and imaginary parts */
typedef struct {
    double real;   /* Real part */
    double imag;   /* Imaginary part */
} Complex;

Complex complex_add(Complex a, Complex b);
Complex complex_sub(Complex a, Complex b);
Complex complex_mul(Complex a, Complex b);
double complex_mag(Complex a);

#endif /* COMPLEX_H_ */
