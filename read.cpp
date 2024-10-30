#include <iostream>
#include <fstream>
#include <filesystem>
#include "bmpheader.h"


void read() {
	FILE *infile = fopen("source.bmp", "rb");
	if (!infile) {
		std::cout<<"Ошибка: не удается открыть файл"<<std::endl;
	}
	else {
		std::cout<<"Файл открыт"<<std::endl;
	}
	Bmpfheader bfh;
	size_t res;
	res = fread(&bfh, 1, sizeof(Bmpfheader), infile);
	if (res != sizeof(Bmpfheader)) {
		fclose(infile);
		std::cout<<"Ошибка чтения заголовка"<<std::endl;
	}
	if (bfh.bf_type != 0x4D42) {
		std::cout<<"не корректный bmp файл"<<std::endl;
	}
	Bmpiheader bih;
	size_t res2 = fread(&bih, 1, sizeof(Bmpiheader), infile);
	
	
	
	fclose(infile);
}
