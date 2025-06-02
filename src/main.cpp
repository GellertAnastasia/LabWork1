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
    
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    if (!infile)
    {
        std::cout<<"Ошибка: не удается открыть файл"<<std::endl;
    }
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    rotate(bmp, "clockwise.bmp", true);
    rotate(bmp, "counterclockwise.bmp", false);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_rotate(bmp, "clockwise.bmp", true);
    old_rotate(bmp, "counterclockwise.bmp", false);
    auto oldend = std::chrono::high_resolution_clock::now();
    int kernel_size = 5;
    float sigma = 1.0f;
    apply_gaussian_blur(kernel_size, sigma);
    
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<<oldduration.count() << " seconds\n";
    
    return 0;

}
