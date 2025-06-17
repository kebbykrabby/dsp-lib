# dsp-lib 🛠️

A compact, pure-C library implementing foundational signal processing algorithms:

- **Normalized LMS adaptive filter**
- **Basic complex number operations**
- **FFT/IFFT computation**
- **Spectrogram computation**
- **Window generation**

All components feature simple APIs, detailed examples, and minimal dependencies—perfect for DSP learning, prototyping, or embedded development.

---

## 📁 Repository Structure

```
dsp-lib/
├── include/           # Public headers
│   ├── adaptive_filter.h
│   ├── complex.h
│   ├── fft.h
│   ├── fir_filter.h
│   ├── iir_filter.h
│   ├── spectrogram.h
│   └── window.h
│
├── src/               # Implementation files
│   ├── adaptive_filter.c
│   ├── complex.c
│   ├── fft.c
│   ├── fir_filter.c
│   ├── iir_filter.c
│   ├── spectrogram.c
│   └── window.c
│
├── examples/          # Usage examples and plotting scripts
│   ├── adaptive_filter_example.c
│   ├── complex_example.c
│   ├── fft_example.c
│   ├── fir_example.c
│   ├── iir_example.c
│   ├── spectrogram_example.c
│   ├── plot_lms.py
│   └── plot_fft.py
│
├── plots/             # Example output (csv/plots) — *ignored by git*
├── .gitignore
└── README.md
```

---

## 🛠️ Features

- **Normalized LMS Adaptive Filter**\
  Estimate and track a desired signal by adapting filter weights using input and error feedback.

- **Complex Arithmetic**\
  Struct and functions for complex addition, subtraction, multiplication, and magnitude.

- **FFT / IFFT**\
  Recursive Cooley–Tukey implementation for full FFT and inverse FFT.

- **FIR Filter**\
  Fixed-coefficient FIR with circular buffer support.

- **IIR Filter**\
  Direct-form IIR with configurable numerator and denominator coefficients.

- **Spectrogram**\
  Frame-based magnitude spectrum computation using FFT and windowing.

- **Window Functions**\
  Hann, Hamming, and Rectangular windows.

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone git@github.com:kebbykrabby/dsp-lib.git
cd dsp-lib
```

### 2. Build & Compile

Compile library and examples using your C compiler:

```bash
gcc -Iinclude src/*.c examples/*.c -lm -o dsp_examples
```

Or compile only the example you need:

```bash
gcc -Iinclude src/complex.c examples/complex_example.c -lm -o complex_example
```

---

## 💡 Example Usage

### Adaptive Filter

```c
#include "adaptive_filter.h"
...
double buffer[16] = {0}, weights[16] = {0};
AfData f = {0.05, 0.001, 16, buffer, 0, weights, 0};

double in = 1.0, desired = 0.8;
double out = AdaptiveFilterRun(in, desired, &f);
printf("Output: %f , Error: %f\n", out, f.Error);
```

Run the example:

```bash
gcc -Iinclude src/adaptive_filter.c examples/adaptive_filter_example.c -lm -o adaptive_demo
./adaptive_demo
```

Use `plot_lms.py` to visualize performance.

---

### Complex Math

```c
#include "complex.h"
...
Complex a = {3,4}, b = {1,-2};
Complex c = complex_mul(a, b);
printf("c = %.2f + %.2fi\n", c.real, c.imag);
```

---

### FFT / IFFT

```c
#include "fft.h"
...
Complex sig[N];
...
fft(sig, N);    /* forward */
ifft(sig, N);   /* inverse */
```

Save output and plot with `plot_fft.py`.

---

### FIR / IIR Filters, Spectrogram, Windowing

Refer to the header comments and example files (`fir_example.c`, `iir_example.c`, `spectrogram_example.c`) for full usage instructions.

---

## 📃 API Reference

Browse each header in `include/` for detailed documentation and function prototypes.

---

## 🛠️ Build Configuration (Optional)

Feel free to add a `Makefile`, `CMakeLists.txt`, or other build scripts if integrating into larger projects.

---

## 🤝 Contributing

Contributions and issues welcome!\
Suggestions: performance optimization, fixed-point support, new DSP utilities, or embedded ports.

---

## 📌 Author

**Omri Kebede**



