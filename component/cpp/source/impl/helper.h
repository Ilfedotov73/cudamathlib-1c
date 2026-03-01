#ifndef HELPER_H
#define HELPER_H

#include <string>

namespace helper {
	// Чтение входной матрица как строки -- matstr, запись в квадратную матрицу -- *mat.
	void read_input(float* mat, std::string matstr, int msize);
	
	/* Запись матрицы-- * mat в строкую.
	   example: array = {123\n{456\n789\n}. */
	std::string mat_to_str(const float* mat, int msize, int mwidth);
}

#endif 