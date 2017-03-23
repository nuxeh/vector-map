#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct quirc_point {
	int x;
	int y;
};

struct quirc_point cns[3] = {
	{10, 10},
	{100, 20},
	{30, 120}
};

struct vector {
	int i;			/* x component */
	int j;			/* y component */
	int m;			/* magnitude */
};


struct connection {
	int p1;
	int p2;
	struct vector v;	/* connection vector */
};

unsigned char img[200 * 200];
void write_img(void);
void draw_points(void);
void draw_matches(void);

int main(void)
{
	draw_points();
	printf("hello\n");

	int i, j;
	double d;
	//int d;
	int x, y;

	struct connection connections[3 * 3 - 3];
	int nc = 0;

	struct vector a, b;
	int dp;
	double theta;

	double score[3];

	// optimise use of sqrt
	// optimised acos() approximation

	/* Calculate possible connection vectors */
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) if (i != j)
		{
			struct connection c;
			struct vector v;

			x = cns[j].x - cns[i].x;
			y = cns[j].y - cns[i].y;

			// approximate square root
			d = sqrt((y * y) + (x * x));
			printf("%d->%d d: %f x: %d y: %d\n", i, j, d, x, y);
			//d = (y * y) + (x * x);

			c.p1 = i;
			c.p2 = j;

			v.i = x;
			v.j = y;
			v.m = d;
			//v.i = x * x;
			//v.j = y * y;

			c.v = v;

			connections[nc] = c;
			nc++;
		}
	}

	/* Evaluate every permutation, and score */
	for (i = 0; i < nc; i++) {
		for (j = 0; j < nc; j++) if (i != j)
		{
			struct connection c1 = connections[i];
			struct connection c2 = connections[j];

			/* vectors both start at capstone B */
			if (c1.p1 == c2.p1)
			{
				printf("%d->%d->%d\n", connections[i].p1,
							connections[i].p2,
							connections[j].p2);

				a = c1.v;
				b = c2.v;

				/* calculate dot product */
				dp = (a.i * b.i) + (a.j * b.j);

				printf("dp: %d rhs: %f\n", dp, (double) dp / (a.m * b.m));
				/* calculate angle */
				// approximate
				theta = acos((double) dp / (a.m * b.m));
				printf("theta: %f\n", (theta / (2 * M_PI)) * 360);

				/* assign scores */
				/* sides are of equal length */
				score[0] = 1.0 - ((double) a.m / b.m);
				/* sides are 90 degrees */
				score[1] = 1.0 - (theta / (0.5 * M_PI));
				/* sides are as small as possible */
				score[2] = 0; //1.0 - (a.m / b.m);

				printf("score: %04f %04f %04f\n", score[0], score[1], score[2]);
			}
		}
	}

	printf("done\n");
	draw_matches();
	write_img();
}

void draw_points(void)
{
	int i;

	memset(img, 255, 200 * 200);
	for (i = 0; i < 3; i++) {
		img[cns[i].x + (200 * cns[i].y)] = 0;
		img[cns[i].x + (200 * cns[i].y) + 1] = 0;
		img[cns[i].x + (200 * cns[i].y) - 1] = 0;
		img[cns[i].x + (200 * (cns[i].y - 1))] = 0;
		img[cns[i].x + (200 * (cns[i].y + 1))] = 0;
		printf("%d %d %d\n", i, cns[i].x, cns[i].y);
	}
}

void draw_matches(void)
{


}

void write_img(void)
{
	FILE *f;
	f = fopen("map.pgm" , "w");
	fprintf(f, "P5\n%d %d\n255\n", 200, 200);
	fwrite(img, 200, 200, f);
}
