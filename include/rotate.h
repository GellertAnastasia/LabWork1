/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef ROTATE_H
#define ROTATE_H
#include "bmpheader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <omp.h>

void rotate(Bmp bmp, const std::string& filename, bool isClockwise);

#endif
