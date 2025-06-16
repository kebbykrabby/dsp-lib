# plot_lms.py
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("plots/lms.csv")

plt.figure(figsize=(10, 6))
plt.plot(df['t'], df['noisy'], label='Noisy Signal', alpha=0.6)
plt.plot(df['t'], df['filtered'], label='Filtered Signal (LMS)', color='red')
plt.plot(df['t'], df['clean'], label='Clean Signal', color='green')
plt.legend()
plt.xlabel("Time")
plt.ylabel("Amplitude")
plt.title("LMS Filter Result")
plt.grid(True)
plt.tight_layout()
plt.show()
