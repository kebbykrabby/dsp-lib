/*
 * @file lms_example.c
 *  
 * Test routine for LMS adaptive filter:
 *   1. Generates a clean sinusoidal signal as the desired signal
 *   2. Adds uniform random noise to create a noisy input signal
 *   3. Applies LMS adaptive filtering to estimate the clean signal
 *   4. Saves the clean, noisy, and filtered signals to a CSV file
 *   5. Launches a Python script to visualize the results
 *
 * Created on: Jun 16, 2025
 * Author: Omri Kebede
 */

/******************************************************************************/
/* include block */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lms_filter.h"  /* LMS filter header */

/******************************************************************************/
/* main function */

/******************************************************************************
 * main
 *
 * @param[in]     none
 *
 * @returns       0 if successful, 1 if an error occurred
 *
 * @note          Demonstrates LMS adaptive filtering on a synthetic signal.
 *                Outputs data for visualization and calls a Python plot script.
 *
 * @warning       Ensure "plots/lms.csv" path exists and Python environment is set.
 ******************************************************************************/
int main() {
    #define NUM_SAMPLES 256
    #define FILTER_ORDER 4
    #define MU 0.01

    double t[NUM_SAMPLES];
    double clean[NUM_SAMPLES];
    double noisy[NUM_SAMPLES];
    double filtered[NUM_SAMPLES];
    double weights[FILTER_ORDER];

    /* Generate test signals */
    for (int i = 0; i < NUM_SAMPLES; i++) {
        t[i] = i * 10.0 / NUM_SAMPLES;
        clean[i] = sin(t[i]);  /* clean reference signal */
        noisy[i] = clean[i] + ((double)rand() / RAND_MAX - 0.5);  /* noisy input */
    }

    /* Apply LMS adaptive filter */
    lms_filter(noisy, clean, NUM_SAMPLES, FILTER_ORDER, MU, filtered, weights);

    /* Save results to CSV for plotting */
    FILE *csv = fopen("plots/lms.csv", "w");
    if (!csv) {
        perror("Failed to open CSV");
        return 1;
    }

    fprintf(csv, "index,t,clean,noisy,filtered\n");
    for (int i = 0; i < NUM_SAMPLES; i++) {
        fprintf(csv, "%d,%lf,%lf,%lf,%lf\n", i, t[i], clean[i], noisy[i], filtered[i]);
    }
    fclose(csv);

    /* Call Python script for visualization */
    int ret = system("python3 examples/plot_lms.py");
    if (ret != 0) {
        fprintf(stderr, "Failed to run plot_lms.py\n");
    }

    return 0;
}
/* End of main() */
/******************************************************************************/
