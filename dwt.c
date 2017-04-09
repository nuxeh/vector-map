#include "pgm.x"

int main(int argc, char *argv[])
{
	unsigned char * in;
	int w, h;

	in = pgm_read(argv[1], &w, &h)

	int length = 0;
	int log_length = 0;
	while ( >>= 1) log_length++;

}


int discreteHaarWaveletTransform(unsigned char *input)
{
    // This function assumes that input.length=2^n, n>1
    int *output = new int[input.length];

    for (int length = input.length >> 1; ; length >>= 1) {
        // length = input.length / 2^n, WITH n INCREASING to log_2(input.length)
        for (int i = 0; i < length; ++i) {
            int sum = input[i * 2] + input[i * 2 + 1];
            int difference = input[i * 2] - input[i * 2 + 1];
            output[i] = sum;
            output[length + i] = difference;
        }
        if (length == 1) {
            return output;
        }

        //Swap arrays to do next iteration
        System.arraycopy(output, 0, input, 0, length << 1);
    }
}
