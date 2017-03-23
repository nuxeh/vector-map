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

unsigned char img[200 * 200];
void write_img(void);
void draw_points(void);

int main(void)
{
	draw_points();

	printf("hello\n");





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
