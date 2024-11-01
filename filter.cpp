#include "bmpheader.h"
#include <iostream>
#include <fstream>
#include <filesystem>

void applyGaussianFilter(Rgb** rgb, Bmpfheader bfh, Bmpiheader bih, int width, int height) {
	Rgb **rgb1 = new Rgb*[height];
	for (int i = 0; i < height; i++) {
		rgb1[i] = new Rgb[width];
	}
		
	const double kernel[5][5] = {
        	{1/273.0, 4/273.0, 6/273.0, 4/273.0, 1/273.0},
        	{4/273.0, 16/273.0, 24/273.0, 16/273.0, 4/273.0},
        	{6/273.0, 24/273.0, 36/273.0, 24/273.0, 6/273.0},
        	{4/273.0, 16/273.0, 24/273.0, 16/273.0, 4/273.0},
        	{1/273.0, 4/273.0, 6/273.0, 4/273.0, 1/273.0}
	};

	for (int i = 0; i < height; ++i) {
	        for (int j = 0; j < width; ++j) {
	        	double bSum = 0.0;
            		double gSum = 0.0;
            		double rSum = 0.0;

			for (int kx = -2; kx <= 2; ++kx) { 
	                	for (int ky = -2; ky <= 2; ++ky) { 
	                    		int ix = std::min(std::max(i + kx, 0), height - 1); 
	                    		int jx = std::min(std::max(j + ky, 0), width - 1); 
                     
	                    		bSum += rgb[ix][jx].rgb_blue * kernel[kx + 2][ky + 2]; 
	                    		gSum += rgb[ix][jx].rgb_green * kernel[kx + 2][ky + 2]; 
	                    		rSum += rgb[ix][jx].rgb_red * kernel[kx + 2][ky + 2]; 
	                	} 
	            	} 

            	rgb1[i][j].rgb_blue = static_cast<unsigned char>(std::min(std::max(int(bSum), 0), 255));
            	rgb1[i][j].rgb_green = static_cast<unsigned char>(std::min(std::max(int(gSum), 0), 255));
            	rgb1[i][j].rgb_red = static_cast<unsigned char>(std::min(std::max(int(rSum), 0), 255));
		}
	}
	
    	FILE *outfile = fopen("filter.bmp", "wb");
	fwrite(&bfh, 1,	sizeof(Bmpfheader), outfile);
	fwrite(&bih, 1,	sizeof(Bmpiheader), outfile);
	fseek(outfile, bfh.bf_off_bits, SEEK_SET);
	int padding = (4 - (bih.width * 3) % 4) % 4;
	
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
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
