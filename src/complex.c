#include "complex.h"
#include <math.h>

Complex complex_add(Complex a, Complex b) {
    Complex result = {a.real + b.real, a.imag + b.imag};
    return result;
}

Complex complex_sub(Complex a, Complex b) {
    Complex result = {a.real - b.real, a.imag - b.imag};
    return result;
}

Complex complex_mul(Complex a, Complex b) {
    Complex result = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return result;
}

double complex_mag(Complex a) {
    return sqrt(a.real * a.real + a.imag * a.imag);
}
