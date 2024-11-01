#include "bmpheader.h"
#include "read.h"
#include "rotate.h"
#include <iostream>
#include <fstream>
#include <filesystem>

int main() {

	FILE *infile = fopen("source1.bmp", "rb");
	if (!infile) {
		std::cout<<"Ошибка: не удается открыть файл"<<std::endl;
	}
	else {
		std::cout<<"Файл открыт"<<std::endl;
	}
	Bmpfheader bfh;
	fread(&bfh, 1, sizeof(Bmpfheader), infile);
	Bmpiheader bih;
	fread(&bih, 1, sizeof(Bmpiheader), infile);
	int width = bih.width;
	int height = bih.height;
	
	
	Rgb **rgb = new Rgb*[height];
	for (int i = 0; i < height; i++) {
		rgb[i] = new Rgb[width];
	}
	fseek(infile, bfh.bf_off_bits, SEEK_SET);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rgb[i][j].rgb_blue = getc(infile);
			rgb[i][j].rgb_green = getc(infile);
			rgb[i][j].rgb_red = getc(infile);
		}
		
	}
	
	
	
	Rgb **rgb1 = new Rgb*[width];
	for (int i = 0; i < width; i++) {
		rgb1[i] = new Rgb[height];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rgb1[j][height - i - 1] = rgb[i][j];
		}
	}
	
	bih.width = height;
	bih.height = width;

	FILE *outfile1 = fopen("final1.bmp", "wb");

	fwrite(&bfh, 1,	sizeof(Bmpfheader), outfile1);
	fwrite(&bih, 1,	sizeof(Bmpiheader), outfile1);
	fseek(outfile1, bfh.bf_off_bits, SEEK_SET);
	int padding = (4 - (bih.width * 3) % 4) % 4;
		
	for (int i = 0; i < bih.height; ++i) {
		for (int j = 0; j < bih.width; ++j) {
			fwrite(&(rgb1[i][j].rgb_blue), 1, 1, outfile1);
			fwrite(&(rgb1[i][j].rgb_green), 1, 1, outfile1);
			fwrite(&(rgb1[i][j].rgb_red), 1, 1, outfile1);
		}
		for (int k = 0; k < padding; k++) {
        		fputc(0, outfile1);
        	}
	}
	
	
	
	
	Rgb **rgb2 = new Rgb*[width];
	for (int i = 0; i < width; i++) {
		rgb2[i] = new Rgb[height];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rgb2[width - j - 1][i] = rgb[i][j];
		}
	}
	
	FILE *outfile2 = fopen("final2.bmp", "wb");

	fwrite(&bfh, 1,	sizeof(Bmpfheader), outfile2);
	fwrite(&bih, 1,	sizeof(Bmpiheader), outfile2);
	fseek(outfile2, bfh.bf_off_bits, SEEK_SET);
	for (int i = 0; i < bih.height; ++i) {
		for (int j = 0; j < bih.width; ++j) {
			fwrite(&(rgb2[i][j].rgb_blue), 1, 1, outfile2);
			fwrite(&(rgb2[i][j].rgb_green), 1, 1, outfile2);
			fwrite(&(rgb2[i][j].rgb_red), 1, 1, outfile2);
		}
		for (int k = 0; k < padding; k++) {
        		fputc(0, outfile2);
        	}
        
	}
	
	fclose(infile);
	fclose(outfile1);
	fclose(outfile2);
	
	return 0;
}
