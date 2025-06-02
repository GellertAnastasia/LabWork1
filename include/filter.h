/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef FILTER_H
#define FILTER_H
#include "bmpheader.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <memory>
#include <omp.h>

void generate_gaussian_kernel(float** kernel, int size, float sigma);
void apply_gaussian_blur(const std::string& filename, int kernel_size, float sigma);

void old_generate_gaussian_kernel(float** kernel, int size, float sigma);
void old_apply_gaussian_blur(const std::string& filename, int kernelSize, float sigma);

#endif
