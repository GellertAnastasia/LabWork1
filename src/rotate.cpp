/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#include "rotate.h"


void rotate(Bmp bmp, const std::string& filename, bool is_clockwise)
{
    std::ifstream infile("source.bmp", std::ios::binary);
    int row = (bmp.width * 3 + 3) & (~3);
    std::unique_ptr<char[]> data = std::make_unique<char[]>(bmp.height * row);
    infile.seekg(bmp.bf_off_bits, std::ios::beg);
    infile.read(data.get(), bmp.height * row);
    infile.close();

    Bmp n_bmp = bmp;
    n_bmp.width = bmp.height;
    n_bmp.height = bmp.width;
    int n_row = (n_bmp.width * 3 + 3) & (~3);

    std::unique_ptr<char[]> rotated_data = std::make_unique<char[]>(n_bmp.height * n_row);
    
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < bmp.height; ++y)
    {
        for (int x = 0; x < bmp.width; ++x)
        {
            int old_index = y * row + x * 3;
            int new_index;
            
            if (is_clockwise) {
                new_index = (bmp.width - x - 1) * n_row + y * 3;
            } else {
                new_index = x * n_row + (bmp.height - y - 1) * 3;
            }

            rotated_data[new_index]     = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    }
    std::ofstream outfile(filename, std::ios::binary|std::ios::out);
    outfile.write(reinterpret_cast<char*>(&n_bmp), sizeof(Bmp));
    outfile.seekp(n_bmp.bf_off_bits, std::ios::beg);
    outfile.write(rotated_data.get(), n_bmp.height * n_row);
    outfile.close();
}



void old_rotate(Bmp bmp, const std::string& filename, bool is_clockwise)
{
    std::ifstream infile("source.bmp", std::ios::binary);
    int row = (bmp.width * 3 + 3) & (~3);
    std::unique_ptr<char[]> data = std::make_unique<char[]>(bmp.height * row);
    infile.seekg(bmp.bf_off_bits, std::ios::beg);
    infile.read(data.get(), bmp.height * row);
    infile.close();

    Bmp n_bmp = bmp;
    n_bmp.width = bmp.height;
    n_bmp.height = bmp.width;
    int n_row = (n_bmp.width * 3 + 3) & (~3);

    std::unique_ptr<char[]> rotated_data = std::make_unique<char[]>(n_bmp.height * n_row);
    
    for (int y = 0; y < bmp.height; ++y)
    {
        for (int x = 0; x < bmp.width; ++x)
        {
            int old_index = y * row + x * 3;
            int new_index;
            
            if (is_clockwise) {
                new_index = (bmp.width - x - 1) * n_row + y * 3;
            } else {
                new_index = x * n_row + (bmp.height - y - 1) * 3;
            }

            rotated_data[new_index]     = data[old_index];
            rotated_data[new_index + 1] = data[old_index + 1];
            rotated_data[new_index + 2] = data[old_index + 2];
        }
    }
    std::ofstream outfile(filename, std::ios::binary|std::ios::out);
    outfile.write(reinterpret_cast<char*>(&n_bmp), sizeof(Bmp));
    outfile.seekp(n_bmp.bf_off_bits, std::ios::beg);
    outfile.write(rotated_data.get(), n_bmp.height * n_row);
    outfile.close();
}
