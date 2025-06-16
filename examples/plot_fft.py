import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("plots/fft.csv")

# Plot
plt.figure(figsize=(12, 8))

plt.subplot(3, 1, 1)
plt.plot(df["Index"], df["Original"], label="Original Signal", color="blue")
plt.title("Original Signal")
plt.grid(True)

plt.subplot(3, 1, 2)
plt.plot(df["Index"], df["FFT_Mag"], label="FFT Magnitude", color="orange")
plt.title("FFT Magnitude Spectrum")
plt.grid(True)

plt.subplot(3, 1, 3)
plt.plot(df["Index"], df["IFFT_Reconstructed"], label="IFFT Reconstruction", color="green")
plt.title("Reconstructed Signal from IFFT")
plt.grid(True)

plt.tight_layout()
plt.show()
