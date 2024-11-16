/* Anastasia Gellert st130144@student.spbu.ru
	labwork 1
*/

#ifndef ROTATE_H
#define ROTATE_H
// Это стиль Си, а мы пишем на плюсах. У тебя тут 6 одинаковых аргументов, и все они могли быть
// внутренним состоянием класса обработки картинок. Причем один из параметров, как я понимаю, является
// входным-выходным, что нехорошо, потому что это совсем неочевидно.
// Нужно сделать из всего этого набора Сишных функции один хороший класс
void rotate_clockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width);
void rotate_counterclockwise(Rgb** rgb, Rgb** rgb1, Bmpfheader bfh, Bmpiheader bih, int height, int width);

#endif
