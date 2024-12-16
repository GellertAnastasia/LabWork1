/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "bmpheader.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

void generateGaussianKernel(float** kernel, int size, float sigma)
{

    float sum = 0.0f;
    int halfSize = size / 2;
    for (int y = -halfSize; y <= halfSize; ++y)
    {
        for (int x = -halfSize; x <= halfSize; ++x)
        {
            kernel[y + halfSize][x + halfSize] = (1.0f / (2.0f * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0f * sigma * sigma));
            sum += kernel[y + halfSize][x + halfSize];
        }
    }
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            kernel[y][x] /= sum;
        }
    }
}


void applyGaussianBlur(int kernelSize, float sigma)
{

    std::ifstream infile("rotated_clockwise.bmp", std::ios::in | std::ios::binary);
    if (!infile)
    {
        std::cout<<"Ошибка: не удается открыть файл1"<<std::endl;
    }
    else
    {
        std::cout<<"Файл открыт"<<std::endl;
    }
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    int row = (bmp.width * 3 + 3) & (~3);
    std::unique_ptr<char[]> data = std::make_unique<char[]>(bmp.height*row);
    infile.seekg(bmp.bf_off_bits, std::ios::beg);
    infile.read(reinterpret_cast<char*>(data.get()), bmp.height*row);
    infile.close();

    float** kernel = new float*[kernelSize];
    for (int i = 0; i < kernelSize; ++i)
    {
        kernel[i] = new float[kernelSize];
    }

    generateGaussianKernel(kernel, kernelSize, sigma);

    int width = bmp.width;
    int height = bmp.height;
    std::unique_ptr<char[]> newData = std::make_unique<char[]>(bmp.height*row);

    for (int y = kernelSize / 2; y < height - kernelSize / 2; ++y)
    {
        for (int x = kernelSize / 2; x < width - kernelSize / 2; ++x)
        {
            float r = 0, g = 0, b = 0;
            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky)
            {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx)
                {
                    int pixelIndex = ((y + ky) * row + (x + kx) * 3);
                    b += (unsigned char)(data[pixelIndex]) * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                    g += (unsigned char)(data[pixelIndex + 1]) * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                    r += (unsigned char)(data[pixelIndex + 2]) * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                }
            }

            int newPixelIndex = (y * row + x * 3);
            newData[newPixelIndex] = std::min(std::max(int(b), 0), 255);
            newData[newPixelIndex + 1] = std::min(std::max(int(g), 0), 255);
            newData[newPixelIndex + 2] = std::min(std::max(int(r), 0), 255);
        }
    }

    for (int i = 0; i < kernelSize; ++i)
    {
        delete[] kernel[i];
    }
    delete[] kernel;

    std::ofstream outfile("filter.bmp", std::ios::out | std::ios::binary);
    if (!outfile)
    {
        std::cerr << "Ошибка: не удается открыть файл для записи" << std::endl;
        return;
    }
    outfile.write(reinterpret_cast<const char*>(&bmp), sizeof(Bmp));
    outfile.seekp(bmp.bf_off_bits, std::ios::beg);
    outfile.write(reinterpret_cast<const char*>(newData.get()), bmp.height * row);
}




