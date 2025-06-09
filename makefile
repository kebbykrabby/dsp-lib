CC = gcc
CFLAGS = -O2 -Wall -Iinclude

SRC = src/fir_filter.c src/wav.c src/complex.c src/fft.c src/window.c src/spectrogram.c src/file_io.c
OBJ = $(SRC:.c=.o)

all: fft_example

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fft_example: examples/fft_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

examples/fft_example.o: examples/fft_example.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f src/*.o examples/*.o fft_example plots/*.csv