/*
 * @file window.h
 *
 * Header file for window.c
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

#ifndef WINDOW_H_
#define WINDOW_H_

/* Enum for supported window types */
typedef enum {
    WINDOW_HAMMING, /* Hamming window */
    WINDOW_HANN     /* Hann window */
} WindowType;

/* Generates window coefficients of given size and type.*/
void generate_window(double *window, int size, WindowType type);

#endif /* WINDOW_H_ */
