/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef BMPHEADER_H
#define BMPHEADER_H
#include <iostream>
#pragma pack(push, 1)

struct Bmp
{
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reversed1;
    uint16_t bf_reversed2;
    uint32_t bf_off_bits;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_per_pixel;
    uint32_t compression;
    uint32_t size_data;
    int32_t pwidth;
    int32_t pheight;
    uint32_t count_colors;
    uint32_t count_imp_colors;
};



#pragma pack(pop)

#endif
