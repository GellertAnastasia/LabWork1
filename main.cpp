/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "bmpheader.h"
#include "rotate.h"
#include "filter.h"
#include <iostream>
#include <fstream>
#include <filesystem>


int main()
{

    FILE *infile = fopen("source.bmp", "rb");
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
    fseek(infile, bfh.bf_off_bits, SEEK_SET);

    int width = bih.width;
    int height = bih.height;

    Rgb **rgb = new Rgb*[height];
    for (int i = 0; i < height; i++) {
        rgb[i] = new Rgb[width];
        for (int j = 0; j < width; j++) {
            rgb[i][j].rgb_blue = getc(infile);
            rgb[i][j].rgb_green = getc(infile);
            rgb[i][j].rgb_red = getc(infile);
        }
    }
    fclose(infile);



    bih.width = height;
    bih.height = width;

    Rgb **rgb1 = new Rgb*[width];
    for (int i = 0; i < width; i++) {
        rgb1[i] = new Rgb[height];
    }
    rotate_clockwise(rgb, rgb1, bfh, bih, height, width);
    rotate_counterclockwise(rgb, rgb1, bfh, bih, height, width);
    
    for (int i = 0; i < height; i++) {
        delete rgb[i];
    }
    delete[] rgb;

    filter(rgb1, bfh, bih, bih.width, bih.height);

    for (int i = 0; i < width; i++) {
        delete rgb1[i];
    }
    delete[] rgb1;


    return 0;
}
