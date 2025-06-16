/*
 * @file complex.c
 *
 * Basic complex number operations: addition, subtraction,
 * multiplication, and magnitude calculation.
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include "complex.h"
#include <math.h>

/******************************************************************************/
/**
 * complex_add
 *
 * @param[in] a First complex number
 * @param[in] b Second complex number
 *
 * @returns Sum of two complex numbers (a + b)
 *
 * @note Performs element-wise addition of real and imaginary parts.
 *
 * @warning None
 */
Complex complex_add(Complex a, Complex b) {
    Complex result = {a.real + b.real, a.imag + b.imag};
    return result;
}
/* End of complex_add() */
/******************************************************************************/

/******************************************************************************/
/**
 * complex_sub
 *
 * @param[in] a First complex number
 * @param[in] b Second complex number
 *
 * @returns Difference of two complex numbers (a - b)
 *
 * @note Performs element-wise subtraction of real and imaginary parts.
 *
 * @warning None
 */
Complex complex_sub(Complex a, Complex b) {
    Complex result = {a.real - b.real, a.imag - b.imag};
    return result;
}
/* End of complex_sub() */
/******************************************************************************/

/******************************************************************************/
/**
 * complex_mul
 *
 * @param[in] a First complex number
 * @param[in] b Second complex number
 *
 * @returns Product of two complex numbers (a * b)
 *
 * @note Multiplies two complex numbers using formula:
 *       (a + bi)(c + di) = (ac - bd) + (ad + bc)i
 *
 * @warning None
 */
Complex complex_mul(Complex a, Complex b) {
    Complex result = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return result;
}
/* End of complex_mul() */
/******************************************************************************/

/******************************************************************************/
/**
 * complex_mag
 *
 * @param[in] a Complex number
 *
 * @returns Magnitude (modulus) of the complex number
 *
 * @note Computes sqrt(real^2 + imag^2)
 *
 * @warning None
 */
double complex_mag(Complex a) {
    return sqrt(a.real * a.real + a.imag * a.imag);
}
/* End of complex_mag() */
/******************************************************************************/
