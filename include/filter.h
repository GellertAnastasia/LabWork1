/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef FILTER_H
#define FILTER_H

void generate_gaussian_kernel(float** kernel, int size, float sigma);
void apply_gaussian_blur(int kernel_size, float sigma);

#endif
