#ifndef ROTATE_H
#define ROTATE_H

void rotate_clockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width);
void rotate_counterclockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width);

#endif
