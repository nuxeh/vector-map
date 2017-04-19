#include <string.h>
#include <stdio.h>
#include <math.h>
#include "pgm.x"


// This function assumes that input.length=2^n, n>1
void discreteHaarWaveletTransform(unsigned char *input, int l, int *output)
{
    for (int length = l >> 1; ; length >>= 1) {
        // length = input.length / 2^n, WITH n INCREASING to log_2(input.length)
        for (int i = 0; i < length; ++i) {
            int sum = input[i * 2] + input[i * 2 + 1];
            int difference = input[i * 2] - input[i * 2 + 1];
            output[i] = sum;
            output[length + i] = difference;
        }
        if (length == 1) {
            return;
        }

        //Swap arrays to do next iteration
	memcpy(input, output, length << 1);
    }
}

int main(int argc, char *argv[])
{
	unsigned char *in;
	int w, h;
	int y;

	printf("file: %s\n", argv[1]);
	in = pgm_read(argv[1], &w, &h);
	printf("width: %d height: %d\n", w, h);

	int length, l;
	length = l = w;
	printf("length: %d\n", length);
	int log_length = 0b10;
	while (length >>= 1) log_length <<= 1;
	printf("log length: %d\n", log_length);

	int *output;
	output = malloc(log_length * h * sizeof(int));

	char *row = malloc(log_length);
	memset(row, 0, log_length);

	for (y = 0; y < h; y++)
	{
		memcpy(row, in + y * w, w);
		discreteHaarWaveletTransform(row, log_length, output + y * log_length);

	}

	int i;
	//for (i = 0; i < log_length; i++)
	//	printf("%d ", abs(output[i]));

	unsigned char *out = malloc(log_length * h);
	for (i = 0; i < log_length * h; i++)
		out[i] = abs(output[i]);

	//pgm_write("dwt.pgm", (int)sqrt(log_length), (int)sqrt(log_length), out);
	pgm_write("dwt2.pgm", log_length, h, out);

	free(output);
	free(row);
	free(out);
}
