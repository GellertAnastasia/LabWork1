/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "bmpheader.h"
#include <iostream>
#include <fstream>
#include <filesystem>


void rotate_clockwise(Bmp bmp)
{

    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    int row = (bmp.width * 3 + 3) & (~3);
    std::unique_ptr<char[]> data = std::make_unique<char[]>(bmp.height*row);
    infile.seekg(bmp.bf_off_bits, std::ios::beg);
    infile.read(reinterpret_cast<char*>(data.get()), bmp.height*row);
    infile.close();

    Bmp n_bmp = bmp;
    n_bmp.width = bmp.height;
    n_bmp.height = bmp.width;
    int n_row = (n_bmp.width * 3 + 3) & (~3);

    std::unique_ptr<char[]> rotated_data = std::make_unique<char[]>(n_bmp.height*n_row);
    std::ofstream outfile("rotated_clockwise.bmp",std::ios::binary|std::ios::out);
    outfile.write(reinterpret_cast<char*>(&n_bmp), 54);
    outfile.seekp(n_bmp.bf_off_bits, std::ios::beg);

    for (int y = 0; y < bmp.height; ++y)
    {
        for (int x = 0; x < bmp.width; ++x)
        {
            int oldIndex = y * row + x * 3;
            int newIndex = (bmp.width - x - 1) * n_row + y * 3;

            rotated_data[newIndex]     = data[oldIndex];
            rotated_data[newIndex + 1] = data[oldIndex + 1];
            rotated_data[newIndex + 2] = data[oldIndex + 2];
        }
    }

    outfile.write(reinterpret_cast<char*>(rotated_data.get()), bmp.height*row);
    outfile.close();
}



void rotate_counterclockwise(Bmp bmp)
{

    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    int row = (bmp.width * 3 + 3) & (~3);
    std::unique_ptr<char[]> data = std::make_unique<char[]>(bmp.height*row);
    infile.seekg(bmp.bf_off_bits, std::ios::beg);
    infile.read(reinterpret_cast<char*>(data.get()), bmp.height*row);
    infile.close();

    Bmp n_bmp = bmp;
    n_bmp.width = bmp.height;
    n_bmp.height = bmp.width;
    int n_row = (n_bmp.width * 3 + 3) & (~3);

    std::unique_ptr<char[]> rotated_data = std::make_unique<char[]>(n_bmp.height*n_row);
    std::ofstream outfile("rotated_counterclockwise.bmp",std::ios::binary|std::ios::out);
    outfile.write(reinterpret_cast<char*>(&n_bmp), 54);
    outfile.seekp(n_bmp.bf_off_bits, std::ios::beg);

    for (int y = 0; y < bmp.height; ++y)
    {
        for (int x = 0; x < bmp.width; ++x)
        {
            int oldIndex = y * row + x * 3;
            int newIndex = x * n_row + (bmp.height - y - 1) * 3;

            rotated_data[newIndex]     = data[oldIndex];
            rotated_data[newIndex + 1] = data[oldIndex + 1];
            rotated_data[newIndex + 2] = data[oldIndex + 2];
        }
    }

    outfile.write(reinterpret_cast<char*>(rotated_data.get()), bmp.height*row);
    outfile.close();
}
