# dsp-lib

A lightweight and efficient C library for Digital Signal Processing (DSP) focused on audio analysis.

## Features

- WAV file reading and handling (Currently only mono WAV files are supported)
- Window functions for signal processing
- FFT and complex number operations
- Spectrogram computation and visualization support
- Modular design for easy integration into projects

## Usage

The library provides core DSP functionality to analyze and process audio signals, with a focus on spectrogram generation. Typical usage includes:

1. Load WAV audio data
2. Apply windowing functions
3. Compute FFT and IFFT on audio frames
4. Generate and save spectrogram data
5. Apply FIR filtering

Example usage and test scripts are provided in the repository.

## 📦 Build

Use `make` or your preferred build system to compile the library and tests:

make

## 🚀 Example Usage
Generate and Plot a Spectrogram
Run the example program on a mono WAV file:

./fft_example example.wav

This will:

-Compute a spectrogram using STFT
-Save the result to ./plots/spectrogram.csv

To automatically plot the spectrogram(requires Python with matplotlib, numpy, and pandas):

./fft_example example.wav --plot

The --plot flag is optional. It invokes the plot_spectrogram.py script automatically.

## 🧪 Python Plotting
You can also run the Python plotting script manually:

python3 plot_spectrogram.py ./plots/spectrogram.csv
