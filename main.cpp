/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "bmpheader.h"
#include "rotate.h"
#include "filter.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

int main()
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    if (!infile)
    {
        std::cout<<"Ошибка: не удается открыть файл"<<std::endl;
    }
    else
    {
        std::cout<<"Файл открыт"<<std::endl;
    }
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);

    rotate_clockwise(bmp);
    rotate_counterclockwise(bmp);
    int kernelSize = 5;
    float sigma = 1.0f;
    applyGaussianBlur(kernelSize, sigma);

    return 0;

}
