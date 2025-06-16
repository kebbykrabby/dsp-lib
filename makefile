CC = gcc
CFLAGS = -O2 -Wall -Iinclude

SRC = src/fir_filter.c src/iir_filter.c src/lms_filter.c src/wav.c \
      src/complex.c src/fft.c src/window.c src/spectrogram.c 
OBJ = $(SRC:.c=.o)

EXAMPLES = fft_example spectrogram_example fir_example iir_example lms_example

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
all: $(EXAMPLES)

fft_example: examples/fft_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

spectrogram_example: examples/spectrogram_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

fir_example: examples/fir_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

iir_example: examples/iir_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

lms_example: examples/lms_example.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

examples/%.o: examples/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f src/*.o examples/*.o $(EXAMPLES) plots/*.csv