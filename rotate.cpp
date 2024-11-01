#include "bmpheader.h"
#include <iostream>
#include <fstream>
#include <filesystem>


void rotate_clockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width) {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rgb1[width - j - 1][i] = rgb[i][j];
		}
	}
	
	FILE *outfile = fopen("rotated_clockwise.bmp", "wb");

	fwrite(&bfh, 1,	sizeof(Bmpfheader), outfile);
	fwrite(&bih, 1,	sizeof(Bmpiheader), outfile);
	fseek(outfile, bfh.bf_off_bits, SEEK_SET);
	int padding = (4 - (bih.width * 3) % 4) % 4;
	
	for (int i = 0; i < bih.height; ++i) {
		for (int j = 0; j < bih.width; ++j) {
			fwrite(&(rgb1[i][j].rgb_blue), 1, 1, outfile);
			fwrite(&(rgb1[i][j].rgb_green), 1, 1, outfile);
			fwrite(&(rgb1[i][j].rgb_red), 1, 1, outfile);
		}
		for (int k = 0; k < padding; k++) {
        		fputc(0, outfile);
        	}
        
	}
	fclose(outfile);
}


void rotate_counterclockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width) {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rgb1[j][height - i - 1] = rgb[i][j];
		}
	}
	
	FILE *outfile = fopen("rotated_counterclockwise.bmp", "wb");

	fwrite(&bfh, 1,	sizeof(Bmpfheader), outfile);
	fwrite(&bih, 1,	sizeof(Bmpiheader), outfile);
	fseek(outfile, bfh.bf_off_bits, SEEK_SET);
	int padding = (4 - (bih.width * 3) % 4) % 4;
	
	for (int i = 0; i < bih.height; ++i) {
		for (int j = 0; j < bih.width; ++j) {
			fwrite(&(rgb1[i][j].rgb_blue), 1, 1, outfile);
			fwrite(&(rgb1[i][j].rgb_green), 1, 1, outfile);
			fwrite(&(rgb1[i][j].rgb_red), 1, 1, outfile);
		}
		for (int k = 0; k < padding; k++) {
        		fputc(0, outfile);
        	}
        
	}
	fclose(outfile);
}
