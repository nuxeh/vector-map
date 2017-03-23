#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct quirc_point {
	int x;
	int y;
};

struct quirc_point c[3] = {
	{10, 10},
	{100, 20},
	{30, 120}
};

struct connection {
	int p1;
	int p2;
	int m;		/* gradient */
	int d;		/* displacement */
};

unsigned char img[200 * 200];
void write_img(void);
void draw_points(void);

int main(void)
{
	draw_points();
	printf("hello\n");

	int i, j;
	double m;
	int d;
	int x, y;

	struct connection connections[3 * 3 - 3];
	int nc = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) if (i != j) {
			x = c[j].x - c[i].x;
			y = c[j].y - c[i].y;

			printf("%d %d\n", x, y);

			m = (double) y / x;
			d = (y * y) + (x * x);

			printf("%f %d\n", m, d);

			struct connection c = {i, j, m, d};
			connections[nc] = c;
			nc++;
		}
	}


	printf("done\n");
	write_img();
}

void draw_points(void)
{
	int i;

	memset(img, 255, 200 * 200);
	for (i = 0; i < 3; i++) {
		img[c[i].x + (200 * c[i].y)] = 0;
		img[c[i].x + (200 * c[i].y) + 1] = 0;
		img[c[i].x + (200 * c[i].y) - 1] = 0;
		img[c[i].x + (200 * (c[i].y - 1))] = 0;
		img[c[i].x + (200 * (c[i].y + 1))] = 0;
		printf("%d %d %d\n", i, c[i].x, c[i].y);
	}
}

void write_img(void)
{
	FILE *f;
	f = fopen("map.pgm" , "w");
	fprintf(f, "P5\n%d %d\n255\n", 200, 200);
	fwrite(img, 200, 200, f);
}
