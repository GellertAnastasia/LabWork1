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
	
	
	
	bih.width = height;
	bih.height = width;
	rotate_clockwise(rgb, bfh, bih, height, width);
	rotate_counterclockwise(rgb, bfh, bih, height, width);
	
	fclose(infile);
	
	return 0;
}
