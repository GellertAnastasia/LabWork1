/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef FILTER_H
#define FILTER_H

void generateGaussianKernel(float** kernel, int size, float sigma);
void applyGaussianBlur(int kernelSize, float sigma);

#endif
