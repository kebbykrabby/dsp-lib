/**
 * @file lms_filter.h
 * @brief Header file for LMS adaptive filter implementation.
 *
 * This header declares the LMS (Least Mean Squares) adaptive filtering function,
 * which is used to reduce noise in a signal by iteratively adapting filter weights
 * to minimize the error between a noisy input and a desired (clean) signal.
 *
 * Created on: Jun 16, 2025  
 * Author: Omri Kebede
 */
#ifndef LMS_FILTER_H
#define LMS_FILTER_H

void lms_filter(
    const double *noisy_signal,
    const double *desired_signal,
    int num_samples,
    int filter_order,
    double mu,
    double *output_signal,
    double *final_weights
);

#endif 
