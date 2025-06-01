/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "filter.h"

void generate_gaussian_kernel(float** kernel, int size, float sigma)
{
    float sum = 0.0f;
    int half_size = size / 2;
    
    #pragma omp parallel for reduction(+:sum) collapse(2) schedule(static)
    for (int y = -half_size; y <= half_size; ++y)
    {
        for (int x = -half_size; x <= half_size; ++x)
        {
            kernel[y + half_size][x + half_size] = (1.0f / (2.0f * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0f * sigma * sigma));
            sum += kernel[y + half_size][x + half_size];
        }
    }
    
    #pragma omp parallel for collapse(2) schedule(static)
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            kernel[y][x] /= sum;
        }
    }
}


void apply_gaussian_blur(int kernel_size, float sigma)
{

    std::ifstream infile("clockwise.bmp", std::ios::in | std::ios::binary);
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

    float** kernel = new float*[kernel_size];
    for (int i = 0; i < kernel_size; ++i)
    {
        kernel[i] = new float[kernel_size];
    }

    generate_gaussian_kernel(kernel, kernel_size, sigma);

    int width = bmp.width;
    int height = bmp.height;
    std::unique_ptr<char[]> new_data = std::make_unique<char[]>(bmp.height*row);
    
    #pragma omp parallel for schedule(dynamic) collapse(2)
    for (int y = kernel_size / 2; y < height - kernel_size / 2; ++y)
    {
        for (int x = kernel_size / 2; x < width - kernel_size / 2; ++x)
        {
            float r = 0, g = 0, b = 0;
            for (int ky = -kernel_size / 2; ky <= kernel_size / 2; ++ky)
            {
                for (int kx = -kernel_size / 2; kx <= kernel_size / 2; ++kx)
                {
                    int pixel_index = ((y + ky) * row + (x + kx) * 3);
                    b += (unsigned char)(data[pixel_index]) * kernel[ky + kernel_size / 2][kx + kernel_size / 2];
                    g += (unsigned char)(data[pixel_index + 1]) * kernel[ky + kernel_size / 2][kx + kernel_size / 2];
                    r += (unsigned char)(data[pixel_index + 2]) * kernel[ky + kernel_size / 2][kx + kernel_size / 2];
                }
            }

            int new_pixel_index = (y * row + x * 3);
            new_data[new_pixel_index] = std::min(std::max(int(b), 0), 255);
            new_data[new_pixel_index + 1] = std::min(std::max(int(g), 0), 255);
            new_data[new_pixel_index + 2] = std::min(std::max(int(r), 0), 255);
        }
    }

    for (int i = 0; i < kernel_size; ++i)
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
    outfile.write(reinterpret_cast<const char*>(new_data.get()), bmp.height * row);
}




