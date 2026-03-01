#include "helper.h"

#include <stdlib.h>
#include <iostream>

void helper::read_input(float* mat, std::string matstr, int msize)
{
	if (matstr.empty()) {
		std::cerr << "Error: the input matrix is empty." << '\n';
		abort();
	}

	if ((sizeof(mat) / sizeof(mat[0])) != msize) {
		std::cerr << "Error: the matrix size is not equal than the given matrix size." << '\n';
		abort();
	}

	int i = 0;
	for (int c : matstr) {
		if (i >= msize) { break; }
		if (c >= '0' || c <= '9') {	mat[i++] = c - '0'; }
	}
}

/* example: array = {123\n{456\n789\n}. */
std::string helper::mat_to_str(const float* mat, int msize, int mwidth)
{
	std::string prmat = "{";
	for (int i = 0; i < msize; ++i) {
		if (i % mwidth == 0) { prmat += '\n'; }
		prmat += std::to_string(mat[i]);
	}
	prmat += "}";

	return prmat;
}