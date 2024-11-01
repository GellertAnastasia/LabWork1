#ifndef ROTATE_H
#define ROTATE_H

void rotate_clockwise(Rgb** rgb, Bmpfheader bfh, Bmpiheader bih, int height, int width);
void rotate_counterclockwise(Rgb** rgb, Bmpfheader bfh, Bmpiheader bih, int height, int width);

#endif
