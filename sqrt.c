#include <stdio.h>
#include <math.h>

float squareRoot(float x)
{
  unsigned int i = *(unsigned int*) &x;

  // adjust bias
  i  += 127 << 23;
  // approximation of square root
  i >>= 1;

  return *(float*) &i;
}

int main(void)
{
	float i;
	int j;

	for (j = 0; j < 1000; j++) {
		for (i = 0; i < 100000; i += 0.1)
		{
			//squareRoot(i);
			sqrt(i);
		}
	}


}
