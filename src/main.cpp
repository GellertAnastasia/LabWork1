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
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    
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

    rotate(bmp, "clockwise.bmp", true);
    rotate(bmp, "counterclockwise.bmp", false);
    int kernel_size = 5;
    float sigma = 1.0f;
    apply_gaussian_blur(kernel_size, sigma);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds\n";

    return 0;

}
