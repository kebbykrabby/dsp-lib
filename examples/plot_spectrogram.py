import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

csv_file = sys.argv[1] if len(sys.argv) > 1 else "./plots/spectrogram.csv"

data = pd.read_csv(csv_file, header=None)
S = data.values
S = S.T
S_db = 20 * np.log10(S + 1e-12)

plt.figure(figsize=(10, 4))
plt.imshow(S_db, aspect='auto', origin='lower', cmap='magma')
plt.colorbar(label="Power (dB)")
plt.xlabel("Time Frame")
plt.ylabel("Frequency Bin")
plt.title("Spectrogram")
plt.tight_layout()
plt.savefig("./plots/spectrogram.png")
print("Saved plot to plots/spectrogram.png")
